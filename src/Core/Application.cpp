#include "Application.h"
#include <QDebug>

#include "Render/Model.h"
#include "Render/Texture2D.h"
#include "Base.h"
#include "Shader/GouraudShader.h"
#include "Render/ShaderData.h"
float Application::s_cameraZ = 3.0f;
Application::Application(int width, int height) : m_stopped(false), m_fps(0)
{
    m_pipeline = new Pipeline(width, height);
}

Application::~Application()
{
    m_stopped = true;
    if (m_pipeline)
        delete m_pipeline;

    m_pipeline = nullptr;
}

void Application::Run()
{
    m_stopped = false;

    Model model("obj/head/african_head.obj");
    // Model model("obj/cube/cube.obj");
    Texture2D texture1("obj/head/african_head_diffuse.tga");
    DrawData drawData;
    drawData.model = new Model(model);
    drawData.shader = new GouraudShader();
    // Vec3f lightDir(0.0f, 0.0f, 1.0f);
    // Vec3f lightDir(1.0f, 1.0f, 1.0f);

    m_fps = 0;
    while (!m_stopped)
    {
        //    m_pipeline->SetCameraPosZ(s_cameraZ);
        m_pipeline->SetCameraPos(cameraEye);
        m_pipeline->SetCameraLookAt(cameraEye, cameraCenter, cameraUp);
        m_pipeline->ClearBuffers(Vec4f(0.2f, 0.2f, 0.2f, 1.0f));
        // m_pipeline->DrawModelPureColor(model, Vec4f(0.0f, 0.8f, 0.1f, 1.0f), SRendererType::SFill);
        //  m_pipeline->DrawModelPureColor(model, Vec4f(0.1f, 0.1f, 0.1f, 1.0f), SRendererType::SLine);
        //   m_pipeline->DrawModelNormalWithoutDepthInfo(model, Vec3f(0.0f, 0.0f, 1.0f), Vec4f(0.0f, 0.8f, 0.1f, 1.0f), SRendererType::SFill);
        //    m_pipeline->DrawModelNormalWithDepthInfo(model, Vec3f(0.0f, 0.0f, 1.0f), Vec4f(0.0f, 0.8f, 0.1f, 1.0f));
        // m_pipeline->DrawModelWithTextureWithoutViewMat(model, Vec3f(0.0f, 0.0f, 1.0f), texture1);
        //m_pipeline->DrawModelWithTextureWithViewMat(model, Vec3f(1.0f, 1.0f, 1.0f), texture1);
         m_pipeline->DrawModelWithShader(drawData);
        ++m_fps;
        m_pipeline->SwapBuffer();
        emit frameReady(m_pipeline->Output());
    }
}

void Application::Stop()
{
    m_stopped = true;
}
