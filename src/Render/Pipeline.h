#ifndef PIPELINE_H
#define PIPELINE_H
#include "Render/FrameBuffer.h"
#include "Render/Model.h"
#include "Render/FPSCamera.h"
#include "Render/Texture2D.h"

#include "Core/Base.h"
#include "Math/MathGroup.h"
#include "Shader/ShaderGroup.h"
class Pipeline
{

public:
    struct Config
    {
        // state settings
        bool m_depthTesting;
        bool m_backFaceCulling;

        // creted by pipeline
        int m_width;
        int m_height;
        FrameBuffer *m_backBuffer;
        FrameBuffer *m_frontBuffer;
        PolygonMode m_polygonMode;
        Mat4x4 m_viewPortMat;
        Vec3 m_eyePos;
        Shader *m_shader;
        std::vector<Texture2D *> m_textureUnits;

        const std::vector<unsigned int> *m_indices;
        const std::vector<Vertex> *m_vertices;
        std::vector<Vec4> m_viewPlaneParameters;
        std::vector<Vec4> m_viewLineParameters;
    };
    Pipeline(int width, int height);
    ~Pipeline();
    void initialize();

    // state settings
    void SetDepthTesting(bool open) { m_config.m_depthTesting = open; }
    void SetBackFaceCulling(bool open) { m_config.m_backFaceCulling = open; }

    // setting texture
    bool BindTexture(const unsigned int &unit);
    bool UnBindTexture(const unsigned int &unit);
    unsigned int LoadTexture(const std::string &path);

    // buffer settings
    void ClearFrameBuffer(const Vec4 &color);
    unsigned char *GetFrameResult();
    void SwapFrameBuffer();
    void SetVertexBuffer(const std::vector<Vertex> *vertices) { m_config.m_vertices = vertices; }
    void SetIndexBuffer(const std::vector<unsigned int> *indices) { m_config.m_indices = indices; }
    int GetWidth()
    {
        return m_config.m_width;
    }
    int GetHeight() { return m_config.m_height; }

    // matrix settings
    void SetModelMatrix(Mat4x4 modelMatrix);
    void SetViewMatrix(Vec3 eye, const Mat4x4 &viewMat);
    void SetViewMatrix(Vec3 eye, Vec3 target, Vec3 up);
    void SetProjectMatrix(float fovy, float aspect, float near, float far);
    void SetProjectMatrix(Mat4x4 mat);

    void SetViewPort(int left, int top, int width, int height)
    {
        m_config.m_viewPortMat.SetViewPort(left, top, width, height);
    }

        // Illumination setting
    void SetShadingMode(ShadingMode mode);
    void SetPolygonMode(PolygonMode mode) { m_config.m_polygonMode = mode; }

    // start the rendering pipeline
    bool DrawMesh();

private:
    // default config
    void SetDefaultConfig();
    // perspectiveDivision
    void PerspectiveDivision(VertexOut &target);

    // linear interpolation
    VertexOut Lerp(const VertexOut &n1, const VertexOut &n2, double weight);

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
    Config m_config;
    Mat4x4 m_projectMatrix;
    Mat4x4 m_viewMatrix;
};

#endif // PIPELINE_H