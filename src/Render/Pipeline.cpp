#include "Pipeline.h"
// #include "UI/window.h"
#include <cmath>
#include <iostream>
#include "imagelabel.h"

Pipeline::Pipeline(int width, int height)
{
    m_config.m_width = width;
    m_config.m_height = height;

    m_config.m_backBuffer = nullptr;
    m_config.m_frontBuffer = nullptr;
    m_config.m_shader = nullptr;
    m_config.m_eyePos = Vec3f(0.0f, 0.0f, 0.0f);

    m_camera = new NaiveCamera(Vec3f({2.0f, 1.0f, 3.0f}));
    m_projectionMat = Mat4x4GetProjectionNaive(m_camera->GetPosition().z);
    m_viewMat = m_camera->GetViewMatrix();
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
    if (m_camera)
        delete m_camera;

    m_config.m_backBuffer = nullptr;
    m_config.m_frontBuffer = nullptr;
    m_config.m_shader = nullptr;
    m_camera = nullptr;
}

void Pipeline::initialize()
{
    if (m_config.m_backBuffer)
        delete m_config.m_backBuffer;
    if (m_config.m_frontBuffer)
        delete m_config.m_frontBuffer;
    if (m_config.m_shader)
        delete m_config.m_shader;
    m_config.m_viewPortMat = Mat4x4GetViewportNaive(0.0f, 0.0f, (float)m_config.m_width, (float)m_config.m_height, 255.0f);
    // m_config.m_viewPortMat = Mat4x4GetViewport(0.0f, 0.0f, (float)m_config.m_width, (float)m_config.m_height);
    m_config.m_backBuffer = new FrameBuffer(m_config.m_width, m_config.m_height);
    m_config.m_frontBuffer = new FrameBuffer(m_config.m_width, m_config.m_height);
    m_config.m_shader = new SimpleShader();
    SetDefaultConfig();
}

void Pipeline::DrawModelPureColor(Model &model, Vec4f &color, const PolygonMode &type)
{
    for (int i = 0; i < model.m_Faces.size(); ++i)
    {
        std::vector<Vec3i> face = model.m_Faces[i];
        Vec3f v[3];
        for (int j = 0; j < 3; ++j)
        {
            v[j] = Vec4fToVec3f(m_config.m_viewPortMat * Vec3fToVec4f(model.m_Vertices[face[j][0]]));
        }
        DrawTriangleWithoutDepthInfo(v, color, (void *)m_config.m_backBuffer, type);
    }
}

void Pipeline::DrawModelNormalWithoutDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const PolygonMode &type)
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
            DrawTriangleWithoutDepthInfo(screenCoord, Vec4f(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), (void *)m_config.m_backBuffer, type);
        }
    }
}
void Pipeline::DrawModelNormalWithDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const PolygonMode &type)
{
    for (int i = 0; i < model.m_Faces.size(); ++i)
    {
        Vec3f screenCoord[3];
        Vec3f worldCoord[3];
        std::vector<Vec3i> face = model.m_Faces[i];
        for (int j = 0; j < 3; ++j)
        {
            worldCoord[j] = model.m_Vertices[face[j][0]];
            screenCoord[j] = Vec4fToVec3f(m_config.m_viewPortMat * m_projectionMat * Vec3fToVec4f(worldCoord[j]));
        }
        Vec3f normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
        // intensity
        float intensity = VecGetDotProduct(normal, lightDir);
        if (intensity > 0)
        {
            DrawTriangleWithDepthInfo(screenCoord, Vec4f(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), (void *)m_config.m_backBuffer, type);
        }
    }
}

void Pipeline::DrawModelWithTextureWithViewMat(Model &model, Vec3f &lightDir, const Texture2D &texture, const PolygonMode &type)
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
            screenCoord[j] = Vec4fToVec3f(m_config.m_viewPortMat * m_projectionMat * m_viewMat * Vec3fToVec4f(worldCoord[j]));
            texCoords[j] = model.m_UVCoords[face[j][1]];
            intensity[j] = VecGetDotProduct(model.m_Normals[face[j][2]], lightDir);
        }
        DrawTriangleFillModeWithDepthTexture(screenCoord, intensity, texCoords, texture, (void *)m_config.m_backBuffer);
    }
}
void Pipeline::DrawModelWithTextureWithoutViewMat(Model &model, Vec3f &lightDir, const Texture2D &texture, const PolygonMode &type)
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
            screenCoord[j] = Vec4fToVec3f(m_config.m_viewPortMat * m_projectionMat * Vec3fToVec4f(worldCoord[j]));
            texCoords[j] = model.m_UVCoords[face[j][1]];
        }

        // normal vector，这里obj定义的顶点顺序是逆时针 v1->v2->v3
        Vec3f normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
        // intensity
        float intensity = VecGetDotProduct(normal, lightDir);
        if (intensity > 0)
        {
            DrawTriangleFillModeWithDepthTexture(screenCoord, intensity, texCoords, texture, (void *)m_config.m_backBuffer);
        }
    }
}
void Pipeline::DrawModelWithShader(DrawData &drawData, const PolygonMode &type)
{
    Model *m = drawData.model;
    Shader *s = drawData.shader;
    shaderData.cameraViewMat = this->m_viewMat;
    shaderData.cameraProjectionMat = this->m_projectionMat;
    shaderData.screenViewportMat = this->m_config.m_viewPortMat;
    shaderData.modelTransViewMat = shaderData.cameraProjectionMat * shaderData.cameraViewMat * shaderData.modelTransMat;
    shaderData.modelTransViewMatInv = MatGetInverse(shaderData.modelTransViewMat);
    for (int i = 0; i < m->m_Faces.size(); ++i)
    {
        Vec3f screenCoord[3];
        for (int j = 0; j < 3; ++j)
        {
            screenCoord[j] = s->VertexShader(i, j);
        }

        DrawTriangleWithShader(screenCoord, s, (void *)m_config.m_backBuffer);
    }
}
// TODO: representation by ViewPortMatrix

Vec3f Pipeline::CoordWorldFloatToScreenFloat(Vec3f &v)
{
    Vec3f res;
    res.x = (v.x + 1.0f) * m_config.m_width / 2.0f;
    res.y = (v.y + 1.0f) * m_config.m_height / 2.0f;
    res.z = (v.z + 1.0f) * 255.0f / 2.0f;
    return res;
}
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
void Pipeline::CleraFrameBuffer(const Vec4f &color)
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

void Pipeline::SetViewMatrix(Vec3f eye, const Mat4x4f &viewMat)
{
    m_config.m_eyePos = eye;
    m_config.m_shader->SetEyePos(eye);
    m_config.m_shader->SetViewMatrix(viewMat);
    m_viewMat = viewMat;
}

void Pipeline::SetViewMatrix(Vec3f eye, Vec3f target, Vec3f up)
{
    m_config.m_eyePos = eye;
    Mat4x4f viewMat = Mat4x4GetLookAt(eye, target, up);
    m_config.m_shader->SetEyePos(eye);
    m_config.m_shader->SetViewMatrix(viewMat);
}

void Pipeline::SetProjectMatrix(float fovy, float aspect, float near, float far)
{
    Mat4x4f projectMat = Mat4x4GetPerspective(fovy, aspect, near, far);
    m_config.m_shader->SetProjectMatrix(projectMat);
}

void Pipeline::SetProjectMatrix(float z)
{
    m_projectionMat = Mat4x4GetProjectionNaive(z);
}

void Pipeline::SetModelMatrix(Mat4x4f modelMatrix)
{
    m_config.m_shader->SetModelMatrix(modelMatrix);
}

void Pipeline::SetShadingMode(ShadingMode &&mode)
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

void Pipeline::SetDefaultConfig()
{
    SetDepthTesting(true);
    SetBackFaceCulling(true);
    SetGeometryClipping(true);
    // SetPolygonMode(PolygonMode::Fill);
}

/* void Pipeline::SetCameraPosZ(float z)
{
    m_camera->SetCameraPosZ(z);
    m_projectionMat = Mat4x4GetProjectionNaive(m_camera->GetPosition().z);
} */

/* void Pipeline::SetCameraPos(const Vec3f &eye)
{
    m_camera->SetCameraPos(eye);
} */

/* void Pipeline::SetCameraLookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up)
{
    m_camera->SetCameraLookAt(eye, center, up);
    m_projectionMat = Mat4x4GetProjectionNaive(eye, center);
    m_viewMat = m_camera->GetViewMatrix();
} */
