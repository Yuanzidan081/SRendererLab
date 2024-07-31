#ifndef PIPELINE_H
#define PIPELINE_H
#include "Render/FrameBuffer.h"
#include "Render/Model.h"
#include "Render/NaiveCamera.h"
#include "Render/Texture2D.h"

#include "Core/Base.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Algorithm/DrawLine.h"
#include "Algorithm/DrawTriangle.h"
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
        Mat4x4f m_viewPortMat;
        Vec3f m_eyePos;
        Shader *m_shader;
        std::vector<Texture2D *> m_textureUnits;
    };
    Pipeline(int width, int height);
    ~Pipeline();
    void initialize();
    /* DrawModel_v1: pure color*/
    void DrawModelPureColor(Model &model, Vec4f &color, const PolygonMode &type = PolygonMode::Fill);
    /* DrawModel_v2: color with normal
        lightDir: from the object to the light
    */
    void DrawModelNormalWithoutDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const PolygonMode &type = PolygonMode::Fill);
    void DrawModelNormalWithDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const PolygonMode &type = PolygonMode::Fill);

    void DrawModelWithTextureWithViewMat(Model &model, Vec3f &lightDir, const Texture2D &texture, const PolygonMode &type = PolygonMode::Fill);
    void DrawModelWithTextureWithoutViewMat(Model &model, Vec3f &lightDir, const Texture2D &texture, const PolygonMode &type = PolygonMode::Fill);
    void DrawModelWithShader(DrawData &drawData, const PolygonMode &type = PolygonMode::Fill);

    Vec3f CoordWorldFloatToScreenFloat(Vec3f &v);

    // state settings
    void SetDepthTesting(bool open) { m_config.m_depthTesting = open; }
    void SetBackFaceCulling(bool open) { m_config.m_backFaceCulling = open; }
    void SetGeometryClipping(bool open) { m_config.m_geometryClipping = open; }

    // setting texture
    bool BindTexture(const unsigned int &unit);
    bool UnBindTexture(const unsigned int &unit);
    unsigned int LoadTexture(const std::string &path);

    // buffer settings
    void CleraFrameBuffer(const Vec4f &color);
    unsigned char *GetFrameResult();
    void SwapFrameBuffer();

    int GetWidth() { return m_config.m_width; }
    int GetHeight() { return m_config.m_height; }

    // matrix settings
    void SetModelMatrix(Mat4x4f modelMatrix);
    void SetViewMatrix(Vec3f eye, const Mat4x4f &viewMat);
    void SetViewMatrix(Vec3f eye, Vec3f target, Vec3f up);
    void SetProjectMatrix(float fovy, float aspect, float near, float far);

    void SetProjectMatrix(float z);
    void SetViewPort(int left, int top, int width, int height)
    {
        m_config.m_viewPortMat = Mat4x4GetViewport(left, top, width, height);
    }

    // Illumination setting
    void SetShadingMode(ShadingMode &&mode);
    void SetPolygonMode(PolygonMode mode) { m_config.m_polygonMode = mode; }

    /*     void SetCameraPosZ(float z);
        void SetCameraPos(const Vec3f &eye);

        void SetCameraLookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up);
     */
private:
    void SetDefaultConfig();

    Config m_config;
    // int m_Width;
    // int m_Height;
    // FrameBuffer *m_backBuffer;
    // FrameBuffer *m_frontBuffer;
    NaiveCamera *m_camera;
    // Mat4x4f m_viewPortMat;
    Mat4x4f m_projectionMat;
    Mat4x4f m_viewMat;
};

#endif // PIPELINE_H