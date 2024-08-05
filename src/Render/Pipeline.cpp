#include "Pipeline.h"
// #include "UI/window.h"
#include <cmath>
#include <iostream>
#include "imagelabel.h"
#include "MathUtils.h"

Pipeline::Pipeline(int width, int height)
{
    m_config.m_width = width;
    m_config.m_height = height;

    m_config.m_backBuffer = nullptr;
    m_config.m_frontBuffer = nullptr;
    m_config.m_shader = nullptr;
    m_config.m_eyePos = Vec3(0.0f, 0.0f, 0.0f);

    /* m_camera = new NaiveCamera(Vec3({2.0f, 1.0f, 3.0f}));
    m_projectionMat = Mat4x4GetProjectionNaive(m_camera->GetPosition().z);
    m_viewMat = m_camera->GetViewMatrix(); */
}

Pipeline::~Pipeline()
{
    if (m_config.m_backBuffer)
        delete m_config.m_backBuffer;
    if (m_config.m_frontBuffer)
        delete m_config.m_frontBuffer;
    if (m_config.m_shader)
        delete m_config.m_shader;
    for (size_t i = 0; i < m_config.m_textureUnits.size(); ++i)
    {
        delete m_config.m_textureUnits[i];
        m_config.m_textureUnits[i] = nullptr;
    }
    /*  if (m_camera)
         delete m_camera; */

    m_config.m_backBuffer = nullptr;
    m_config.m_frontBuffer = nullptr;
    m_config.m_shader = nullptr;
    /* m_camera = nullptr; */
}

void Pipeline::initialize()
{
    if (m_config.m_backBuffer)
        delete m_config.m_backBuffer;
    if (m_config.m_frontBuffer)
        delete m_config.m_frontBuffer;
    if (m_config.m_shader)
        delete m_config.m_shader;
    // m_config.m_viewPortMat = Mat4x4GetViewportNaive(0.0f, 0.0f, (float)m_config.m_width, (float)m_config.m_height, 255.0f);
    m_config.m_viewPortMat.SetViewPort(0.0f, 0.0f, (float)m_config.m_width, (float)m_config.m_height);
    m_config.m_backBuffer = new FrameBuffer(m_config.m_width, m_config.m_height);
    m_config.m_frontBuffer = new FrameBuffer(m_config.m_width, m_config.m_height);
    m_config.m_shader = new SimpleShader();
    SetDefaultConfig();
}

// void Pipeline::DrawModelPureColor(Model &model, Vec4 &color, const PolygonMode &type)
// {
//     bool flag = true;
//     for (int i = 0; i < model.m_Faces.size(); ++i)
//     {
//         std::vector<Vec3i> face = model.m_Faces[i];
//         Vec3 v[3];
//         for (int j = 0; j < 3; ++j)
//         {
//             v[j] = Vec3(m_config.m_viewPortMat * Vec4(model.m_Vertices[face[j][0]]));
//             /* if (flag)
//             {
//                 std::cout << "DrawModelPureColor" << std::endl;
//                 std::cout << "vertices:" << Vec3ToVec4(model.m_Vertices[face[j][0]]) << std::endl;
//                 std::cout << "viewPortMat: " << m_config.m_viewPortMat << std::endl;
//                 std::cout << "final vertices:" << v[0] << std::endl;
//                 flag = false;
//             } */
//         }
//         DrawTriangleWithoutDepthInfo(v, color, (void *)m_config.m_backBuffer, type);
//     }
// }

// void Pipeline::DrawModelNormalWithoutDepthInfo(Model &model, Vec3 &lightDir, Vec4 &color, const PolygonMode &type)
// {
//     for (int i = 0; i < model.m_Faces.size(); ++i)
//     {
//         Vec3 screenCoord[3];
//         Vec3 worldCoord[3];
//         std::vector<Vec3i> face = model.m_Faces[i];
//         for (int j = 0; j < 3; ++j)
//         {
//             worldCoord[j] = model.m_Vertices[face[j][0]];
//             screenCoord[j] = CoordWorldFloatToScreenFloat(worldCoord[j]);
//         }
//         Vec3 normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
//         // intensity
//         float intensity = VecGetDotProduct(normal, lightDir);
//         if (intensity > 0)
//         {
//             DrawTriangleWithoutDepthInfo(screenCoord, Vec4(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), (void *)m_config.m_backBuffer, type);
//         }
//     }
// }
// void Pipeline::DrawModelNormalWithDepthInfo(Model &model, Vec3 &lightDir, Vec4 &color, const PolygonMode &type)
// {
//     for (int i = 0; i < model.m_Faces.size(); ++i)
//     {
//         Vec3 screenCoord[3];
//         Vec3 worldCoord[3];
//         std::vector<Vec3i> face = model.m_Faces[i];
//         for (int j = 0; j < 3; ++j)
//         {
//             worldCoord[j] = model.m_Vertices[face[j][0]];
//             screenCoord[j] = Vec3(m_config.m_viewPortMat * m_projectionMat * Vec4(worldCoord[j]));
//         }
//         Vec3 normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
//         // intensity
//         float intensity = VecGetDotProduct(normal, lightDir);
//         if (intensity > 0)
//         {
//             DrawTriangleWithDepthInfo(screenCoord, Vec4(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), (void *)m_config.m_backBuffer, type);
//         }
//     }
// }

// void Pipeline::DrawModelWithTextureWithViewMat(Model &model, Vec3 &lightDir, const Texture2D &texture, const PolygonMode &type)
// {
//     for (int i = 0; i < model.m_Faces.size(); ++i)
//     {
//         Vec3 screenCoord[3];
//         Vec3 worldCoord[3];
//         Vec2f texCoords[3];
//         float intensity[3];
//         std::vector<Vec3i> face = model.m_Faces[i];

//         for (int j = 0; j < 3; ++j)
//         {
//             worldCoord[j] = model.m_Vertices[face[j][0]];
//             screenCoord[j] = Vec3(m_config.m_viewPortMat * m_projectionMat * m_viewMat * Vec4(worldCoord[j]));
//             texCoords[j] = model.m_UVCoords[face[j][1]];
//             intensity[j] = VecGetDotProduct(model.m_Normals[face[j][2]], lightDir);
//         }
//         DrawTriangleFillModeWithDepthTexture(screenCoord, intensity, texCoords, texture, (void *)m_config.m_backBuffer);
//     }
// }
// void Pipeline::DrawModelWithTextureWithoutViewMat(Model &model, Vec3 &lightDir, const Texture2D &texture, const PolygonMode &type)
// {

//     for (int i = 0; i < model.m_Faces.size(); ++i)
//     {
//         Vec3 screenCoord[3];
//         Vec3 worldCoord[3];
//         Vec2f texCoords[3];
//         std::vector<Vec3i> face = model.m_Faces[i];
//         for (int j = 0; j < 3; ++j)
//         {
//             worldCoord[j] = model.m_Vertices[face[j][0]];
//             screenCoord[j] = Vec3(m_config.m_viewPortMat * m_projectionMat * Vec4(worldCoord[j]));
//             texCoords[j] = model.m_UVCoords[face[j][1]];
//         }

//         // normal vector，这里obj定义的顶点顺序是逆时针 v1->v2->v3
//         Vec3 normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
//         // intensity
//         float intensity = VecGetDotProduct(normal, lightDir);
//         if (intensity > 0)
//         {
//             DrawTriangleFillModeWithDepthTexture(screenCoord, intensity, texCoords, texture, (void *)m_config.m_backBuffer);
//         }
//     }
// }
// void Pipeline::DrawModelWithShader(DrawData &drawData, const PolygonMode &type)
// {
//     Model *m = drawData.model;
//     Shader *s = drawData.shader;
//     shaderData.cameraViewMat = this->m_viewMat;
//     shaderData.cameraProjectionMat = this->m_projectionMat;
//     shaderData.screenViewportMat = this->m_config.m_viewPortMat;
//     shaderData.modelTransViewMat = shaderData.cameraProjectionMat * shaderData.cameraViewMat * shaderData.modelTransMat;
//     shaderData.modelTransViewMatInv = MatGetInverse(shaderData.modelTransViewMat);
//     for (int i = 0; i < m->m_Faces.size(); ++i)
//     {
//         Vec3 screenCoord[3];
//         for (int j = 0; j < 3; ++j)
//         {
//             screenCoord[j] = s->VertexShader(i, j);
//         }

//         DrawTriangleWithShader(screenCoord, s, (void *)m_config.m_backBuffer);
//     }
// }
// // TODO: representation by ViewPortMatrix

// Vec3 Pipeline::CoordWorldFloatToScreenFloat(Vec3 &v)
// {
//     Vec3 res;
//     res.x = (v.x + 1.0f) * m_config.m_width / 2.0f;
//     res.y = (v.y + 1.0f) * m_config.m_height / 2.0f;
//     res.z = (v.z + 1.0f) * 255.0f / 2.0f;
//     return res;
// }
unsigned int Pipeline::LoadTexture(const std::string &path)
{
    Texture2D *tex = new Texture2D();
    if (!tex->LoadTexture(path))
        return 0;
    m_config.m_textureUnits.push_back(tex);
    return static_cast<unsigned int>(m_config.m_textureUnits.size() - 1);
}
bool Pipeline::BindTexture(const unsigned int &unit)
{
    if (unit >= m_config.m_textureUnits.size())
        return false;
    m_config.m_shader->BindShaderTexture(m_config.m_textureUnits[unit]);
    return true;
}
bool Pipeline::UnBindTexture(const unsigned int &unit)
{
    if (unit >= m_config.m_textureUnits.size())
        return false;
    m_config.m_shader->BindShaderTexture(nullptr);
    return true;
}
void Pipeline::ClearFrameBuffer(const Vec4 &color)
{
    m_config.m_backBuffer->clearColorAndDepthBuffer(color);
}

unsigned char *Pipeline::GetFrameResult()
{
    return m_config.m_frontBuffer->GetColorBuffer();
}

void Pipeline::SwapFrameBuffer()
{
    FrameBuffer *temp = m_config.m_frontBuffer;
    m_config.m_frontBuffer = m_config.m_backBuffer;
    m_config.m_backBuffer = temp;
}

void Pipeline::SetViewMatrix(Vec3 eye, const Mat4x4 &viewMat)
{
    m_config.m_eyePos = eye;
    m_config.m_shader->SetEyePos(eye);
    m_config.m_shader->SetViewMatrix(viewMat);
    m_viewMat = viewMat;
}

void Pipeline::SetViewMatrix(Vec3 eye, Vec3 target, Vec3 up)
{
    m_config.m_eyePos = eye;
    // Mat4x4 viewMat = Mat4x4GetLookAt(eye, target, up);
    m_config.m_shader->SetEyePos(eye);
    m_viewMat.SetLookAt(eye, target, up);
    m_config.m_shader->SetViewMatrix(m_viewMat);
    // m_viewMat = viewMat;
}

void Pipeline::SetProjectMatrix(float fovy, float aspect, float near, float far)
{
    // Mat4x4 projectMat = Mat4x4GetPerspective(fovy, aspect, near, far);
    m_projectionMat.SetPerspective(fovy, aspect, near, far);
    m_config.m_shader->SetProjectMatrix(m_projectionMat);
}

void Pipeline::SetModelMatrix(Mat4x4 modelMatrix)
{
    m_config.m_shader->SetModelMatrix(modelMatrix);
}

void Pipeline::SetShadingMode(ShadingMode mode)
{
    if (m_config.m_shader)
        delete m_config.m_shader;
    m_config.m_shader = nullptr;
    switch (mode)
    {
    case ShadingMode::Simple:
    {
        m_config.m_shader = new SimpleShader();
        break;
    }
    case ShadingMode::Gouraud:
    {
        m_config.m_shader = new GouraudShader();
        break;
    }
    case ShadingMode::Phong:
    {
        m_config.m_shader = new PhongShader();
        break;
    }
    }
}

bool Pipeline::DrawMesh()
{
    if (m_config.m_indices->empty())
        return false;

    // line clipping
    bool line1 = false, line2 = false, line3 = false, line4 = false;
    for (unsigned int i = 0; i < m_config.m_indices->size(); i += 3)
    {
        // assemble to a triangle primitive
        Vertex p1, p2, p3;
        {
            p1 = (*m_config.m_vertices)[(*m_config.m_indices)[i + 0]];
            p2 = (*m_config.m_vertices)[(*m_config.m_indices)[i + 1]];
            p3 = (*m_config.m_vertices)[(*m_config.m_indices)[i + 2]];
        }

        // vertex shader stage
        VertexOut v1, v2, v3;
        {
            v1 = m_config.m_shader->vertexShader(p1);
            v2 = m_config.m_shader->vertexShader(p2);
            v3 = m_config.m_shader->vertexShader(p3);
        }

        // todo: back face culling
        // todo: geometry clipping

        // perspective division
        {
            perspectiveDivision(v1);
            perspectiveDivision(v2);
            perspectiveDivision(v3);
        }

        // view port transformation
        {
            // 如果m_viewPortMat的(2,2)元素反转了，那么Texture和depthBuffer的元素不用反转
            v1.posProj = m_config.m_viewPortMat * v1.posProj;
            v2.posProj = m_config.m_viewPortMat * v2.posProj;
            v3.posProj = m_config.m_viewPortMat * v3.posProj;
        }

        // rasterization and fragment shader stage
        {
            if (m_config.m_polygonMode == PolygonMode::Wire)
            {
                if (!line1)
                    bresenhamLineRasterization(v1, v2);
                if (!line2)
                    bresenhamLineRasterization(v2, v3);
                if (!line3)
                    bresenhamLineRasterization(v3, v1);
            }
            else if (m_config.m_polygonMode == PolygonMode::Fill)
            {
                edgeWalkingFillRasterization(v1, v2, v3);
            }
        }
    }
}

void Pipeline::perspectiveDivision(VertexOut &target)
{
    target.posProj.x /= target.posProj.w;
    target.posProj.y /= target.posProj.w;
    target.posProj.z /= target.posProj.w;
    target.posProj.w = 1.0f;
    // map from [-1, 1] to [0, 1]
    target.posProj.z = (target.posProj.z + 1.0f) * 0.5f;
}

VertexOut Pipeline::lerp(const VertexOut &n1, const VertexOut &n2, double weight)
{
    VertexOut result;
    result.posProj = n1.posProj.GetLerp(n2.posProj, weight);
    result.posWorld = n1.posWorld.GetLerp(n2.posWorld, weight);
    result.color = n1.color.GetLerp(n2.color, weight);
    result.normal = n1.normal.GetLerp(n2.normal, weight);
    result.texcoord = n1.texcoord.GetLerp(n2.texcoord, weight);
    result.oneDivZ = (1.0 - weight) * n1.oneDivZ + weight * n2.oneDivZ;
    return result;
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// https://liolok.com/zhs/bresenham-line-algorithm-and-decision-parameter/
void Pipeline::bresenhamLineRasterization(const VertexOut &from, const VertexOut &to)
{
    int dx = to.posProj.x - from.posProj.x;
    int dy = to.posProj.y - from.posProj.y;
    int stepX = 1, stepY = 1;
    // 保证dx和dy都是正的，用来判断斜率，不用除法
    if (dx < 0)
    {
        stepX = -1;
        dx = -dx;
    }
    if (dy < 0)
    {
        stepY = -1;
        dy = -dy;
    }
    int d2x = 2 * dx, d2y = 2 * dy;
    int d2y_minus_d2x = d2y - d2x;
    int sx = from.posProj.x;
    int sy = from.posProj.y;

    VertexOut tmp;
    // slop < 1

    if (dy < dx)
    {
        int flag = d2y - dx;
        for (int i = 0; i < dx; ++i)
        {
            // linear interpolation
            tmp = lerp(from, to, static_cast<float>(i) / dx);
            float depth = m_config.m_backBuffer->GetPixelDepth(sx, sy);
            if (tmp.posProj.z > depth)
                continue; // fail to pass the depth testing
            m_config.m_backBuffer->SetPixelDepth(sx, sy, tmp.posProj.z);
            // fragment shader
            m_config.m_backBuffer->SetPixelColor(sx, sy, m_config.m_shader->fragmentShader(tmp));
            sx += stepX;
            if (flag <= 0)
                flag += d2y;
            else
            {
                sy += stepY;
                flag += d2y_minus_d2x;
            }
        }
    }
    else
    {
        int flag = d2x - dy;
        for (int i = 0; i < dy; ++i)
        {
            tmp = lerp(from, to, static_cast<float>(i) / dy);
            float depth = m_config.m_backBuffer->GetPixelDepth(sx, sy);
            if (tmp.posProj.z > depth)
                continue; // fail to pass the depth testing
            m_config.m_backBuffer->SetPixelDepth(sx, sy, tmp.posProj.z);

            // fragment shader
            m_config.m_backBuffer->SetPixelColor(sx, sy, m_config.m_shader->fragmentShader(tmp));
            sy += stepY;
            if (flag <= 0)
                flag += d2x;
            else
            {
                sx += stepX;
                flag -= d2y_minus_d2x;
            }
        }
    }
}
void Pipeline::scanLinePerRow(const VertexOut &left, const VertexOut &right)
{
    // scan the line from left to right
    VertexOut current;
    int length = right.posProj.x - left.posProj.x + 1;
    for (int i = 0; i <= length; ++i)
    {
        float weight = static_cast<float>(i) / length;
        current = lerp(left, right, weight);
        current.posProj.x = left.posProj.x + i;
        current.posProj.y = left.posProj.y;

        // depth testing
        if (m_config.m_depthTesting)
        {
            float depth = m_config.m_backBuffer->GetPixelDepth(current.posProj.x, current.posProj.y);
            if (current.posProj.z > depth)
                continue; // fail to pass the depth testing
            m_config.m_backBuffer->SetPixelDepth(current.posProj.x, current.posProj.y, current.posProj.z);
        }
        if (current.posProj.x < 0 || current.posProj.y < 0)
            continue;
        if (current.posProj.x >= m_config.m_width || current.posProj.y >= m_config.m_height)
            break;
        float w = 1.0f / current.oneDivZ;
        current.posWorld *= w;
        current.color *= w;
        current.texcoord *= w;
        // fragment shader
        m_config.m_backBuffer->SetPixelColor(current.posProj.x, current.posProj.y, m_config.m_shader->fragmentShader(current));
    }
}
void Pipeline::rasterTopTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3)
{
    VertexOut left = v2;
    VertexOut right = v3;
    VertexOut dest = v1;
    VertexOut tmp, newleft, newright;
    if (left.posProj.x > right.posProj.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = left.posProj.y - dest.posProj.y + 1;

    for (int i = 0; i < dy; ++i)
    {
        float weight = 0;
        if (dy != 0)
            weight = static_cast<float>(i) / dy;
        newleft = lerp(left, dest, weight);
        newright = lerp(right, dest, weight);
        newleft.posProj.y = newright.posProj.y = left.posProj.y - i;
        scanLinePerRow(newleft, newright);
    }
}
void Pipeline::rasterBottomTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3)
{
    VertexOut left = v1;
    VertexOut right = v2;
    VertexOut dest = v3;
    VertexOut tmp, newleft, newright;
    if (left.posProj.x > right.posProj.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = dest.posProj.y - left.posProj.y + 1;

    for (int i = 0; i < dy; ++i)
    {
        float weight = 0;
        if (dy != 0)
            weight = static_cast<float>(i) / dy;
        newleft = lerp(left, dest, weight);
        newright = lerp(right, dest, weight);
        newleft.posProj.y = newright.posProj.y = left.posProj.y + i;
        scanLinePerRow(newleft, newright);
    }
}
void Pipeline::edgeWalkingFillRasterization(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3)
{
    // split the triangle into two parts
    VertexOut tmp;
    VertexOut target[3] = {v1, v2, v3};
    // vertexOut[0].y < vertexOut[1].y < vertexOut[2].y
    //*
    // ** vertexOut[0]
    //  * *
    //   *  *
    //    *  *  vertexOut[1]
    //     *  vertexOut[2]

    if (target[0].posProj.y > target[1].posProj.y)
    {
        tmp = target[0];
        target[0] = target[1];
        target[1] = tmp;
    }
    if (target[0].posProj.y > target[2].posProj.y)
    {
        tmp = target[0];
        target[0] = target[2];
        target[2] = tmp;
    }
    if (target[1].posProj.y > target[2].posProj.y)
    {
        tmp = target[1];
        target[1] = target[2];
        target[2] = tmp;
    }
    // bottom triangle
    if (Equal(target[0].posProj.y, target[1].posProj.y))
    {
        rasterBottomTriangle(target[0], target[1], target[2]);
    }
    else if (Equal(target[1].posProj.y, target[2].posProj.y))
    {
        rasterTopTriangle(target[0], target[1], target[2]);
    }
    else
    {
        float weight = static_cast<float>(target[1].posProj.y - target[0].posProj.y) / (target[2].posProj.y - target[0].posProj.y);
        VertexOut newPoint = lerp(target[0], target[2], weight);

        rasterTopTriangle(target[0], newPoint, target[1]);
        rasterBottomTriangle(newPoint, target[1], target[2]);
    }
}
void Pipeline::SetDefaultConfig()
{
    SetDepthTesting(true);
    SetBackFaceCulling(true);
    SetGeometryClipping(true);
    // SetPolygonMode(PolygonMode::Fill);
}
