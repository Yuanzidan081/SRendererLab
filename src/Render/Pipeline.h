#ifndef PIPELINE_H
#define PIPELINE_H
#include "Render/FrameBuffer.h"
#include "Core/Base.h"
#include "Math/Vec.h"
class Pipeline
{

public:
    Pipeline(int width, int height);
    ~Pipeline();

    void DrawLine(int x1, int y1, int x2, int y2, Vec4f &color);
    void ClearBuffers(const Vec4f &color);
    unsigned char *Output();
    void SwapBuffer();
    void Init();
    int GetWidth() { return m_Width; }
    int GetHeight() { return m_Height; }
    void CheckResize();

private:
    int m_Width;
    int m_Height;
    FrameBuffer *m_backBuffer;
    FrameBuffer *m_frontBuffer;
};

#endif // PIPELINE_H