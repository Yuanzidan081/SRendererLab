#ifndef PIPELINE_H
#define PIPELINE_H
#include "Render/FrameBuffer.h"
#include "Render/Model.h"
#include "Core/Base.h"
#include "Math/Vec.h"
enum class SRendererType
{
    SLine = 0,
    SFill
};
class Pipeline
{

public:
    Pipeline(int width, int height);
    ~Pipeline();

    void DrawLine(Vec3i v1, Vec3i v2, Vec4f &color);
    void DrawTriangleWithoutDepthInfo(Vec2i v1, Vec2i v2, Vec2i v3, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    void DrawTriangleWithoutDepthInfo(Vec3i v1, Vec3i v2, Vec3i v3, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    void DrawTriangleLineModeWithoutDepthInfo(Vec3i &v1, Vec3i &v2, Vec3i &v3, Vec4f &color);
    void DrawTriangleFillModeWithoutDepthInfo(Vec3i &v1, Vec3i &v2, Vec3i &v3, Vec4f &color); // 直接传递像素的坐标即可，未考虑像素的信息

    void DrawTriangleWithDepthInfo(Vec2i v1, Vec2i v2, Vec2i v3, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    void DrawTriangleWithDepthInfo(Vec3i v1, Vec3i v2, Vec3i v3, Vec4f &color, const SRendererType &type);
    void DrawTriangleFillModeWithDepthInfo(Vec3i &v1, Vec3i &v2, Vec3i &v3, Vec4f &color); // 考虑了深度信息绘制三角形

    /* DrawModel_v1: pure color*/
    void DrawModelPureColor(Model &model, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    /* DrawModel_v2: color with normal
        lightDir: from the object to the light
    */
    void DrawModelNormalWithoutDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    void DrawModelNormalWithDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    Vec3i CoordWorldFloatToScreenInt(Vec3f &v);
    Vec3f CoordWorldFloatToScreenFloat(Vec3f &v);
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