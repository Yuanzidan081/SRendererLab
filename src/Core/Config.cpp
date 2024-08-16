#include "Config.h"
#include "Render/Model.h"
#include "Render/Vertex.h"
#include "Render/FrameBuffer.h"
#include "Shader/ShaderGroup.h"
#include "Render/Light.h"
#include "Render/FPSCamera.h"
Config *Config::localInstance = nullptr;

Config::Config() : m_depthTesting(true),
                   m_backFaceCulling(true),
                   m_width(0),
                   m_height(0),
                   m_backBuffer(nullptr),
                   m_frontBuffer(nullptr),
                   m_polygonMode(PolygonMode::Fill),
                   m_viewPortMat(),
                   m_eyePos(Vec3(0, 0, 0)),
                   m_shader(nullptr),
                   m_indices(nullptr),
                   m_vertices(nullptr),
                   m_models(),
                   m_lights(),
                   m_viewPlaneParameters(),
                   m_viewLineParameters(),
                   m_fpsCamera(nullptr)
{
}
Config::~Config()
{
}
void Config::AddModel(Model *model)
{
    m_models.push_back(model);
}
void Config::Destroy()
{
    if (m_backBuffer)
        delete m_backBuffer;
    if (m_frontBuffer)
        delete m_frontBuffer;

    if (m_fpsCamera)
        delete m_fpsCamera;
    for (size_t i = 0; i < m_lights.size(); ++i)
    {
        delete m_lights[i];
        m_lights[i] = nullptr;
    }
    /* for (size_t i = 0; i < m_models.size(); ++i)
    {
        delete m_models[i];
        m_models[i] = nullptr;
    } */

    Shader *shader = PhongShader::GetInstance();
    shader->Destroy();
    shader = GouraudShader::GetInstance();
    shader->Destroy();
    shader = SimpleShader::GetInstance();
    shader->Destroy();
    m_fpsCamera = nullptr;
    m_backBuffer = nullptr;
    m_frontBuffer = nullptr;
    m_shader = nullptr;
    if (localInstance)
        delete localInstance;
    localInstance = nullptr;
}
Config *Config::GetInstance()
{
    if (localInstance == nullptr)
    {
        localInstance = new Config();
    }
    return localInstance;
}

void Config::Initialize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_viewPlaneParameters.resize(6, Vec4());
    m_viewLineParameters = {
        // near
        Vec4(0, 0, 1, 1),
        // far
        Vec4(0, 0, -1, 1),
        // left
        Vec4(1, 0, 0, 1),
        // right
        Vec4(-1, 0, 0, 1),
        // top
        Vec4(0, -1, 0, 1),
        // bottom
        Vec4(0, 1, 0, 1)};
    if (m_backBuffer)
        delete m_backBuffer;
    if (m_frontBuffer)
        delete m_frontBuffer;
    if (m_shader)
        delete m_shader;
    if (m_fpsCamera)
        delete m_fpsCamera;
    m_viewPortMat.SetViewPort(0.0f, 0.0f, (float)m_width, (float)m_height);
    m_backBuffer = new FrameBuffer(m_width, m_height);
    m_frontBuffer = new FrameBuffer(m_width, m_height);
    m_shader = SimpleShader::GetInstance();
    m_fpsCamera = new EulerFPSCamera(Vec3(1.5f, 1.0f, 10.0f));
}
