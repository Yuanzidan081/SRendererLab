#include "DrawTriangle.h"
#include "Render/FrameBuffer.h"
// #include "UI/window.h"
#include "DrawLine.h"
#include "UI/imagelabel.h"

void DrawTriangleWithoutDepthInfo(Vec3f *v, const Vec4f &color, const void *buffer, const SRendererType &type)
{
    switch (type)
    {
    case SRendererType::SWire:
        DrawTriangleLineModeWithoutDepthInfo(v, color, buffer);
        break;
    case SRendererType::SFill:
        DrawTriangleFillModeWithoutDepthInfo(v, color, buffer);
        break;
    default:
        std::cout << "invalid RendererType!";
        break;
    }
}

void DrawTriangleLineModeWithoutDepthInfo(Vec3f *v, const Vec4f &color, const void *buffer)
{
    DrawLineNaive(v[0], v[1], color, buffer);
    DrawLineNaive(v[1], v[2], color, buffer);
    DrawLineNaive(v[2], v[0], color, buffer);
}

void DrawTriangleFillModeWithoutDepthInfo(Vec3f *v, const Vec4f &color, const void *buffer)
{
    Vec3i v1(v[0].x, v[0].y, v[0].z);
    Vec3i v2(v[1].x, v[1].y, v[1].z);
    Vec3i v3(v[2].x, v[2].y, v[2].z);

    if (v1.y == v3.y && v1.y == v2.y)
        return;
    // v1.y <= v2.y <= v3.y
    if (v1.y > v2.y)
        std::swap(v1, v2);
    if (v1.y > v3.y)
        std::swap(v1, v3);
    if (v2.y > v3.y)
        std::swap(v2, v3);
    int total_height = v3.y - v1.y;
    for (int i = 0; i <= total_height; ++i)
    {
        // 根据t1将三角形分为上下两部分
        bool second_half = i > v2.y - v1.y || v2.y == v1.y;
        int segment_height = second_half ? v3.y - v2.y : v2.y - v1.y;
        float alpha = (float)i / total_height;
        float beta = (float)(i - (second_half ? v2.y - v1.y : 0)) / segment_height;
        Vec3i A = v1 + (v3 - v1) * alpha;
        Vec3i B = second_half ? v2 + (v3 - v2) * beta : v1 + (v2 - v1) * beta;
        if (A.x > B.x)
            std::swap(A, B);

        // 下面这个是不对的，会有浮点数的误差，导致出现一些白点
        // DrawLine(Vec3i(A.x, v1.y + i, 0), Vec3i(B.x, v1.y + i, 0), color);
        for (int j = A.x; j <= B.x; ++j)
            ((FrameBuffer *)buffer)->SetPixelColor(j, v1.y + i, color);
    }
}

void DrawTriangleWithDepthInfo(Vec3f *v, Vec4f &color, const void *buffer, const SRendererType &type)
{
    switch (type)
    {
        /*     case SRendererType::SLine:
                DrawTriangleLineModeWithoutDepthInfo(v1, v2, v3, color, buffer);
                break; */
    case SRendererType::SFill:
        DrawTriangleFillModeWithDepthInfo(v, color, buffer);
        break;
    default:
        std::cout << "invalid RendererType!";
        break;
    }
}

void DrawTriangleFillModeWithDepthInfo(Vec3f *v, Vec4f &color, const void *buffer)
{
    // version 2
    Vec2i boxMax;
    Vec2i boxMin;
    // find the box that the triangle is inside
    boxMax.x = Max(v[0].x, v[1].x, v[2].x);
    boxMax.y = Max(v[0].y, v[1].y, v[2].y);
    boxMin.x = Min(v[0].x, v[1].x, v[2].x);
    boxMin.y = Min(v[0].y, v[1].y, v[2].y);

    for (int x = boxMin.x; x <= boxMax.x; ++x)
    {
        for (int y = boxMin.y; y <= boxMax.y; ++y)
        {
            Vec3f bcScreen = VecGetBaryCentric(v[0], v[1], v[2], Vec3f(x + 0.5f, y + 0.5f, 0.0f));
            if (bcScreen.x < 0 || bcScreen.y < 0 || bcScreen.z < 0)
                continue;
            float z = 1.0f / (bcScreen.u / v[0].z + bcScreen.v / v[1].z + bcScreen.w / v[2].z);
            if (((FrameBuffer *)buffer)->GetPixelDepth(x, y) < z)
            {
                ((FrameBuffer *)buffer)->SetPixelDepth(x, y, z);
                ((FrameBuffer *)buffer)->SetPixelColor(x, y, color);
            }
        }
    }
}

// use the uniform vertices intensity (float intensity)
void DrawTriangleFillModeWithDepthTexture(Vec3f *v, float intensity, Vec2f *texCoords, const Texture2D &texture, const void *buffer)
{
    // version 2
    Vec2i boxMax;
    Vec2i boxMin;
    // find the box that the triangle is inside
    boxMax.x = Max(v[0].x, v[1].x, v[2].x);
    boxMax.y = Max(v[0].y, v[1].y, v[2].y);
    boxMin.x = Min(v[0].x, v[1].x, v[2].x);
    boxMin.y = Min(v[0].y, v[1].y, v[2].y);

    for (int x = boxMin.x; x <= boxMax.x; ++x)
    {
        for (int y = boxMin.y; y <= boxMax.y; ++y)
        {
            if (x >= screenWidth || y >= screenHeight || x < 0 || y < 0)
                continue;
            Vec3f bcScreen = VecGetBaryCentric(v[0], v[1], v[2], Vec3f(x + 0.5f, y + 0.5f, 0.0f));
            if (bcScreen.x < 0 || bcScreen.y < 0 || bcScreen.z < 0)
                continue;
            float zt = 1.0f / (bcScreen.u / v[0].z + bcScreen.v / v[1].z + bcScreen.w / v[2].z);
            Vec2f texel = (bcScreen.u * texCoords[0] / v[0].z + bcScreen.v * texCoords[1] / v[1].z + bcScreen.w * texCoords[2] / v[2].z) * zt;

            if (((FrameBuffer *)buffer)->GetPixelDepth(x, y) < zt)
            {
                Vec4f color = texture.SampleTexture(texel);
                color.r *= intensity;
                color.g *= intensity;
                color.b *= intensity;
                // std::cout << P << std::endl;
                ((FrameBuffer *)buffer)->SetPixelDepth(x, y, zt);
                ((FrameBuffer *)buffer)->SetPixelColor(x, y, color);
            }
        }
    }
}

// use the vertices normals and vertices intensity (float *intensity)
void DrawTriangleFillModeWithDepthTexture(Vec3f *v, float *intensity, Vec2f *texCoords, const Texture2D &texture, const void *buffer)
{
    // version 2
    Vec2i boxMax;
    Vec2i boxMin;
    // find the box that the triangle is inside
    boxMax.x = Max(v[0].x, v[1].x, v[2].x);
    boxMax.y = Max(v[0].y, v[1].y, v[2].y);
    boxMin.x = Min(v[0].x, v[1].x, v[2].x);
    boxMin.y = Min(v[0].y, v[1].y, v[2].y);

    for (int x = boxMin.x; x <= boxMax.x; ++x)
    {
        for (int y = boxMin.y; y <= boxMax.y; ++y)
        {
            if (x >= screenWidth || y >= screenHeight || x < 0 || y < 0)
                continue;
            Vec3f bcScreen = VecGetBaryCentric(v[0], v[1], v[2], Vec3f(x + 0.5f, y + 0.5f, 0.0f));
            if (bcScreen.x < 0 || bcScreen.y < 0 || bcScreen.z < 0)
                continue;
            float zt = 1.0f / (bcScreen.u / v[0].z + bcScreen.v / v[1].z + bcScreen.w / v[2].z);
            Vec2f texel = (bcScreen.u * texCoords[0] / v[0].z + bcScreen.v * texCoords[1] / v[1].z + bcScreen.w * texCoords[2] / v[2].z) * zt;
            float intensityP = (bcScreen.u * intensity[0] / v[0].z + bcScreen.v * intensity[1] / v[1].z + bcScreen.w * intensity[2] / v[2].z) * zt;
            intensityP = (intensityP > 1.f ? 1.f : (intensityP < 0.f ? 0.f : intensityP));
            if (((FrameBuffer *)buffer)->GetPixelDepth(x, y) < zt)
            {
                Vec4f color = texture.SampleTexture(texel);
                /*  color.r *= intensityP;
                 color.g *= intensityP;
                 color.b *= intensityP; */
                color.r = intensityP;
                color.g = intensityP;
                color.b = intensityP;
                // std::cout << P << std::endl;
                ((FrameBuffer *)buffer)->SetPixelDepth(x, y, zt);
                ((FrameBuffer *)buffer)->SetPixelColor(x, y, color);
            }
        }
    }
}

void DrawTriangleWithShader(Vec3f *v, Shader *shader, const void *buffer)
{
    // version 2
    Vec2i boxMax;
    Vec2i boxMin;
    // find the box that the triangle is inside
    boxMax.x = Max(v[0].x, v[1].x, v[2].x);
    boxMax.y = Max(v[0].y, v[1].y, v[2].y);
    boxMin.x = Min(v[0].x, v[1].x, v[2].x);
    boxMin.y = Min(v[0].y, v[1].y, v[2].y);
    Vec4f color;
    for (int x = boxMin.x; x <= boxMax.x; ++x)
    {
        for (int y = boxMin.y; y <= boxMax.y; ++y)
        {
            if (x >= screenWidth || y >= screenHeight || x < 0 || y < 0)
                continue;
            Vec3f bcScreen = VecGetBaryCentric(v[0], v[1], v[2], Vec3f(x + 0.5f, y + 0.5f, 0.0f));
            float zt = 1.0f / (bcScreen.u / v[0].z + bcScreen.v / v[1].z + bcScreen.w / v[2].z);

            if (bcScreen.x < 0 || bcScreen.y < 0 || bcScreen.z < 0 || ((FrameBuffer *)buffer)->GetPixelDepth(x, y) >= zt)
                continue;
            v2f fsData;
            fsData.oneDivideZ = {1.0f / v[0].z, 1.0f / v[1].z, 1.0f / v[2].z};
            fsData.triangleCoeff = bcScreen;
            fsData.oneDividepixelZ = 1.0f / zt;

            bool discard = shader->FragmentShader(&fsData, color);

            // float intensityP = (bcScreen.u * intensity[0] / v[0].z + bcScreen.v * intensity[1] / v[1].z + bcScreen.w * intensity[2] / v[2].z) * zt;
            // intensityP = (intensityP > 1.f ? 1.f : (intensityP < 0.f ? 0.f : intensityP));
            if (!discard)
            {
                ((FrameBuffer *)buffer)->SetPixelDepth(x, y, zt);
                ((FrameBuffer *)buffer)->SetPixelColor(x, y, color);
            }
        }
    }
}
