#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "Math/Mat.h"
#include <vector>
#include <initializer_list>

class FrameBuffer
{

public:
    FrameBuffer(int width, int height);
    ~FrameBuffer() = default;
    int &GetHeight();
    int &GetWidth();
    int &GetChannels();
    unsigned char *GetColorBuffer();
    float *GetDepthBuffer();

    void clearColorAndDepthBuffer(const Vec4f &color);
    void SetPixelColor(const unsigned int x, const unsigned int y, const Vec4f &color);

    void SetPixelDepth(const unsigned int x, const unsigned int y, float depth);
    void SetPixelDepth(int ind, float depth);
    float GetPixelDepth(const unsigned int x, const unsigned int y);
    float GetPixelDepth(int ind);

private:
    int m_Width, m_Height, m_Channels;
    std::vector<unsigned char> m_ColorBuffer;
    std::vector<float> m_DepthBuffer;
};
#endif // FRAMEBUFFER_H