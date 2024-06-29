#include "DrawLine.h"
#include "Render/FrameBuffer.h"
void DrawLineNaive(Vec3f &v1, Vec3f &v2, const Vec4f &color, const void *buffer)
{
    bool steep = false;
    int v1x = v1.x, v1y = v1.y;
    int v2x = v2.x, v2y = v2.y;

    if (std::abs(v1x - v2x) < std::abs(v1y - v2y))
    {
        std::swap(v1x, v1y);
        std::swap(v2x, v2y);
        steep = true;
    }
    if (v1x > v2x)
    { // 当x0>x1时，调换两个点的坐标
        std::swap(v1x, v2x);
        std::swap(v1y, v2y);
    }
    for (int x = v1x; x <= v2x; ++x)
    {
        float t = (float)(x - v1x) / (float)(v2x - v1x);
        int y = v1y * (1.0f - t) + v2y * t;
        if (steep)
            ((FrameBuffer *)buffer)->SetPixelColor(y, x, color);
        else
            ((FrameBuffer *)buffer)->SetPixelColor(x, y, color);
    }
}