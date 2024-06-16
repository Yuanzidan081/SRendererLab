#ifndef PIPELINE_H
#define PIPELINE_H
#include "Render/FrameBuffer.h"
#include "Render/DepthBuffer.h"
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
    void DrawTriangle(Vec2i v1, Vec2i v2, Vec2i v3, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    void DrawTriangle(Vec3i v1, Vec3i v2, Vec3i v3, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    /* DrawModel_v1: pure color*/
    void DrawModelPureColor(Model &model, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    /* DrawModel_v2: color with normal
        lightDir: from the object to the light
    */
    void DrawModelNormal(Model &model, Vec3f &lightDir, Vec4f &color, const SRendererType &type = SRendererType::SFill);
    Vec3i CoordWorld2Screen(Vec3f &v);
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
    DepthBuffer *m_depthBuffer;
};

#endif // PIPELINE_H