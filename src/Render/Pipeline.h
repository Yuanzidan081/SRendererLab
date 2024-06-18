#ifndef PIPELINE_H
#define PIPELINE_H
#include "Render/FrameBuffer.h"
#include "Render/Model.h"
#include "Core/Base.h"
#include "Math/Vec.h"
#include "Algorithm/DrawLine.h"
#include "Algorithm/DrawTriangle.h"
class Pipeline
{

public:
    Pipeline(int width, int height);
    ~Pipeline();

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