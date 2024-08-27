#ifndef MATERIAL_H
#define MATERIAL_H
#include "Math/Vec4.h"
#include "Render/Texture2D.h"
#include "Shader/Shader.h"
class Shader;
class Uniform;
class Material
{
public:
    Vec4 m_diffuse;
    Vec4 m_specular;
    int m_shiness;
    float m_roughness;
    float m_metallic;
    float m_ao;
    std::shared_ptr<Texture2D> m_mainTex;
    std::shared_ptr<Texture2D> m_normalTex;
    std::shared_ptr<Texture2D> m_metallicTex;
    Shader *m_shader;

    Material() : m_diffuse(Vec4(1.0, 1.0, 1.0, 1.0)),
                 m_specular(Vec4(1.0, 1.0, 1.0, 1.0)),
                 m_shiness(16), m_roughness(0.99f), m_metallic(1.0f), m_ao(1.0f),
                 m_mainTex(nullptr), m_normalTex(nullptr), m_metallicTex(nullptr) {}
    Material(const Vec4 &color, const Vec4 &specular, const int &gloss)
        : m_diffuse(color), m_specular(specular), m_shiness(gloss), m_roughness(0.99f), m_metallic(1.0f), m_ao(1.0f),
          m_mainTex(nullptr), m_normalTex(nullptr), m_metallicTex(nullptr), m_shader(nullptr)
    {
    }
    Material(const Material &m) : m_diffuse(m.m_diffuse), m_specular(m_specular), m_shiness(m.m_shiness), m_roughness(m.m_roughness), m_metallic(m.m_metallic), m_ao(m.m_ao),
                                  m_mainTex(m.m_mainTex), m_normalTex(m.m_normalTex), m_metallicTex(m.m_metallicTex), m_shader(m.m_shader)
    {
    }
    ~Material()
    {
    }
    void SetShader(Shader *s)
    {
        m_shader = s;
    }
    void SetMainTexture(std::shared_ptr<Texture2D> &t)
    {
        m_mainTex = t;
    }
    void SetNormalTexture(std::shared_ptr<Texture2D> &t)
    {
        m_normalTex = t;
    }
    void SetMatallicTex(std::shared_ptr<Texture2D> &t)
    {
        m_metallicTex = t;
    }
    void SetupUniform(Uniform &uniform);
};
#endif // MATERIAL_H