#ifndef MODEL_H
#define MODEL_H
#include "Math/MathGroup.h"
#include <vector>
#include <string>
#include "Texture.h"
#include "Object.h"
#include <initializer_list>
#include "Core/Transformation.h"
// 单个顶点的属性
#include "Math/Vec3.h"
class Model
{

    struct Transform
    {
        Vec3 position; // x, y, z
        Vec3 rotation; // x, y, z
        Vec3 scale;    // x, y, z
    };

public:
    std::vector<Object> m_objects;
    Transform m_transform;
    std::string m_name = "Unknown";
    int m_objectNum;
    int m_vertexNum;
    int m_triangleNum;
    Model() : m_objectNum(0), m_minPoint(Vec3(+10000000000, +10000000000, +10000000000)),
              m_maxPoint(Vec3(-10000000000, -10000000000, -10000000000)), m_vertexNum(0), m_triangleNum(0) {}
    ~Model() = default;
    Model(const std::string &path, const std::string &name = "Unknown");
    Model(Mesh *meshPtr, const std::string &name = "Unknown");

    Model(const Model &model, const std::string &name = "Unknown")
        : m_objects(model.m_objects), m_objectNum(model.m_objectNum),
          m_minPoint(model.m_minPoint), m_maxPoint(model.m_maxPoint),
          m_transform(model.m_transform), m_vertexNum(model.m_vertexNum), m_triangleNum(model.m_triangleNum)
    {
        if (name != "Unknown")
            m_name = name;
        else
            m_name = model.m_name;
    }

    Model &operator=(const Model &model)
    {
        if (&model == this)
            return *this;
        m_objects = model.m_objects;
        m_objectNum = model.m_objectNum;
        m_minPoint = model.m_minPoint;
        m_maxPoint = model.m_maxPoint;
        m_name = model.m_name;
        m_vertexNum = model.m_vertexNum;
        m_triangleNum = model.m_triangleNum;
        return *this;
    }
    void SetMaterial(const int &id, std::shared_ptr<Material> m)
    {
        m_objects[id].m_material = m;
    }
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

    Mat4x4 GetTransform()
    {
        return (Transformation::GetTranslate(m_transform.position) *
                Transformation::GetRotationZ(m_transform.rotation[2]) *
                Transformation::GetRotationY(m_transform.rotation[1]) *
                Transformation::GetRotationX(m_transform.rotation[0]) *
                Transformation::GetScale(m_transform.scale));
    }

    void SetRelScale(Vec3 &s);
    void SetScale(Vec3 &s);
    void SetRotation(Vec3 &r) { m_transform.rotation = r; }
    void SetTranslate(Vec3 &p) { m_transform.position = p; }

private:
    void BuildTangents(std::vector<Vec4> &tangents, Mesh *mesh, bool hasFileTangent, std::vector<int> &vertID);
    Vec3 m_minPoint,
        m_maxPoint;
};

#endif // MODEL_H