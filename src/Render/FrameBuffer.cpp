#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height) : m_Width(width), m_Height(height), m_Channels(4)
{
    m_ColorBuffer.resize(m_Width * m_Height * m_Channels, 255);
    m_DepthBuffer.resize(m_Width * m_Height, 1.0f);
}

int &FrameBuffer::GetHeight()
{
    return m_Height;
}

int &FrameBuffer::GetWidth()
{
    return m_Width;
}

int &FrameBuffer::GetChannels()
{
    return m_Channels;
}

unsigned char *FrameBuffer::GetColorBuffer()
{
    // std::cout << "image: " << m_Width << " " << m_Height;
    return m_ColorBuffer.data();
}

float *FrameBuffer::GetDepthBuffer()
{
    return m_DepthBuffer.data();
}

void FrameBuffer::clearColorAndDepthBuffer(const Vec4 &color)
{
    for (int x = 0; x < m_Width; ++x)
    {
        for (int y = 0; y < m_Height; ++y)
        {
            int ind = y * m_Width + x;
            /* color buffer*/
            m_ColorBuffer[ind * m_Channels + 0] = static_cast<unsigned char>(255.0f * color.r);
            m_ColorBuffer[ind * m_Channels + 1] = static_cast<unsigned char>(255.0f * color.g);
            m_ColorBuffer[ind * m_Channels + 2] = static_cast<unsigned char>(255.0f * color.b);
            m_ColorBuffer[ind * m_Channels + 3] = static_cast<unsigned char>(255.0f * color.a);
            /* depth buffer*/
            m_DepthBuffer[ind] = 1.0f;
        }
    }
}

void FrameBuffer::SetPixelColor(const unsigned int x, const unsigned int y, const Vec4 &color)
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    // int ind = (m_Height - 1 - y) * m_Width + x; // 把坐标的原点规定在左下角
    int ind = y * m_Width + x; // 把坐标的原点规定在左下角

    m_ColorBuffer[ind * m_Channels + 0] = static_cast<unsigned char>(255.0f * Clamp(color.r, 0.0f, 1.0f));
    m_ColorBuffer[ind * m_Channels + 1] = static_cast<unsigned char>(255.0f * Clamp(color.g, 0.0f, 1.0f));
    m_ColorBuffer[ind * m_Channels + 2] = static_cast<unsigned char>(255.0f * Clamp(color.b, 0.0f, 1.0f));
    m_ColorBuffer[ind * m_Channels + 3] = static_cast<unsigned char>(255.0f * color.a);
}

void FrameBuffer::SetPixelDepth(const unsigned int x, const unsigned int y, float depth)
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    // int ind = (m_Height - 1 - y) * m_Width + x; // 把坐标的原点规定在左下角
    int ind = y * m_Width + x; // 把坐标的原点规定在左下角

    m_DepthBuffer[ind] = depth;
}

void FrameBuffer::SetPixelDepth(int ind, float depth)
{
    if (ind < 0 || ind >= m_DepthBuffer.size())
        return; // 返回一个FLT_MAX，初始化的数
    m_DepthBuffer[ind] = depth;
}

float FrameBuffer::GetPixelDepth(const unsigned int x, const unsigned int y)
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return 0.0f; // 返回一个FLT_MAX，初始化的数
    //    int ind = (m_Height - 1 - y) * m_Width + x; // 把坐标的原点规定在左下角
    int ind = y * m_Width + x; // 把坐标的原点规定在左下角

    return m_DepthBuffer[ind];
}

float FrameBuffer::GetPixelDepth(int ind)
{
    if (ind < 0 || ind >= m_DepthBuffer.size())
        return 0.0f; // 返回一个FLT_MAX，初始化的数
    return m_DepthBuffer[ind];
}
