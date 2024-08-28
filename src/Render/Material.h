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
    // std::shared_ptr<Texture2D> m_mainTex;
    // std::shared_ptr<Texture2D> m_normalTex;
    // std::shared_ptr<Texture2D> m_metallicTex;

    std::string m_mainTexPath;
    std::string m_normalTexPath;
    std::string m_metallicTexPath;
    std::string m_roughnessTexPath;
    std::string m_aoTexPath;

    Shader *m_shader;

    Material() : m_diffuse(Vec4(1.0, 1.0, 1.0, 1.0)),
                 m_specular(Vec4(1.0, 1.0, 1.0, 1.0)),
                 m_shiness(16), m_roughness(0.99f), m_metallic(1.0f), m_ao(1.0f),
                 m_mainTexPath(), m_normalTexPath(), m_metallicTexPath(), m_shader(nullptr) {}
    Material(const Vec4 &color, const Vec4 &specular, const int &gloss)
        : m_diffuse(color), m_specular(specular), m_shiness(gloss), m_roughness(0.99f), m_metallic(1.0f), m_ao(1.0f),
          m_mainTexPath(), m_normalTexPath(), m_metallicTexPath(), m_roughnessTexPath(), m_shader(nullptr)
    {
    }
    Material(const Material &m) : m_diffuse(m.m_diffuse), m_specular(m.m_specular), m_shiness(m.m_shiness), m_roughness(m.m_roughness), m_metallic(m.m_metallic), m_ao(m.m_ao),
                                  m_mainTexPath(m.m_mainTexPath), m_normalTexPath(m.m_normalTexPath), m_metallicTexPath(m.m_metallicTexPath), m_roughnessTexPath(m.m_roughnessTexPath),
                                  m_shader(m.m_shader)
    {
    }
    ~Material();

    void SetShader(Shader *s)
    {
        m_shader = s;
    }
    void SetMainTexturePath(const std::string &t)
    {
        m_mainTexPath = t;
    }
    void SetNormalTexturePath(const std::string &t)
    {
        m_normalTexPath = t;
    }
    void SetMatallicTexPath(const std::string &t)
    {
        m_metallicTexPath = t;
    }
    void SetRoughnessTexPath(const std::string &t)
    {
        m_roughnessTexPath = t;
    }
    void SetAOTexturePath(const std::string &t)
    {
        m_aoTexPath = t;
    }
    void SetupUniform(Uniform &uniform);
};
#endif // MATERIAL_H