#ifndef PIPELINE_H
#define PIPELINE_H
#include "FrameBuffer.h"
#include "Model.h"
#include "FPSCamera.h"
#include "Texture2D.h"
#include "Light.h"

#include "Core/Base.h"
#include "Math/MathGroup.h"
#include "Shader/ShaderGroup.h"
#include "Core/Config.h"
class Pipeline
{

public:
    Pipeline(int width, int height);
    ~Pipeline();

    // state settings
    void SetDepthTesting(bool open) { m_config->m_depthTesting = open; }
    void SetBackFaceCulling(bool open) { m_config->m_backFaceCulling = open; }

    // buffer settings
    void ClearFrameBuffer(const Vec4 &color);
    unsigned char *GetFrameResult();
    void SwapFrameBuffer();
    void SetVertexBuffer(const std::vector<Vertex> *vertices) { m_config->m_vertices = vertices; }
    void SetIndexBuffer(const std::vector<unsigned int> *indices) { m_config->m_indices = indices; }
    int GetWidth()
    {
        return m_config->m_width;
    }
    int GetHeight() { return m_config->m_height; }

    // Illumination setting
    void SetPolygonMode(PolygonMode mode) { m_config->m_polygonMode = mode; }
    // Light
    void AddDirectionLight(Vec3 amb, Vec3 diff, Vec3 spec, Vec3 dir);
    void AddPointLight(Vec3 amb, Vec3 diff, Vec3 spec, Vec3 pos, Vec3 atte);
    void AddSpotLight(Vec3 amb, Vec3 diff, Vec3 spec, double cutoff,
                      Vec3 pos, Vec3 dir, Vec3 atte);

    // start the rendering pipeline
    void DrawScene();
    void DrawMesh();
    void DrawModel(Model *model);
    void DrawObject(const Object &obj, Uniform &u);
    Config *m_config;

private:
    // perspectiveDivision
    void PerspectiveDivision(VertexOut &target);

    // linear interpolation
    VertexOut Lerp(const VertexOut &n1, const VertexOut &n2, double weight);

    // clipping and culling
    bool BackFaceClipping(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3);
    bool ViewCulling(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3);
    void UpdateViewPlanes();
    void ViewingFrustumPlanes(std::vector<Vec4> &planeParameter, const Mat4x4 &vp);
    bool IsInsideFrustum(const Vec3 &v, const Vec4 &planeParameter);
    bool IsInsideViewPort(const Vec4 &lineParameter, const Vec4 &p);
    bool Pipeline::IsAllVertexsInsideViewPort(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3);
    VertexOut GetViewPortIntersect(const VertexOut &v1, const VertexOut &v2, const Vec4 &lineParameter);
    std::vector<VertexOut> SutherlandHodgeman(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3);

    // rasterization
    void BresenhamLineRasterization(const VertexOut &from, const VertexOut &to);
    void ScanLinePerRow(const VertexOut &left, const VertexOut &right);
    void RasterTopTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3);
    void RasterBottomTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3);
    void EdgeWalkingFillRasterization(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3);

    Mat4x4 m_projectMatrix;
    Mat4x4 m_viewMatrix;
};

#endif // PIPELINE_H