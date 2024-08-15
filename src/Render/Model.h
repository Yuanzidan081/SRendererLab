#ifndef MODEL_H
#define MODEL_H
#include "Math/MathGroup.h"
#include <vector>
#include <string>
#include "Texture2D.h"
#include "Object.h"
#include <initializer_list>
// 单个顶点的属性

class Model
{

public:
    std::vector<Object> m_objects;
    std::string m_name = "Unknown";
    int m_objectNum;
    Model() : m_objectNum(0), m_minPoint(Vec3(+10000000000, +10000000000, +10000000000)),
              m_maxPoint(Vec3(-10000000000, -10000000000, -10000000000)) {}
    ~Model() = default;
    Model(const std::string &path);
    Model(Mesh *meshPtr, const std::string &name = "Unknown");
    Model(const Model &model)
        : m_objects(model.m_objects), m_objectNum(model.m_objectNum),
          m_minPoint(model.m_minPoint), m_maxPoint(model.m_maxPoint), m_name(model.m_name) {}

    Model &operator=(const Model &model)
    {
        if (&model == this)
            return *this;
        m_objects = model.m_objects;
        m_objectNum = model.m_objectNum;
        m_minPoint = model.m_minPoint;
        m_maxPoint = model.m_maxPoint;
        m_name = model.m_name;
        return *this;
    }
    Mat4x4 SetSize(float sx, float sy, float sz) const;
    void SetMaterial(const int &id, std::shared_ptr<Material> m)
    {
        m_objects[id].m_material = m;
    }
    // Model &operator=(const Model &model);
    void AddObject(const std::string &path);
    void Model::AddObject(Object &obj);
    void SetModelName(const std::string &name)
    {
        m_name = name;
    }
    void SetShader(Shader *s)
    {
        for (auto &obj : m_objects)
        {
            obj.m_material->SetShader(s);
        }
    }

private:
    Vec3 m_minPoint,
        m_maxPoint;
};

#endif // MODEL_H