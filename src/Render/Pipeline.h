#ifndef PIPELINE_H
#define PIPELINE_H
#include "Render/FrameBuffer.h"
#include "Render/Model.h"
#include "Render/NaiveCamera.h"
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
        bool m_geometryClipping;

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
    };
    Pipeline(int width, int height);
    ~Pipeline();
    void initialize();
    // /* DrawModel_v1: pure color*/
    // void DrawModelPureColor(Model &model, Vec4 &color, const PolygonMode &type = PolygonMode::Fill);
    // /* DrawModel_v2: color with normal
    //     lightDir: from the object to the light
    // */
    // void DrawModelNormalWithoutDepthInfo(Model &model, Vec3 &lightDir, Vec4 &color, const PolygonMode &type = PolygonMode::Fill);
    // void DrawModelNormalWithDepthInfo(Model &model, Vec3 &lightDir, Vec4 &color, const PolygonMode &type = PolygonMode::Fill);

    // void DrawModelWithTextureWithViewMat(Model &model, Vec3 &lightDir, const Texture2D &texture, const PolygonMode &type = PolygonMode::Fill);
    // void DrawModelWithTextureWithoutViewMat(Model &model, Vec3 &lightDir, const Texture2D &texture, const PolygonMode &type = PolygonMode::Fill);
    // void DrawModelWithShader(DrawData &drawData, const PolygonMode &type = PolygonMode::Fill);

    // Vec3 CoordWorldFloatToScreenFloat(Vec3 &v);

    // state settings
    void SetDepthTesting(bool open) { m_config.m_depthTesting = open; }
    void SetBackFaceCulling(bool open) { m_config.m_backFaceCulling = open; }
    void SetGeometryClipping(bool open) { m_config.m_geometryClipping = open; }

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

    void SetViewPort(int left, int top, int width, int height)
    {
        m_config.m_viewPortMat.SetViewPort(left, top, width, height);
    }

    // Illumination setting
    void SetShadingMode(ShadingMode mode);
    void SetPolygonMode(PolygonMode mode) { m_config.m_polygonMode = mode; }

    // start the rendering pipeline
    bool DrawMesh();

    // default config
    void SetDefaultConfig();
    // perspectiveDivision
    void perspectiveDivision(VertexOut &target);

    // linear interpolation
    VertexOut lerp(const VertexOut &n1, const VertexOut &n2, double weight);
    // rasterization
    void bresenhamLineRasterization(const VertexOut &from, const VertexOut &to);
    void scanLinePerRow(const VertexOut &left, const VertexOut &right);
    void rasterTopTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3);
    void rasterBottomTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3);
    void edgeWalkingFillRasterization(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3);
    Config m_config;
    // int m_Width;
    // int m_Height;
    // FrameBuffer *m_backBuffer;
    // FrameBuffer *m_frontBuffer;
    // NaiveCamera *m_camera;
    // Mat4x4 m_viewPortMat;
    Mat4x4 m_projectionMat;
    Mat4x4 m_viewMat;
};

#endif // PIPELINE_H