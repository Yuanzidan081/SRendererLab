#include "Config.h"
#include "Render/Model.h"
#include "Render/Vertex.h"
#include "Render/FrameBuffer.h"
#include "Shader/Shader.h"
#include "Render/Light.h"
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
                   m_viewLineParameters()
{
}
Config::~Config()
{
    // 其他地方也要析构一下
    if (localInstance)
        delete localInstance;
    localInstance = nullptr;
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
    if (m_shader)
        delete m_shader;

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
    m_backBuffer = nullptr;
    m_frontBuffer = nullptr;
    m_shader = nullptr;
}
Config *Config::GetInstance()
{
    if (localInstance == nullptr)
    {
        localInstance = new Config();
    }
    return localInstance;
}