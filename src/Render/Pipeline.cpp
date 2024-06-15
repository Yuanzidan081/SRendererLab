#include "Pipeline.h"
#include "UI/window.h"
#include <cmath>
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

    /* naive version 1*/
    /* for (float t = 0.0f; t < 1.0f; t += 0.01f)
    {
        int x = x1 * (1.0f - t) + x2 * t;
        int y = y1 * (1.0f - t) + y2 * t;
        m_backBuffer->DrawPixels(x, y, color);
    } */
    /* naive version 2*/
    /* if (x1 > x2)
    { // 当x0>x1时，调换两个点的坐标
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    for (int x = x1; x <= x2; ++x)
    {
        float t = (float)(x - x1) / (float)(x2 - x1);
        int y = y1 * (1.0f - t) + y2 * t;
        m_backBuffer->DrawPixels(x, y, color);
    } */
    bool steep = false;
    if (std::abs(x1 - x2) < std::abs(y1 - y2))
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }
    if (x1 > x2)
    { // 当x0>x1时，调换两个点的坐标
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    for (int x = x1; x <= x2; ++x)
    {
        float t = (float)(x - x1) / (float)(x2 - x1);
        int y = y1 * (1.0f - t) + y2 * t;
        if (steep)
            m_backBuffer->DrawPixels(y, x, color);
        else
            m_backBuffer->DrawPixels(x, y, color);
    }
}

void Pipeline::DrawTriangle(Model &model, Vec4f &color)
{
    for (int i = 0; i < model.GetFacesSize(); ++i)
    {
        std::vector<int> f = model.GetFaces(i);
        // std::cout << f[0] << " " << f[1] << " " << f[2] << std::endl;
        for (int j = 0; j < 3; ++j)
        {
            Vec3f v1 = model.GetVetices(f[j]);
            Vec3f v2 = model.GetVetices(f[(j + 1) % 3]);

            int x1 = (v1.x + 1.0f) * (float)m_Width / 2.0f;
            int y1 = (v1.y + 1.0f) * (float)m_Height / 2.0f;
            int x2 = (v2.x + 1.0f) * (float)m_Width / 2.0f;
            int y2 = (v2.y + 1.0f) * (float)m_Height / 2.0f;
            DrawLine(x1, y1, x2, y2, color);
        }
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
