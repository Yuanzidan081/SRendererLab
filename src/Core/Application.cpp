#include "Application.h"
#include <QDebug>
Application::Application(int width, int height) : m_stopped(false)
{
    m_pipeline = new Pipeline(width, height);
}

void Application::Resize(int width, int height)
{
    if (m_pipeline)
        delete m_pipeline;
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
    while (!m_stopped)
    {
        //++i;
        // qDebug() << i;
        m_pipeline->CheckResize();
        m_pipeline->ClearBuffers(Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
        m_pipeline->DrawLine(20, 20, 75, 75, Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
        m_pipeline->DrawLine(75, 90, 100, 50, Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
        m_pipeline->DrawLine(150, 200, 50, 100, Vec4f(0.0f, 0.0f, 1.0f, 1.0f));
        m_pipeline->SwapBuffer();
        emit frameReady(m_pipeline->Output());
    }
}

void Application::Stop()
{
    m_stopped = true;
}
