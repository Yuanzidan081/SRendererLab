#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height) : m_Width(width), m_Height(height), m_Channels(4)
{
    m_ColorBuffer.resize(m_Width * m_Height * m_Channels, 255);
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
    return m_ColorBuffer.data();
}

void FrameBuffer::ClearBuffers(const Vec4f &color)
{
    for (int x = 0; x < m_Width; ++x)
    {
        for (int y = 0; y < m_Height; ++y)
        {
            int ind = y * m_Width + x;
            m_ColorBuffer[ind * m_Channels + 0] = static_cast<unsigned char>(255.0f * color.r);
            m_ColorBuffer[ind * m_Channels + 1] = static_cast<unsigned char>(255.0f * color.g);
            m_ColorBuffer[ind * m_Channels + 2] = static_cast<unsigned char>(255.0f * color.b);
            m_ColorBuffer[ind * m_Channels + 3] = static_cast<unsigned char>(255.0f * color.a);
        }
    }
}

void FrameBuffer::SetPixelColor(const unsigned int x, const unsigned int y, const Vec4f &color)
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    int ind = (m_Height - 1 - y) * m_Width + x; // 把坐标的原点规定在左下角
    m_ColorBuffer[ind * m_Channels + 0] = static_cast<unsigned char>(255.0f * color.r);
    m_ColorBuffer[ind * m_Channels + 1] = static_cast<unsigned char>(255.0f * color.g);
    m_ColorBuffer[ind * m_Channels + 2] = static_cast<unsigned char>(255.0f * color.b);
    m_ColorBuffer[ind * m_Channels + 3] = static_cast<unsigned char>(255.0f * color.a);
}
