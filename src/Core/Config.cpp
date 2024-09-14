#include "Config.h"
#include "Render/Model.h"
#include "Render/Vertex.h"
#include "Render/FrameBuffer.h"
#include "Shader/ShaderGroup.h"
#include "Render/Light.h"
#include "Render/FPSCamera.h"
std::shared_ptr<Config> Config::localInstance = nullptr;

void deleter(Config *ptr)
{
    ptr->Destroy();
    delete ptr;
    ptr = nullptr;
}

Config::Config() : m_depthTesting(true),
                   m_backFaceCulling(true),
                   m_useSkyBox(true),
                   m_viewCull(true),
                   m_faceCullMode(BackFaceCull),
                   m_shadingMode(ForwardMode),
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
                   m_resourceManager(ResourceManager::GetInstance()),
                   //    m_lightGroup(nullptr),
                   m_skyBox(nullptr),
                   m_cubeMap(nullptr),
                   m_ambient(Vec4(0.1f, 0.1f, 0.1f, 1.0f)),
                   m_currentLight(),
                   m_deferredBuffer(nullptr)

{
}
Config::~Config()
{
}
void Config::AddModel(const std::shared_ptr<Model> &model)
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
    // if (m_cubeMap)
    //     delete m_cubeMap;
    for (size_t i = 0; i < m_models.size(); ++i)
    {
        m_models[i].reset();
    }
    m_models.clear();
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
    // m_cubeMap = nullptr;
}
// Config *Config::GetInstance()
std::shared_ptr<Config> Config::GetInstance()
{
    if (localInstance == nullptr)
    {
        localInstance.reset(new Config());
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
    m_fpsCamera = new EulerFPSCamera(Vec3(0.0f, 0.0f, 8.0f));
    m_skyBox = new Model(Mesh::CreateBox(2.0f, 2.0f, 2.0f), "skybox");
    m_skyBox->SetShader(SkyBoxShader::GetInstance());
    // m_cubeMap = std::make_shared<CubeMap>();
    // m_cubeMap = std::make_shared<CubeMap>(
    //     new Texture("res/skybox_sea/right.jpg"),
    //     new Texture("res/skybox_sea/left.jpg"),
    //     new Texture("res/skybox_sea/top.jpg"),
    //     new Texture("res/skybox_sea/bottom.jpg"),
    //     new Texture("res/skybox_sea/back.jpg"),
    //     new Texture("res/skybox_sea/front.jpg"));
    m_cubeMap = std::make_shared<CubeMap>(
        new Texture("res/skybox_avenue/posx.bmp"),
        new Texture("res/skybox_avenue/negx.bmp"),
        new Texture("res/skybox_avenue/posy.bmp"),
        new Texture("res/skybox_avenue/negy.bmp"),
        new Texture("res/skybox_avenue/negz.bmp"),
        new Texture("res/skybox_avenue/posz.bmp"));

    m_deferredBuffer = std::make_shared<DeferredGBuffer>(m_width, m_height);
}

void Config::NewLightProperty(int lightIndex)
{
    if (lightIndex < 0 || lightIndex >= m_lights.size())
    {
        m_currentLight.reset();
        std::cout << "invalid light index";
        return;
    }
    if (m_lights.size() == 0)
    {
        m_currentLight.reset();
    }
    else
    {
        m_currentLight = m_lights[lightIndex];
    }
    Fire_OnPropertyChanged("NewLightProperty");
}

std::shared_ptr<Light> &Config::GetCurrentLight()
{
    return m_currentLight;
}

void Config::AddLight(const std::shared_ptr<Light> light)
{
    m_lights.push_back(light);
}

DeferredGBuffer::DeferredGBuffer(int w, int h)
    : m_GBufferPosition(std::make_shared<FrameBuffer>(w, h, 3, GBuffer)),
      m_GBufferNormal(std::make_shared<FrameBuffer>(w, h, 3, GBuffer)),
      m_GBufferColor(std::make_shared<FrameBuffer>(w, h, 4, GBuffer)) {}

void DeferredGBuffer::clearGBuffer(const Vec4 &color)
{
    m_GBufferColor->ClearGbufferData(color);
    m_GBufferNormal->ClearGbufferData();
    m_GBufferPosition->ClearGbufferData();
}
