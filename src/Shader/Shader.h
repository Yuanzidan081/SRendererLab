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
    Vec3 m_eyePos;
    Mat4x4 m_modelMatrix;
    Mat3x3 m_normalMatrix;
    Mat4x4 m_viewMatrix;
    Mat4x4 m_projectMatrix;
    Material *m_material;
    std::vector<Light *> *m_lights;
    Texture2D *m_mainTex;
    Texture2D *m_normalTex;
    CubeMap *m_cubeMap;
    Uniform();
    Uniform(const Mat4x4 m,
            const Mat4x4 v,
            const Mat4x4 p);
};
class Shader
{

public:
    Shader() = default;
    Uniform *m_uniform;

    virtual void Destroy() {}
    virtual ~Shader() = default;
    virtual void BindShaderTexture(Texture2D *tex) {}
    virtual VertexOut vertexShader(const Vertex &in) { return VertexOut(); }
    virtual Vec4 fragmentShader(const VertexOut &in) { return Vec4(); }

    void SetUniform(Uniform *u)
    {
        m_uniform = u;
    }
};

#endif // SHADER_H