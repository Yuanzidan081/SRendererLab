#ifndef SHADER_H
#define SHADER_H
#include "Math/MathGroup.h"
#include "Core/Base.h"
#include "Render/Vertex.h"
#include "Render/Texture2D.h"
#include <vector>
class Light;
class Material;
class Uniform
{
public:
    Vec3 eye;
    Mat4x4 world;
    Mat4x4 normalMatrix;
    Mat4x4 view;
    Mat4x4 project;
    Material *material;
    std::vector<Light *> *lights;
    Texture2D *mainTexture;
    Uniform();
    Uniform(const Mat4x4 m,
            const Mat4x4 v,
            const Mat4x4 p);
};
class Shader
{

public:
    Shader() = default;
    Uniform m_uniform;

    void Destroy() {}
    virtual ~Shader() = default;
    virtual void BindShaderTexture(Texture2D *tex) {}
    virtual VertexOut vertexShader(const Vertex &in) { return VertexOut(); }
    virtual Vec4 fragmentShader(const VertexOut &in) { return Vec4(); }

    void SetUniform(const Uniform &u)
    {
        m_uniform = u;
    }
    virtual void SetEyePos(const Vec3 &eye) {}
    virtual void SetModelMatrix(const Mat4x4 &world) {}
    virtual void SetViewMatrix(const Mat4x4 &view) {}
    virtual void SetProjectMatrix(const Mat4x4 &project) {}
    virtual void SetMaterial(const Material *material) {};
    virtual void SetLight(const std::vector<Light *> *light) {};
};

#endif // SHADER_H