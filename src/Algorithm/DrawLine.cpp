#include "DrawLine.h"
#include "Render/FrameBuffer.h"
void DrawLineNaive(Vec3i v1, Vec3i v2, const Vec4f &color, const void *buffer)
{
    bool steep = false;
    if (std::abs(v1.x - v2.x) < std::abs(v1.y - v2.y))
    {
        std::swap(v1.x, v1.y);
        std::swap(v2.x, v2.y);
        steep = true;
    }
    if (v1.x > v2.x)
    { // 当x0>x1时，调换两个点的坐标
        std::swap(v1, v2);
    }
    for (int x = v1.x; x <= v2.x; ++x)
    {
        float t = (float)(x - v1.x) / (float)(v2.x - v1.x);
        int y = v1.y * (1.0f - t) + v2.y * t;
        if (steep)
            ((FrameBuffer *)buffer)->SetPixelColor(y, x, color);
        else
            ((FrameBuffer *)buffer)->SetPixelColor(x, y, color);
    }
}