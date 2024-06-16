#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H
#include "Math/Mat.h"
#include <vector>
#include <initializer_list>

class DepthBuffer
{

public:
    DepthBuffer(int width, int height);
    ~DepthBuffer() = default;
    int &GetHeight();
    int &GetWidth();
    float *GetDepthBuffer();
    void ClearBuffers();
    void SetPixelDepth(const unsigned int x, const unsigned int y, float depth);

private:
    int m_Width, m_Height;
    std::vector<float> m_DepthBuffer;
};
#endif // DEPTHBUFFER_H