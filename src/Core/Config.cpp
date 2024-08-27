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
                   m_useSkyBox(true),
                   m_viewCull(true),
                   m_faceCullMode(BackFaceCull),

                   m_width(0),
                   m_height(0),
                   m_backBuffer(nullptr),
                   m_frontBuffer(nullptr),
                   m_polygonMode(PolygonMode::Fill),
                   m_viewPortMat(),
                   m_shader(nullptr),
                   m_indices(nullptr),
                   m_vertices(nullptr),
                   m_models(),
                   m_lights(),
                   m_fpsCamera(nullptr),

                   //    m_lightGroup(nullptr),
                   m_skyBox(nullptr),
                   m_cubeMap(nullptr),
                   m_ambient(Vec4(0.1f, 0.1f, 0.1f, 1.0f))
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
    if (m_skyBox)
        delete m_skyBox;
    if (m_cubeMap)
        delete m_cubeMap;
    for (size_t i = 0; i < m_lights.size(); ++i)
    {
        if (m_lights[i])
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
    shader = NormalShader::GetInstance();
    shader->Destroy();
    shader = PBRShader::GetInstance();
    shader->Destroy();
    shader = SkyBoxShader::GetInstance();
    shader->Destroy();
    m_backBuffer = nullptr;
    m_frontBuffer = nullptr;
    m_fpsCamera = nullptr;
    m_skyBox = nullptr;
    m_cubeMap = nullptr;
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
    m_viewPortMat.SetViewPort(0.0f, 0.0f, (float)m_width, (float)m_height);
    m_backBuffer = new FrameBuffer(m_width, m_height);
    m_frontBuffer = new FrameBuffer(m_width, m_height);
    m_shader = SimpleShader::GetInstance();
    m_fpsCamera = new EulerFPSCamera(Vec3(0.0f, 0.0f, 5.0f));
    m_skyBox = new Model(Mesh::CreateBox(2.0f, 2.0f, 2.0f), "skybox");
    m_skyBox->SetShader(SkyBoxShader::GetInstance());
    // m_lightGroup = new LightGroup();
}
