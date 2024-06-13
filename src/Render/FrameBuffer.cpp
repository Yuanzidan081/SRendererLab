#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height) : m_Width(width), m_Height(height), m_Channels(4)
{
    m_ColorBuffer.resize(m_Width * m_Height * m_Channels, 255);
}

int &FrameBuffer::GetHeight()
{
    // TODO: 在此处插入 return 语句
    return m_Height;
}

int &FrameBuffer::GetWidth()
{
    // TODO: 在此处插入 return 语句
    return m_Width;
    ;
}

int &FrameBuffer::GetChannels()
{
    // TODO: 在此处插入 return 语句
    return m_Channels;
}

unsigned char *FrameBuffer::GetColorBuffer()
{
    // TODO: 在此处插入 return 语句
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

void FrameBuffer::DrawPixels(const unsigned int x, const unsigned int y, const Vec4f &color)
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    int ind = y * m_Width + x;
    m_ColorBuffer[ind * m_Channels + 0] = static_cast<unsigned char>(255.0f * color.r);
    m_ColorBuffer[ind * m_Channels + 1] = static_cast<unsigned char>(255.0f * color.g);
    m_ColorBuffer[ind * m_Channels + 2] = static_cast<unsigned char>(255.0f * color.b);
    m_ColorBuffer[ind * m_Channels + 3] = static_cast<unsigned char>(255.0f * color.a);
}
