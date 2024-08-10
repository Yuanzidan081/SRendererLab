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
    int m_objectNum;
    Model() : m_objectNum(0) {}
    ~Model() = default;
    Model(const std::string &path);
    Model(const std::initializer_list<std::string> &list);

    Model(const Model &model)
        : m_objects(model.m_objects), m_objectNum(model.m_objectNum),
          m_minPoint(model.m_minPoint), m_maxPoint(model.m_maxPoint) {}
    Model &operator=(const Model &model)
    {
        if (&model == this)
            return *this;
        m_objects = model.m_objects;
        return *this;
    }
    Mat4x4 SetSize(float sx, float sy, float sz) const;
    void SetMaterial(const int &id, const Material &m)
    {
        m_objects[id].m_material = m;
    }
    // Model &operator=(const Model &model);
    void AddObjModel(const std::string &path);
    void AddObjModel(const std::initializer_list<std::string> &list);

private:
    Vec3 m_minPoint, m_maxPoint;
};

#endif // MODEL_H