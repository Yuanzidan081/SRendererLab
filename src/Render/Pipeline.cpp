#include "Pipeline.h"
// #include "UI/window.h"
#include <cmath>
#include <iostream>
#include "imagelabel.h"
Pipeline::Pipeline(int width, int height) : m_Width(width), m_Height(height)
{
    m_camera = new Camera(Vec3f({2.0f, 1.0f, 3.0f}));
    m_viewPortMat = Mat4x4GetViewportNaive(0.0f, 0.0f, (float)m_Width, (float)m_Height, 255.0f);
    m_projectionMat = Mat4x4GetProjectionNaive(m_camera->GetCameraPos().z);
    m_viewMat = m_camera->GetCameraLookAt();
    m_backBuffer = new FrameBuffer(width, height);
    m_frontBuffer = new FrameBuffer(width, height);
}

Pipeline::~Pipeline()
{
    if (m_backBuffer)
        delete m_backBuffer;
    if (m_frontBuffer)
        delete m_frontBuffer;
    if (m_camera)
        delete m_camera;

    m_backBuffer = nullptr;
    m_frontBuffer = nullptr;
    m_camera = nullptr;
}

void Pipeline::DrawModelPureColor(Model &model, Vec4f &color, const SRendererType &type)
{
    for (int i = 0; i < model.m_Faces.size(); ++i)
    {
        std::vector<Vec3i> face = model.m_Faces[i];
        Vec3f v[3];
        for (int j = 0; j < 3; ++j)
        {
            v[j] = Vec4fToVec3f(m_viewPortMat * Vec3fToVec4f(model.m_Vertices[face[j][0]]));
        }
        DrawTriangleWithoutDepthInfo(v, color, (void *)m_backBuffer, type);
    }
}

void Pipeline::DrawModelNormalWithoutDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const SRendererType &type)
{
    for (int i = 0; i < model.m_Faces.size(); ++i)
    {
        Vec3f screenCoord[3];
        Vec3f worldCoord[3];
        std::vector<Vec3i> face = model.m_Faces[i];
        for (int j = 0; j < 3; ++j)
        {
            worldCoord[j] = model.m_Vertices[face[j][0]];
            screenCoord[j] = CoordWorldFloatToScreenFloat(worldCoord[j]);
        }
        Vec3f normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
        // intensity
        float intensity = VecGetDotProduct(normal, lightDir);
        if (intensity > 0)
        {
            DrawTriangleWithoutDepthInfo(screenCoord, Vec4f(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), (void *)m_backBuffer, type);
        }
    }
}
void Pipeline::DrawModelNormalWithDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const SRendererType &type)
{
    for (int i = 0; i < model.m_Faces.size(); ++i)
    {
        Vec3f screenCoord[3];
        Vec3f worldCoord[3];
        std::vector<Vec3i> face = model.m_Faces[i];
        for (int j = 0; j < 3; ++j)
        {
            worldCoord[j] = model.m_Vertices[face[j][0]];
            screenCoord[j] = Vec4fToVec3f(m_viewPortMat * m_projectionMat * Vec3fToVec4f(worldCoord[j]));
        }
        Vec3f normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
        // intensity
        float intensity = VecGetDotProduct(normal, lightDir);
        if (intensity > 0)
        {
            DrawTriangleWithDepthInfo(screenCoord, Vec4f(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), (void *)m_backBuffer, type);
        }
    }
}

void Pipeline::DrawModelWithTextureWithViewMat(Model &model, Vec3f &lightDir, const Texture2D &texture, const SRendererType &type)
{
    for (int i = 0; i < model.m_Faces.size(); ++i)
    {
        Vec3f screenCoord[3];
        Vec3f worldCoord[3];
        Vec2f texCoords[3];
        float intensity[3];
        std::vector<Vec3i> face = model.m_Faces[i];

        for (int j = 0; j < 3; ++j)
        {
            worldCoord[j] = model.m_Vertices[face[j][0]];
            screenCoord[j] = Vec4fToVec3f(m_viewPortMat * m_projectionMat * m_viewMat * Vec3fToVec4f(worldCoord[j]));
            texCoords[j] = model.m_UVCoords[face[j][1]];
            intensity[j] = VecGetDotProduct(model.m_Normals[face[j][2]], lightDir);
        }
        DrawTriangleFillModeWithDepthTexture(screenCoord, intensity, texCoords, texture, (void *)m_backBuffer);
    }
}
void Pipeline::DrawModelWithTextureWithoutViewMat(Model &model, Vec3f &lightDir, const Texture2D &texture, const SRendererType &type)
{

    for (int i = 0; i < model.m_Faces.size(); ++i)
    {
        Vec3f screenCoord[3];
        Vec3f worldCoord[3];
        Vec2f texCoords[3];
        std::vector<Vec3i> face = model.m_Faces[i];
        for (int j = 0; j < 3; ++j)
        {
            worldCoord[j] = model.m_Vertices[face[j][0]];
            screenCoord[j] = Vec4fToVec3f(m_viewPortMat * m_projectionMat * Vec3fToVec4f(worldCoord[j]));
            texCoords[j] = model.m_UVCoords[face[j][1]];
        }

        // normal vector，这里obj定义的顶点顺序是逆时针 v1->v2->v3
        Vec3f normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
        // intensity
        float intensity = VecGetDotProduct(normal, lightDir);
        if (intensity > 0)
        {
            DrawTriangleFillModeWithDepthTexture(screenCoord, intensity, texCoords, texture, (void *)m_backBuffer);
        }
    }
}
void Pipeline::DrawModelWithShader(DrawData &drawData, const SRendererType &type)
{
    Model *m = drawData.model;
    Shader *s = drawData.shader;
    shaderData.cameraViewMat = this->m_viewMat;
    shaderData.cameraProjectionMat = this->m_projectionMat;
    shaderData.screenViewportMat = this->m_viewPortMat;
    for (int i = 0; i < m->m_Faces.size(); ++i)
    {
        Vec3f screenCoord[3];
        for (int j = 0; j < 3; ++j)
        {
            screenCoord[j] = s->VertexShader(i, j);
        }

        DrawTriangleWithShader(screenCoord, s, (void *)m_backBuffer);
    }
}
// TODO: representation by ViewPortMatrix

Vec3f Pipeline::CoordWorldFloatToScreenFloat(Vec3f &v)
{
    Vec3f res;
    res.x = (v.x + 1.0f) * m_Width / 2.0f;
    res.y = (v.y + 1.0f) * m_Height / 2.0f;
    res.z = (v.z + 1.0f) * 255.0f / 2.0f;
    return res;
}
void Pipeline::ClearBuffers(const Vec4f &color)
{
    m_backBuffer->ClearBuffers(color);
}

unsigned char *Pipeline::Output()
{
    return m_frontBuffer->GetColorBuffer();
}

void Pipeline::SwapBuffer()
{
    FrameBuffer *temp = m_frontBuffer;
    m_frontBuffer = m_backBuffer;
    m_backBuffer = temp;
}

void Pipeline::SetCameraPosZ(float z)
{
    m_camera->SetCameraPosZ(z);
    m_projectionMat = Mat4x4GetProjectionNaive(m_camera->GetCameraPos().z);
}

void Pipeline::SetCameraPos(const Vec3f &eye)
{
    m_camera->SetCameraPos(eye);
}

void Pipeline::SetCameraLookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up)
{
    m_camera->SetCameraLookAt(eye, center, up);
    m_projectionMat = Mat4x4GetProjectionNaive(eye, center);
    m_viewMat = m_camera->GetCameraLookAt();
}
