#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "Math/MathGroup.h"
#include <vector>
#include <initializer_list>
#include "Core/Base.h"
class FrameBuffer
{

public:
    FrameBuffer(int width, int height, int channels = 4, FrameBufferMode mode = NormalBuffer);
    ~FrameBuffer() = default;
    int &GetHeight();
    int &GetWidth();
    int &GetChannels();
    unsigned char *GetColorBuffer();
    float *GetDepthBuffer();

    void clearColorAndDepthBuffer(const Vec4 &color);
    void SetPixelColor(const unsigned int x, const unsigned int y, const Vec4 &color);

    void SetPixelDepth(const unsigned int x, const unsigned int y, float depth);
    void SetPixelDepth(int ind, float depth);
    float GetPixelDepth(const unsigned int x, const unsigned int y);
    float GetPixelDepth(int ind);

    void SetPixelGBufferData2(const unsigned int x, const unsigned int y, const Vec2 &data);
    void SetPixelGBufferData3(const unsigned int x, const unsigned int y, const Vec3 &data);
    void SetPixelGBufferData4(const unsigned int x, const unsigned int y, const Vec4 &data);
    Vec3 SampleGbufferData3(const unsigned int x, const unsigned int y);
    Vec4 SampleGbufferData4(const unsigned int x, const unsigned int y);
    void ClearGbufferData();
    void ClearGbufferData(const Vec4 &color);

    float *GetGBuffer();

private:
    int m_Width, m_Height, m_Channels;
    std::vector<unsigned char> m_ColorBuffer;
    std::vector<float> m_DepthBuffer;

    // deferred rendering
    std::vector<float> m_gBuffer;
    FrameBufferMode m_mode;
};
#endif // FRAMEBUFFER_H