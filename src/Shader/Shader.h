#ifndef SHADER_H
#define SHADER_H
#include "Math/MathGroup.h"
#include "Core/Base.h"
#include "Render/Vertex.h"
#include "Render/Texture.h"
#include <vector>
#include <memory>
class Light;
class Material;
class LightGroup;
class Uniform
{
public:
    Vec3 m_eyePos;
    Mat4x4 m_modelMatrix;
    Mat3x3 m_normalMatrix;
    Mat4x4 m_viewMatrix;
    Mat4x4 m_projectMatrix;
    // material
    Vec4 m_ambient;
    float m_roughness;
    float m_metallic;
    float m_ao;
    Vec3 m_emission;

    Vec4 m_diffuse;
    Vec4 m_specular;
    float m_shiness;

    // Material *m_material;
    std::vector<std::shared_ptr<Light>> *m_lights;
    // LightGroup *m_lights;
    Texture *m_mainTex;
    Texture *m_normalTex;
    Texture *m_metallicTex;
    Texture *m_roughnessTex;
    Texture *m_aoTex;
    Texture *m_emissionTex;

    std::shared_ptr<CubeMap> m_cubeMap;
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
    virtual void BindShaderTexture(Texture *tex) {}
    virtual VertexOut VertexShader(const Vertex &in) { return VertexOut(); }
    virtual Vec4 FragmentShader(const VertexOut &in) { return Vec4(); }

    void SetUniform(Uniform *u)
    {
        m_uniform = u;
    }
};

#endif // SHADER_H