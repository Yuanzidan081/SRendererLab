#include "Application.h"
#include <QDebug>

#include "Render/Model.h"
#include "Render/Texture.h"
#include "Base.h"
#include "Shader/ShaderGroup.h"
#include "time.h"
#include "Render/Mesh.h"
#include "Render/Light.h"
#include <stdio.h>
#include <direct.h>
#include <memory>
#include "Transformation.h"
#include "Render/Scene.h"
Application::Application(int width, int height) : m_stopped(false), m_fps(0), m_width(width), m_height(height)
{
    m_pipeline = new CorePipeline(width, height);
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
        // if (m_pipeline->m_config->m_shadingMode == ForwardMode)
        // {
        m_pipeline->ClearFrameBuffer(Vec4(0.2f, 0.2f, 0.2f, 1.0f));
        // }
        // else if (m_pipeline->m_config->m_shadingMode == DeferredMode)
        // {
        //     m_pipeline->m_config->m_deferredBuffer->clearGBuffer(Vec4(0.2f, 0.2f, 0.2f, 1.0f));
        // }
        // if (m_pipeline->m_config->m_shadingMode == DeferredMode)
        // {
        //     m_pipeline->m_config->m_deferredBuffer->clearGBuffer();
        //     // emit frameReadyGbufferPos(m_pipeline->GetGBufferPositionResult());
        //     // emit frameReadyGbufferColor(m_pipeline->GetGbufferColorResult());
        //     // emit frameReadyGbufferNormal(m_pipeline->GetGbufferNormalResult());
        // }
        // m_pipeline->m_config->m_mutex.lock();
        m_pipeline->DrawScene();
        // m_pipeline->m_config->m_mutex.unlock();
        m_pipeline->SwapFrameBuffer();
        // if (m_pipeline->m_config->m_shadingMode == ForwardMode)
        emit frameReady(m_pipeline->GetFrameResult());
        if (m_pipeline->m_config->m_shadingMode == DeferredMode)
        {
            // emit frameReadyGbufferPos(m_pipeline->GetGBufferPositionResult());
            // emit frameReadyGbufferColor(m_pipeline->GetGbufferColorResult());
            // emit frameReadyGbufferNormal(m_pipeline->GetGbufferNormalResult());
        }
        ++m_fps;
    }
}

void Application::Stop()
{
    m_stopped = true;
}
