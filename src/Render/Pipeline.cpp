#include "Pipeline.h"
#include "UI/window.h"
Pipeline::Pipeline(int width, int height) : m_Width(width), m_Height(height), m_backBuffer(nullptr), m_frontBuffer(nullptr)
{
}

Pipeline::~Pipeline()
{
    if (m_backBuffer)
        delete m_backBuffer;
    if (m_frontBuffer)
        delete m_frontBuffer;
    m_backBuffer = nullptr;
    m_frontBuffer = nullptr;
}

void Pipeline::DrawLine(int x1, int y1, int x2, int y2, Vec4f &color)
{

    for (float t = 0.0f; t < 1.0f; t += 0.01f)
    {
        int x = x1 * (1.0f - t) + x2 * t;
        int y = y1 * (1.0f - t) + y2 * t;
        m_backBuffer->DrawPixels(x, y, color);
    }
}

void Pipeline::ClearBuffers(const Vec4f &color)
{
    m_backBuffer->ClearBuffers(color);
}

unsigned char *Pipeline::Output()
{
    return m_frontBuffer->GetColorBuffer();
}

void Pipeline::SwapBuffer()
{
    FrameBuffer *temp = m_frontBuffer;
    m_frontBuffer = m_backBuffer;
    m_backBuffer = temp;
}

void Pipeline::Init()
{
    if (m_backBuffer)
        delete m_backBuffer;
    if (m_frontBuffer)
        delete m_frontBuffer;
    m_backBuffer = new FrameBuffer(m_Width, m_Height);
    m_frontBuffer = new FrameBuffer(m_Width, m_Height);
}

void Pipeline::CheckResize()
{
    if (Window::m_window->width() != m_Width || Window::m_window->height() != m_Height)
    {
        m_Width = Window::m_window->width();
        m_Height = Window::m_window->height();
        Init();
    }
}
