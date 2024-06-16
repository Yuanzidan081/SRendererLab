#include "Application.h"
#include <QDebug>
#include "Render/Model.h"
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
    // static int i = 0;
    m_stopped = false;
    m_pipeline->Init();
    Model model("obj/head/african_head.obj");
    // Model model("obj/cube/cube.obj");
    m_pipeline->CheckResize();
    m_fps = 0;
    while (!m_stopped)
    {
        m_pipeline->ClearBuffers(Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
        m_pipeline->DrawModelPureColor(model, Vec4f(0.0f, 0.8f, 0.1f, 1.0f));
        // m_pipeline->DrawModelNormal(model, Vec3f(0.0f, 0.0f, 1.0f), Vec4f(0.0f, 0.8f, 0.1f, 1.0f));

        ++m_fps;
        m_pipeline->SwapBuffer();
        emit frameReady(m_pipeline->Output());
    }
}

void Application::Stop()
{
    m_stopped = true;
}
