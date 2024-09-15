#ifndef COREPIPELINE_H
#define COREPIPELINE_H
#include "FrameBuffer.h"
#include "Model.h"
#include "FPSCamera.h"
#include "Texture.h"
#include "Light.h"

#include "Core/Base.h"
#include "Math/MathGroup.h"
#include "Shader/ShaderGroup.h"
#include "Core/Config.h"
class CorePipeline
{

public:
    CorePipeline(int width, int height);
    ~CorePipeline();

    // buffer settings
    void ClearFrameBuffer(const Vec4 &color);
    unsigned char *GetFrameResult();
    float *GetGBufferPositionResult();
    float *GetGbufferColorResult();
    float *GetGbufferNormalResult();

    void RenderLighting();
    void SwapFrameBuffer();

    // Illumination setting
    void SetPolygonMode(PolygonMode mode) { m_config->m_polygonMode = mode; }
    // Light
    // void AddDirectionLight(const Vec3 &dir, const Vec4 &color);
    // void AddPointLight(Vec3 pos, Vec3 atte, const Vec4 &color);
    // void AddSpotLight(double cutoff,
    //                   Vec3 pos, Vec3 dir, Vec3 atte, const Vec4 &color);

    // start the rendering pipeline
    void DrawScene(const Vec4 &clearColor);
    void DrawSceneAllForwardMode();
    void DrawSceneMixForwardModeDeferredMode(const Vec4 &clearColor);
    void DrawMesh();
    void DrawTriangle(Vertex &p1, Vertex &p2, Vertex &p3);
    void DrawModel(const std::shared_ptr<Model> &model);
    void DrawSkyBox(Model *model);
    void DrawObject(const Object &obj, Uniform &u);

    void RasterTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3);
    std::shared_ptr<Config> m_config;

private:
    // perspectiveDivision
    void PerspectiveDivision(VertexOut &target);

    // rasterization
    void BresenhamLineRasterization(const VertexOut &from, const VertexOut &to);
    void ScanLinePerRow(const VertexOut &left, const VertexOut &right);
    void PerspectiveRestore(VertexOut &current);
    void RasterTopTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3);
    void RasterBottomTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3);
    void EdgeWalkingFillRasterization(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3);

    Mat4x4 m_projectMatrix;
    Mat4x4 m_viewMatrix;
};

#endif // COREPIPELINE_H