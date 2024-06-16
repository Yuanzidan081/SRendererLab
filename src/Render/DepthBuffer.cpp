#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(int width, int height) : m_Width(width), m_Height(height)
{
    m_DepthBuffer.resize(m_Width * m_Height, FLT_MAX);
}

int &DepthBuffer::GetHeight()
{
    return m_Height;
}

int &DepthBuffer::GetWidth()
{
    return m_Width;
}

float *DepthBuffer::GetDepthBuffer()
{
    return m_DepthBuffer.data();
}

void DepthBuffer::ClearBuffers()
{
    for (int x = 0; x < m_Width; ++x)
    {
        for (int y = 0; y < m_Height; ++y)
        {
            int ind = y * m_Width + x;
            m_DepthBuffer[ind] = FLT_MAX;
        }
    }
}

void DepthBuffer::SetPixelDepth(const unsigned int x, const unsigned int y, float depth)
{
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    int ind = (m_Height - 1 - y) * m_Width + x; // 把坐标的原点规定在左下角
    m_DepthBuffer[ind] = depth;
}