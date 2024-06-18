#include "DrawTriangle.h"
#include "Render/FrameBuffer.h"
#include "DrawLine.h"
void DrawTriangleWithoutDepthInfo(Vec2i v1, Vec2i v2, Vec2i v3, const Vec4f &color, const void *buffer, const SRendererType &type)
{
    DrawTriangleWithoutDepthInfo(Vec3i(v2.x, v2.y, 0), Vec3i(v3.x, v3.y, 0), Vec3i(v1.x, v1.y, 0), color, buffer, type);
}

void DrawTriangleWithoutDepthInfo(Vec3i v1, Vec3i v2, Vec3i v3, const Vec4f &color, const void *buffer, const SRendererType &type)
{
    switch (type)
    {
    case SRendererType::SLine:
        DrawTriangleLineModeWithoutDepthInfo(v1, v2, v3, color, buffer);
        break;
    case SRendererType::SFill:
        DrawTriangleFillModeWithoutDepthInfo(v1, v2, v3, color, buffer);
        break;
    default:
        std::cout << "invalid RendererType!";
        break;
    }
}

void DrawTriangleLineModeWithoutDepthInfo(Vec3i &v1, Vec3i &v2, Vec3i &v3, const Vec4f &color, const void *buffer)
{
    DrawLineNaive(v1, v2, color, buffer);
    DrawLineNaive(v2, v3, color, buffer);
    DrawLineNaive(v3, v1, color, buffer);
}

void DrawTriangleFillModeWithoutDepthInfo(Vec3i &v1, Vec3i &v2, Vec3i &v3, const Vec4f &color, const void *buffer)
{
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

void DrawTriangleWithDepthInfo(Vec2i v1, Vec2i v2, Vec2i v3, Vec4f &color, const void *buffer, const SRendererType &type)
{
    DrawTriangleWithDepthInfo(Vec3i(v2.x, v2.y, 0.0f), Vec3i(v3.x, v3.y, 0.0f), Vec3i(v1.x, v1.y, 0.0f), color, buffer, type);
}

void DrawTriangleWithDepthInfo(Vec2f v1, Vec2f v2, Vec2f v3, Vec4f &color, const void *buffer, const SRendererType &type)
{
    DrawTriangleWithDepthInfo(Vec3f(v2.x, v2.y, 0.0f), Vec3f(v3.x, v3.y, 0.0f), Vec3f(v1.x, v1.y, 0.0f), color, buffer, type);
}

void DrawTriangleWithDepthInfo(Vec3i v1, Vec3i v2, Vec3i v3, Vec4f &color, const void *buffer, const SRendererType &type)
{
    switch (type)
    {
        /*     case SRendererType::SLine:
                DrawTriangleLineModeWithoutDepthInfo(v1, v2, v3, color, buffer);
                break; */
    case SRendererType::SFill:
        DrawTriangleFillModeWithDepthInfo(v1, v2, v3, color, buffer);
        break;
    default:
        std::cout << "invalid RendererType!";
        break;
    }
}

void DrawTriangleWithDepthInfo(Vec3f v1, Vec3f v2, Vec3f v3, Vec4f &color, const void *buffer, const SRendererType &type)
{
    switch (type)
    {
        /*     case SRendererType::SLine:
                DrawTriangleLineModeWithoutDepthInfo(v1, v2, v3, color, buffer);
                break; */
    case SRendererType::SFill:
        DrawTriangleFillModeWithDepthInfo(v1, v2, v3, color, buffer);
        break;
    default:
        std::cout << "invalid RendererType!";
        break;
    }
}

void DrawTriangleFillModeWithDepthInfo(Vec3i &v1, Vec3i &v2, Vec3i &v3, Vec4f &color, const void *buffer)
{
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
        {
            float phi = B.x == A.x ? 1.0f : (float)(j - A.x) / (float)(B.x - A.x);
            Vec3i P = A + (B - A) * phi;
            if (((FrameBuffer *)buffer)->GetPixelDepth(j, v1.y + i) < P.z)
            {
                ((FrameBuffer *)buffer)->SetPixelDepth(j, v1.y + i, P.z);
                ((FrameBuffer *)buffer)->SetPixelColor(j, v1.y + i, color);
            }
        }
    }
}

void DrawTriangleFillModeWithDepthInfo(Vec3f &v1, Vec3f &v2, Vec3f &v3, Vec4f &color, const void *buffer)
{
    // version 2
    Vec2i boxMax;
    Vec2i boxMin;
    // find the box that the triangle is inside
    boxMax.x = Max(v1.x, v2.x, v3.x);
    boxMax.y = Max(v1.y, v2.y, v3.y);
    boxMin.x = Min(v1.x, v2.x, v3.x);
    boxMin.y = Min(v1.y, v2.y, v3.y);
    /* boxMax = VecGetBetween(boxMax, Vec2i(0, 0), Vec2i(m_Width - 1, m_Height - 1));
    boxMin = VecGetBetween(boxMin, Vec2i(0, 0), Vec2i(m_Width - 1, m_Height - 1)); */

    for (int x = boxMin.x; x <= boxMax.x; ++x)
    {
        for (int y = boxMin.y; y <= boxMax.y; ++y)
        {
            Vec3f bcScreen = VecGetBaryCentric(v1, v2, v3, Vec3f(x + 0.5f, y + 0.5f, 0.0f));
            // std::cout << "bcScreen:" << bcScreen << " v1:" << v1 << " v2:" << v2 << " v3:" << v3 << " P:" << P << std::endl;
            if (bcScreen.x < 0 || bcScreen.y < 0 || bcScreen.z < 0)
                continue;
            // float z = bcScreen.u * v1.z + bcScreen.v * v2.z + bcScreen.w * v3.z;
            float z = 1.0f / (bcScreen.u / v1.z + bcScreen.v / v2.z + bcScreen.w / v3.z);
            if (((FrameBuffer *)buffer)->GetPixelDepth(x, y) < z)
            {
                // std::cout << P << std::endl;
                ((FrameBuffer *)buffer)->SetPixelDepth(x, y, z);
                ((FrameBuffer *)buffer)->SetPixelColor(x, y, color);
            }
        }
    }
}
