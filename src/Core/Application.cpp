#include "Application.h"
#include <QDebug>

#include "Render/Model.h"
#include "Render/Texture2D.h"
#include "Base.h"
#include "Shader/ShaderGroup.h"
#include "time.h"
#include "Render/Mesh.h"
#include "Render/Light.h"
#include <stdio.h>
#include <direct.h>
#include <memory>
#include "Transformation.h"
#include "Render/Sence.h"
Application::Application(int width, int height) : m_stopped(false), m_fps(0), m_width(width), m_height(height)
{
    m_pipeline = new Pipeline(width, height);
}

Application::~Application()
{
    if (m_pipeline)
        delete m_pipeline;
    m_pipeline = nullptr;
}

void Application::Run()
{
    // SetTestScenePBRSphere(m_pipeline->m_config);
    // SetTestSceneBlinnPhong(m_pipeline->m_config);
    // SetTestScenePBRHelmet(m_pipeline->m_config);
    SetTestSceneSkyBox(m_pipeline->m_config);

    m_pipeline->m_config->NotifyTreeNodeChanged();
    m_pipeline->m_config->NotifyLightChanged();
    m_fps = 0;
    while (!m_stopped)
    {
        m_pipeline->ClearFrameBuffer(Vec4(0.2f, 0.2f, 0.2f, 1.0f));
        m_pipeline->DrawScene();

        m_pipeline->SwapFrameBuffer();
        emit frameReady(m_pipeline->GetFrameResult());
        ++m_fps;
    }
}

void Application::Stop()
{
    m_stopped = true;
}
