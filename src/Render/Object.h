#ifndef OBJECT_H
#define OBJECT_H
#include "Mesh.h"
#include "Material.h"
#include <memory>
class Object
{
public:
    Mesh m_mesh;
    Material m_material;

    Object() = default;
    ~Object() = default;
    Object(const Mesh m, const Material mat) : m_mesh(m), m_material(mat) {}
    Object(const Object &obj) : m_mesh(obj.m_mesh), m_material(obj.m_material)
    {
    }
    Object &operator()(const Object &obj)
    {
        if (&obj == this)
            return *this;
        m_mesh = obj.m_mesh;
        m_material = obj.m_material;
        return *this;
    }
};
#endif // OBJECT_H