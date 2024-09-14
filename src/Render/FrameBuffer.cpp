#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height, int channels, FrameBufferMode mode) : m_Width(width), m_Height(height), m_Channels(channels), m_mode(mode)
{
    if (mode == NormalBuffer)
    {
        m_ColorBuffer.resize(m_Width * m_Height * m_Channels, 255);
        m_DepthBuffer.resize(m_Width * m_Height, 1.0f);
    }
    if (mode == GBuffer)
    {
        m_gBuffer.resize(m_Width * m_Height * m_Channels, 1.0f);
    }
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

float *FrameBuffer::GetGBuffer()
{
    // std::cout << m_gBuffer.size() << std::endl;
    // std::cout << m_gBuffer << std::endl;
    // std::cout << m_gBuffer[188136 * 3 + 0] << " " << m_gBuffer[188136 * 3 + 1] << " " << m_gBuffer[188136 * 3 + 2] << " " << m_gBuffer[188136 * 3 + 3] << std::endl;
    return m_gBuffer.data();
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

void FrameBuffer::SetPixelGBufferData3(const unsigned int x, const unsigned int y, const Vec3 &data)
{
    if (m_Channels != 3)
    {
        std::cout << "Gbuffer channel is not 3" << std::endl;
        return;
    }

    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    // int ind = (m_Height - 1 - y) * m_Width + x; // 把坐标的原点规定在左下角
    int ind = y * m_Width + x; // 把坐标的原点规定在左下角

    m_gBuffer[ind * m_Channels + 0] = data.r;
    m_gBuffer[ind * m_Channels + 1] = data.g;
    m_gBuffer[ind * m_Channels + 2] = data.b;
}

void FrameBuffer::SetPixelGBufferData4(const unsigned int x, const unsigned int y, const Vec4 &data)
{
    if (m_Channels != 4)
    {
        std::cout << "Gbuffer channel is not 4" << std::endl;
        return;
    }

    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    // int ind = (m_Height - 1 - y) * m_Width + x; // 把坐标的原点规定在左下角
    int ind = y * m_Width + x; // 把坐标的原点规定在左下角

    m_gBuffer[ind * m_Channels + 0] = data.r;
    m_gBuffer[ind * m_Channels + 1] = data.g;
    m_gBuffer[ind * m_Channels + 2] = data.b;
    m_gBuffer[ind * m_Channels + 3] = data.a;
    // std::cout << m_gBuffer[ind * m_Channels + 0] << " " << m_gBuffer[ind * m_Channels + 1] << " " << m_gBuffer[ind * m_Channels + 2] << " " << m_gBuffer[ind * m_Channels + 3] << std::endl;
}

Vec3 FrameBuffer::SampleGbufferData3(const unsigned int x, const unsigned int y)
{
    if (m_Channels != 3)
    {
        std::cout << "Gbuffer channel is not 3" << std::endl;
        return Vec3();
    }

    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return Vec3();
    int ind = y * m_Width + x; // 把坐标的原点规定在左下角
    return Vec3(m_gBuffer[ind * m_Channels + 0],
                m_gBuffer[ind * m_Channels + 1],
                m_gBuffer[ind * m_Channels + 2]);
}

Vec4 FrameBuffer::SampleGbufferData4(const unsigned int x, const unsigned int y)
{
    if (m_Channels != 4)
    {
        std::cout << "Gbuffer channel is not 4" << std::endl;
        return Vec4();
    }

    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return Vec4();
    int ind = y * m_Width + x; // 把坐标的原点规定在左下角
    return Vec4(m_gBuffer[ind * m_Channels + 0],
                m_gBuffer[ind * m_Channels + 1],
                m_gBuffer[ind * m_Channels + 2],
                m_gBuffer[ind * m_Channels + 3]);
}

void FrameBuffer::ClearGbufferData()
{
    // m_gBuffer.resize(m_Width * m_Height * m_Channels, 1.0f);
    for (int x = 0; x < m_Width; ++x)
    {
        for (int y = 0; y < m_Height; ++y)
        {
            int ind = y * m_Width + x;
            /* color buffer*/
            if (m_Channels == 3)
            {
                m_gBuffer[ind * m_Channels + 0] = static_cast<unsigned char>(0);
                m_gBuffer[ind * m_Channels + 1] = static_cast<unsigned char>(0);
                m_gBuffer[ind * m_Channels + 2] = static_cast<unsigned char>(0);
            }
            else if (m_Channels == 4)
            {
                m_gBuffer[ind * m_Channels + 0] = static_cast<unsigned char>(0);
                m_gBuffer[ind * m_Channels + 1] = static_cast<unsigned char>(0);
                m_gBuffer[ind * m_Channels + 2] = static_cast<unsigned char>(0);
                m_gBuffer[ind * m_Channels + 3] = static_cast<unsigned char>(0);
            }
        }
    }
}

void FrameBuffer::ClearGbufferData(const Vec4 &color)
{
    for (int x = 0; x < m_Width; ++x)
    {
        for (int y = 0; y < m_Height; ++y)
        {
            int ind = y * m_Width + x;
            /* color buffer*/
            if (m_Channels == 3)
            {
                m_gBuffer[ind * m_Channels + 0] = color.r;
                m_gBuffer[ind * m_Channels + 1] = color.g;
                m_gBuffer[ind * m_Channels + 2] = color.b;
            }
            else if (m_Channels == 4)
            {
                m_gBuffer[ind * m_Channels + 0] = color.r;
                m_gBuffer[ind * m_Channels + 1] = color.g;
                m_gBuffer[ind * m_Channels + 2] = color.b;
                m_gBuffer[ind * m_Channels + 3] = color.a;
            }
        }
    }
}

void FrameBuffer::SetPixelGBufferData2(const unsigned int x, const unsigned int y, const Vec2 &data)
{

    if (m_Channels != 2)
    {
        std::cout << "Gbuffer channel is not 2" << std::endl;
        return;
    }
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;
    // int ind = (m_Height - 1 - y) * m_Width + x; // 把坐标的原点规定在左下角
    int ind = y * m_Width + x; // 把坐标的原点规定在左下角

    m_gBuffer[ind * m_Channels + 0] = data.x;
    m_gBuffer[ind * m_Channels + 1] = data.y;
}
