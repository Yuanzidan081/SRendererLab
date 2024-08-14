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
    Model() : m_objectNum(0) {}
    ~Model() = default;
    Model(const std::string &path);
    Model(const std::initializer_list<std::string> &list);

    Model(const Model &model)
        : m_objects(model.m_objects), m_objectNum(model.m_objectNum),
          m_minPoint(model.m_minPoint), m_maxPoint(model.m_maxPoint), m_name(model.m_name) {}
    Model(const Mesh *mesh);
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
    void SetMaterial(const int &id, Material *m)
    {
        m_objects[id].m_material = m;
    }
    // Model &operator=(const Model &model);
    void AddObjModel(const std::string &path);
    void Model::AddObjModel(Object &obj);
    void SetModelName(const std::string &name)
    {
        m_name = name;
    }

private:
    Vec3 m_minPoint,
        m_maxPoint;
};

#endif // MODEL_H