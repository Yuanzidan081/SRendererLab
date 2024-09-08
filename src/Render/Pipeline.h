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
    void AddDirectionLight(const Vec3 &dir, const Vec4 &color);
    void AddPointLight(Vec3 pos, Vec3 atte, const Vec4 &color);
    void AddSpotLight(double cutoff,
                      Vec3 pos, Vec3 dir, Vec3 atte, const Vec4 &color);

    // start the rendering pipeline
    void DrawScene();
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

#endif // PIPELINE_H