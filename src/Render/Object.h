#ifndef OBJECT_H
#define OBJECT_H
#include "Mesh.h"
#include "Material.h"
#include <memory>
class Object
{
public:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;

    Object() : m_mesh(std::make_shared<Mesh>()), m_material(std::make_shared<Material>())
    {
    }
    ~Object()
    {
    }
    // Object(Mesh *m, Material *mat) : m_mesh(std::make_shared<Mesh>(*m)),
    //                                  m_material(std::make_shared<Material>(*mat)) {}
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
    Material *GetMaterial() const
    {
        return m_material.get();
    }
    Texture2D *GetMainTex() const
    {
        return m_material->m_mainTex.get();
    }
    Shader *GetShader() const
    {
        return m_material->m_shader;
    }
};
#endif // OBJECT_H