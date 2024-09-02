#ifndef CONFIG_H
#define CONFIG_H
#include "Base.h"
#include <vector>
#include "Math/MathGroup.h"
#include <QObject>
#include "Render/ResourceManager.h"
#include <memory>
#include "UI/Common/CommandBase.h"
class Model;
class Vertex;
class FrameBuffer;
class Shader;
class Light;
class EulerFPSCamera;
class CubeMap;
class LightGroup;

class Config : public QObject, public Proxy_PropertyNotification<Config>, public Proxy_CommandNotification<Config>
{
    Q_OBJECT
private:
    static std::shared_ptr<Config> localInstance;

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

    // pipeline
    Shader *m_shader;
    const std::vector<unsigned int> *m_indices;
    const std::vector<Vertex> *m_vertices;

    std::vector<Model *> m_models;
    std::vector<std::shared_ptr<Light>> m_lights;
    EulerFPSCamera *m_fpsCamera;
    ResourceManager *m_resourceManager;
    // LightGroup *m_lightGroup;

    // cubeMap
    CubeMap *m_cubeMap;
    Model *m_skyBox; // skybox

    // eveironment Light
    Vec4 m_ambient;

    // provide for view
    std::shared_ptr<Light> m_currentLight;

    // static Config *GetInstance();
    static std::shared_ptr<Config> GetInstance();
    void Initialize(int width, int height);
    void NotifyTreeNodeChanged()
    {
        emit TreeNodeChanged();
    }
    void NotifyLightChanged()
    {
        emit LightChanged();
    }
    void NewLightProperty(int lightIndex);

    std::shared_ptr<Light> &GetCurrentLight();
signals:
    void TreeNodeChanged();
    void LightChanged();
};

void deleter(Config *ptr);
#endif // CONFIG_H