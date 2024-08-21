#ifndef CONFIG_H
#define CONFIG_H
#include "Base.h"
#include <vector>
#include "Math/MathGroup.h"
#include <QObject>
class Model;
class Vertex;
class FrameBuffer;
class Shader;
class Light;
class EulerFPSCamera;
class CubeMap;
// 创建单例模式让view可以访问当前渲染的状态
class Config : public QObject
{
    Q_OBJECT
private:
    static Config *localInstance;
    Config();

public:
    ~Config();
    Config(const Config &) = delete;
    Config &operator=(const Config &) = delete;

    void AddModel(Model *model);
    void Destroy();
    // state settings
    bool m_depthTesting;
    bool m_backFaceCulling;
    bool m_useSkyBox;
    bool m_viewCull;

    FaceCullMode m_faceCullMode;

    // creted by pipeline
    int m_width;
    int m_height;
    FrameBuffer *m_backBuffer;
    FrameBuffer *m_frontBuffer;
    PolygonMode m_polygonMode;
    Mat4x4 m_viewPortMat;

    Vec3 m_eyePos;
    Shader *m_shader;

    const std::vector<unsigned int> *m_indices;
    const std::vector<Vertex> *m_vertices;
    std::vector<Model *> m_models;
    std::vector<Light *> m_lights;
    // std::vector<Vec4> m_viewPlaneParameters;
    // std::vector<Vec4> m_viewLineParameters;
    EulerFPSCamera *m_fpsCamera;

    // skybox
    Model *m_skyBox;

    // cubeMap
    CubeMap *m_cubeMap;
    static Config *GetInstance();
    void Initialize(int width, int height);
    void NotifyTreeNodeChanged()
    {
        emit TreeNodeChanged();
    }
    void NotifyLightChanged()
    {
        emit LightChanged();
    }
signals:
    void TreeNodeChanged();
    void LightChanged();
};

#endif // CONFIG_H