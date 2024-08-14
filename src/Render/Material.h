#ifndef MATERIAL_H
#define MATERIAL_H
#include "Math/Vec4.h"
#include "Render/Texture2D.h"
#include "Shader/Shader.h"

class Shader;
class Material
{
public:
    Vec4 m_diffuse;
    Vec4 m_specular;
    int m_gloss;
    Texture2D *m_mainTex;
    Shader *m_shader;

    Material() : m_diffuse(Vec4(1.0, 1.0, 1.0, 1.0)),
                 m_specular(Vec4(1.0, 1.0, 1.0, 1.0)),
                 m_gloss(16),
                 m_mainTex(nullptr) {}
    Material(const Vec4 &color, const Vec4 &specular, const int &gloss)
        : m_diffuse(color), m_specular(specular), m_gloss(gloss),
          m_mainTex(nullptr)
    {
    }
    ~Material()
    {
        if (m_mainTex)
            delete m_mainTex;
        m_mainTex = nullptr;
    }
    void SetShader(Shader *s)
    {
        m_shader = s;
    }
    void SetTexture(Texture2D *t)
    {
        m_mainTex = t;
    }
};
#endif // MATERIAL_H