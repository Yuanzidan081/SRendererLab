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
    m_config.m_viewPlaneParameters.resize(6, Vec4());
    m_config.m_viewLineParameters = {
        Vec3(-1, 0, -1),
        Vec3(0, 1, -1),
        Vec3(1, 0, -1),
        Vec3(0, -1, -1)};
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
    m_viewMatrix = viewMat;
    m_config.m_shader->SetViewMatrix(viewMat);
}

void Pipeline::SetViewMatrix(Vec3 eye, Vec3 target, Vec3 up)
{
    m_config.m_eyePos = eye;
    m_config.m_shader->SetEyePos(eye);
    m_viewMatrix.SetLookAt(eye, target, up);
    m_config.m_shader->SetViewMatrix(m_viewMatrix);
}

void Pipeline::SetProjectMatrix(float fovy, float aspect, float near, float far)
{
    m_projectMatrix.SetPerspective(fovy, aspect, near, far);
    m_config.m_shader->SetProjectMatrix(m_projectMatrix);
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
    // unsigned int cnt = 0;
    UpdateViewPlanes();
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
        // view culling
        if (!ViewCulling(v1.posWorld / v1.oneDivZ, v2.posWorld / v2.oneDivZ, v3.posWorld / v3.oneDivZ))
        {
            // cnt++;
            continue;
        }
        // geometry clipping
        {
            if (m_config.m_geometryClipping)
            {
                if (m_config.m_polygonMode == PolygonMode::Wire)
                {
                    line1 = LineClipping(v1, v2);
                    line2 = LineClipping(v2, v3);
                    line3 = LineClipping(v3, v1);
                }
                else if (m_config.m_polygonMode == PolygonMode::Fill && !TriangleClipping(v1, v2, v3))
                    continue;
            }
        }
        // perspective division
        {
            PerspectiveDivision(v1);
            PerspectiveDivision(v2);
            PerspectiveDivision(v3);
        }
#if 0

        // back face culling
        {
            if (m_config.m_backFaceCulling)
            {
                if (!BackFaceClipping(v1.posProj, v2.posProj, v3.posProj))
                    continue;
            }
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
                    BresenhamLineRasterization(v1, v2);
                if (!line2)
                    BresenhamLineRasterization(v2, v3);
                if (!line3)
                    BresenhamLineRasterization(v3, v1);
            }
            else if (m_config.m_polygonMode == PolygonMode::Fill)
            {
                EdgeWalkingFillRasterization(v1, v2, v3);
            }
        }
#else
        std::vector<VertexOut> clippingVertexs = SutherlandHodgeman(v1, v2, v3);
        int n = clippingVertexs.size() - 3 + 1; // the number of the clipping triangles
        for (int i = 0; i < n; ++i)
        {
            VertexOut v1 = clippingVertexs[0];
            VertexOut v2 = clippingVertexs[i + 1];
            VertexOut v3 = clippingVertexs[i + 2];
            // back face culling
            {
                if (m_config.m_backFaceCulling)
                {
                    if (!BackFaceClipping(v1.posProj, v2.posProj, v3.posProj))
                        continue;
                }
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
                        BresenhamLineRasterization(v1, v2);
                    if (!line2)
                        BresenhamLineRasterization(v2, v3);
                    if (!line3)
                        BresenhamLineRasterization(v3, v1);
                }
                else if (m_config.m_polygonMode == PolygonMode::Fill)
                {
                    EdgeWalkingFillRasterization(v1, v2, v3);
                }
            }
        }

#endif
    }
}

void Pipeline::PerspectiveDivision(VertexOut &target)
{
    target.posProj.x /= target.posProj.w;
    target.posProj.y /= target.posProj.w;
    target.posProj.z /= target.posProj.w;
    target.posProj.w = 1.0f;
    // map from [-1, 1] to [0, 1]
    target.posProj.z = (target.posProj.z + 1.0f) * 0.5f;
}

VertexOut Pipeline::Lerp(const VertexOut &n1, const VertexOut &n2, double weight)
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

bool Pipeline::LineClipping(const VertexOut &from, const VertexOut &to)
{
    // true:clip;
    // false: not clip.
    float vMin = -from.posProj.w, vMax = from.posProj.w;
    float x1 = from.posProj.x, y1 = from.posProj.y;
    float x2 = to.posProj.x, y2 = to.posProj.y;

    int tmp = 0;
    int outcode1 = 0;
    int outcode2 = 0;

    // outcode1 calculation
    tmp = (y1 > vMax) ? 1 : 0;
    tmp <<= 3;
    outcode1 |= tmp;
    tmp = (y1 < vMin) ? 1 : 0;
    tmp <<= 2;
    outcode1 |= tmp;
    tmp = (x1 > vMax) ? 1 : 0;
    tmp <<= 1;
    outcode1 |= tmp;
    tmp = (x1 < vMin) ? 1 : 0;
    tmp <<= 0;
    outcode1 |= tmp;

    // outcode2 calculation
    tmp = (y2 > vMax) ? 1 : 0;
    tmp <<= 3;
    outcode2 |= tmp;
    tmp = (y2 < vMin) ? 1 : 0;
    tmp <<= 2;
    outcode2 |= tmp;
    tmp = (x2 > vMax) ? 1 : 0;
    tmp <<= 1;
    outcode2 |= tmp;
    tmp = (x2 < vMin) ? 1 : 0;
    tmp <<= 0;
    outcode2 |= tmp;

    if ((outcode1 & outcode2) != 0)
        return true;

    // bounding box
    Vec2 minPoint, maxPoint;
    minPoint.x = std::min(from.posProj.x, to.posProj.x);
    minPoint.y = std::min(from.posProj.y, to.posProj.y);
    maxPoint.x = std::max(from.posProj.x, to.posProj.x);
    maxPoint.y = std::max(from.posProj.y, to.posProj.y);
    if (minPoint.x > vMax || maxPoint.x < vMin || minPoint.y > vMax || maxPoint.y < vMin)
        return true;
    return false;
}

bool Pipeline::TriangleClipping(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3)
{
    // true:not clip;
    // false: clip.
    float vMin = -v1.posProj.w;
    float vMax = +v1.posProj.w;

    // if the triangle is too far to see it, just return false.
    if (v1.posProj.z > vMax && v2.posProj.z > vMax && v3.posProj.z > vMax)
        return false;

    // if the triangle is behind the camera, just return false.
    if (v1.posProj.z < vMin && v2.posProj.z < vMin && v3.posProj.z < vMin)
        return false;

    // calculate the bounding box and check if clip or not.
    Vec2 minPoint, maxPoint;
    minPoint.x = min(v1.posProj.x, min(v2.posProj.x, v3.posProj.x));
    minPoint.y = min(v1.posProj.y, min(v2.posProj.y, v3.posProj.y));
    maxPoint.x = max(v1.posProj.x, max(v2.posProj.x, v3.posProj.x));
    maxPoint.y = max(v1.posProj.y, max(v2.posProj.y, v3.posProj.y));
    if (minPoint.x > vMax || maxPoint.x < vMin || minPoint.y > vMax || maxPoint.y < vMin)
        return false;

    return true;
}

bool Pipeline::BackFaceClipping(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3)
{
    if (m_config.m_polygonMode == PolygonMode::Wire)
        return true;
    Vec3 edge1(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
    Vec3 edge2(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
    Vec3 viewRay(0, 0, 1);
    Vec3 normal = edge1.GetCrossProduct(edge2);
    return viewRay.GetDotProduct(normal) > 0;
}

bool Pipeline::ViewCulling(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3)
{
    Vec3 minPoint, maxPoint;
    minPoint.x = min(v1.x, min(v2.x, v3.x));
    minPoint.y = min(v1.y, min(v2.y, v3.y));
    minPoint.z = min(v1.z, min(v2.z, v3.z));
    maxPoint.x = max(v1.x, max(v2.x, v3.x));
    maxPoint.y = max(v1.y, max(v2.y, v3.y));
    maxPoint.z = max(v1.z, max(v2.z, v3.z));
    // Near 和 Far culling: save the point inside
    if (!IsInsideFrustum(minPoint, m_config.m_viewPlaneParameters[4]) && !IsInsideFrustum(maxPoint, m_config.m_viewPlaneParameters[4]))
        return false;
    if (!IsInsideFrustum(minPoint, m_config.m_viewPlaneParameters[5]) && !IsInsideFrustum(maxPoint, m_config.m_viewPlaneParameters[5]))
        return false;
    if (!IsInsideFrustum(minPoint, m_config.m_viewPlaneParameters[0]) && !IsInsideFrustum(maxPoint, m_config.m_viewPlaneParameters[0]))
        return false;
    if (!IsInsideFrustum(minPoint, m_config.m_viewPlaneParameters[1]) && !IsInsideFrustum(maxPoint, m_config.m_viewPlaneParameters[1]))
        return false;
    if (!IsInsideFrustum(minPoint, m_config.m_viewPlaneParameters[2]) && !IsInsideFrustum(maxPoint, m_config.m_viewPlaneParameters[2]))
        return false;
    if (!IsInsideFrustum(minPoint, m_config.m_viewPlaneParameters[3]) && !IsInsideFrustum(maxPoint, m_config.m_viewPlaneParameters[3]))
        return false;
    return true;
}

void Pipeline::UpdateViewPlanes()
{
    ViewingFrustumPlanes(m_config.m_viewPlaneParameters, m_projectMatrix * m_viewMatrix);
}

// get six frusum's  planes to use for frustum culling
// all the normal vectors of the frustum planes are toward the inside of the frustum
void Pipeline::ViewingFrustumPlanes(std::vector<Vec4> &planeParameter, const Mat4x4 &vp)
{

    // left plane
    planeParameter[0].x = vp[0][3] + vp[0][0];
    planeParameter[0].y = vp[1][3] + vp[1][0];
    planeParameter[0].z = vp[2][3] + vp[2][0];
    planeParameter[0].w = vp[3][3] + vp[3][0];
    // right plane
    planeParameter[1].x = vp[0][3] - vp[0][0];
    planeParameter[1].y = vp[1][3] - vp[1][0];
    planeParameter[1].z = vp[2][3] - vp[2][0];
    planeParameter[1].w = vp[3][3] - vp[3][0];
    // top plane
    planeParameter[2].x = vp[0][3] - vp[0][1];
    planeParameter[2].y = vp[1][3] - vp[1][1];
    planeParameter[2].z = vp[2][3] - vp[2][1];
    planeParameter[2].w = vp[3][3] - vp[3][1];
    // bottom plane
    planeParameter[3].x = vp[0][3] + vp[0][1];
    planeParameter[3].y = vp[1][3] + vp[1][1];
    planeParameter[3].z = vp[2][3] + vp[2][1];
    planeParameter[3].w = vp[3][3] + vp[3][1];
    // near plane
    planeParameter[4].x = vp[0][3] + vp[0][2];
    planeParameter[4].y = vp[1][3] + vp[1][2];
    planeParameter[4].z = vp[2][3] + vp[2][2];
    planeParameter[4].w = vp[3][3] + vp[3][2];
    // far plane
    planeParameter[5].x = vp[0][3] - vp[0][2];
    planeParameter[5].y = vp[1][3] - vp[1][2];
    planeParameter[5].z = vp[2][3] - vp[2][2];
    planeParameter[5].w = vp[3][3] - vp[3][2];
}

// the distance of the point to the plane d = Ax + By + Cz + D
// d < 0 point is outside the frustum
// d > 0 point is inside the frustum
// d = 0 point is on the planes of the frustum
// https://www8.cs.umu.se/kurser/5DV180/VT18/lab/plane_extraction.pdf
bool Pipeline::IsInsideFrustum(const Vec3 &v, const Vec4 &planePrameter)
{
    return planePrameter.x * v.x + planePrameter.y * v.y + planePrameter.z * v.z + planePrameter.w >= 0;
}

bool Pipeline::IsInsideViewPort(const Vec3 &lineParameter, const Vec4 &p)
{
    return lineParameter.x * p.x + lineParameter.y * p.y + lineParameter.z * p.z < 0;
}

bool Pipeline::IsAllVertexsInsideViewPort(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3)
{
    // outside the ndc
    if (v1.x > 1 || v1.x < -1)
        return false;
    if (v1.y > 1 || v1.y < -1)
        return false;
    if (v2.x > 1 || v2.x < -1)
        return false;
    if (v2.y > 1 || v2.y < -1)
        return false;
    if (v3.x > 1 || v3.x < -1)
        return false;
    if (v3.y > 1 || v3.y < -1)
        return false;
    return true;
}

VertexOut Pipeline::GetViewPortIntersect(const VertexOut &out, const VertexOut &in, const Vec3 &lineParameter)
{
    if (lineParameter.x == -1)
    {
        float weight = (-1 - out.posProj.x) / (in.posProj.x - out.posProj.x);
        return Lerp(out, in, weight);
    }
    if (lineParameter.x == 1)
    {
        float weight = (1 - out.posProj.x) / (in.posProj.x - out.posProj.x);
        return Lerp(out, in, weight);
    }
    if (lineParameter.y == -1)
    {
        float weight = (-1 - out.posProj.y) / (in.posProj.y - out.posProj.y);
        return Lerp(out, in, weight);
    }
    if (lineParameter.y == 1)
    {
        float weight = (1 - out.posProj.y) / (in.posProj.y - out.posProj.y);
        return Lerp(out, in, weight);
    }
}

std::vector<VertexOut> Pipeline::SutherlandHodgeman(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3)
{
    std::vector<VertexOut> output = {v1, v2, v3};
    if (IsAllVertexsInsideViewPort(v1.posProj, v2.posProj, v3.posProj))
        return output;
    for (int i = 0; i < 4; ++i)
    {
        std::vector<VertexOut> input(output);
        output.clear();
        for (int j = 0; j < input.size(); ++j)
        {
            VertexOut cur = input[j];
            VertexOut pre = input[(j + input.size() - 1) % input.size()];
            if (IsInsideViewPort(m_config.m_viewLineParameters[i], cur.posProj))
            {
                if (!IsInsideViewPort(m_config.m_viewLineParameters[i], pre.posProj))
                {
                    VertexOut intersecting = GetViewPortIntersect(pre, cur, m_config.m_viewLineParameters[i]);
                    output.push_back(intersecting);
                }
                output.push_back(cur);
            }
            else if (IsInsideViewPort(m_config.m_viewLineParameters[i], pre.posProj))
            {
                VertexOut intersecting = GetViewPortIntersect(cur, pre, m_config.m_viewLineParameters[i]);
                output.push_back(intersecting);
            }
        }
    }
    return output;
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// https://liolok.com/zhs/bresenham-line-algorithm-and-decision-parameter/
void Pipeline::BresenhamLineRasterization(const VertexOut &from, const VertexOut &to)
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
            tmp = Lerp(from, to, static_cast<float>(i) / dx);
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
            tmp = Lerp(from, to, static_cast<float>(i) / dy);
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
void Pipeline::ScanLinePerRow(const VertexOut &left, const VertexOut &right)
{
    // scan the line from left to right
    VertexOut current;
    int length = right.posProj.x - left.posProj.x + 1;
    for (int i = 0; i <= length; ++i)
    {
        float weight = static_cast<float>(i) / length;
        current = Lerp(left, right, weight);
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
void Pipeline::RasterTopTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3)
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
        newleft = Lerp(left, dest, weight);
        newright = Lerp(right, dest, weight);
        newleft.posProj.y = newright.posProj.y = left.posProj.y - i;
        ScanLinePerRow(newleft, newright);
    }
}
void Pipeline::RasterBottomTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3)
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
        newleft = Lerp(left, dest, weight);
        newright = Lerp(right, dest, weight);
        newleft.posProj.y = newright.posProj.y = left.posProj.y + i;
        ScanLinePerRow(newleft, newright);
    }
}
void Pipeline::EdgeWalkingFillRasterization(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3)
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
        RasterBottomTriangle(target[0], target[1], target[2]);
    }
    else if (Equal(target[1].posProj.y, target[2].posProj.y))
    {
        RasterTopTriangle(target[0], target[1], target[2]);
    }
    else
    {
        float weight = static_cast<float>(target[1].posProj.y - target[0].posProj.y) / (target[2].posProj.y - target[0].posProj.y);
        VertexOut newPoint = Lerp(target[0], target[2], weight);

        RasterTopTriangle(target[0], newPoint, target[1]);
        RasterBottomTriangle(newPoint, target[1], target[2]);
    }
}
void Pipeline::SetDefaultConfig()
{
    SetDepthTesting(true);
    SetBackFaceCulling(true);
    SetGeometryClipping(true);
    // SetPolygonMode(PolygonMode::Fill);
}
