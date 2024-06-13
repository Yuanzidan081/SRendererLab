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
    void ClearBuffers(const Vec4f &color);
    void DrawPixels(const unsigned int x, const unsigned int y, const Vec4f &color);

private:
    int m_Width, m_Height, m_Channels;
    std::vector<unsigned char> m_ColorBuffer;
};
#endif // FRAMEBUFFER_H