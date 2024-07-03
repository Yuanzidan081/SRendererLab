#ifndef PIPELINE_H
#define PIPELINE_H
#include "Render/FrameBuffer.h"
#include "Render/Model.h"
#include "Render/Camera.h"
#include "Render/Texture2D.h"

#include "Core/Base.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Algorithm/DrawLine.h"
#include "Algorithm/DrawTriangle.h"
#include "Shader/Shader.h"
#include "Shader/GouraudShader.h"

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

    void DrawModelWithTextureWithViewMat(Model &model, Vec3f &lightDir, const Texture2D &texture, const SRendererType &type = SRendererType::SFill);
    void DrawModelWithTextureWithoutViewMat(Model &model, Vec3f &lightDir, const Texture2D &texture, const SRendererType &type = SRendererType::SFill);
    void DrawModelWithShader(DrawData &drawData, const SRendererType &type = SRendererType::SFill);

    Vec3f CoordWorldFloatToScreenFloat(Vec3f &v);
    void ClearBuffers(const Vec4f &color);
    unsigned char *Output();
    void SwapBuffer();

    int GetWidth() { return m_Width; }
    int GetHeight() { return m_Height; }

    void SetCameraPosZ(float z);
    void SetCameraPos(const Vec3f &eye);
    void SetCameraLookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up);

private:
    int m_Width;
    int m_Height;
    FrameBuffer *m_backBuffer;
    FrameBuffer *m_frontBuffer;
    Camera *m_camera;
    Mat4x4f m_viewPortMat;
    Mat4x4f m_projectionMat;
    Mat4x4f m_viewMat;
};



#endif // PIPELINE_H