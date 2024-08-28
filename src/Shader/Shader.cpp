#include "Shader.h"
// #include "Core/Config.h"
Uniform::Uniform() : m_eyePos(Vec3(0.0f, 0.0f, 0.0f)),
                     m_modelMatrix(),
                     m_normalMatrix(),
                     m_viewMatrix(),
                     m_projectMatrix(),
                     m_ambient(),
                     m_roughness(0.99f),
                     m_metallic(1.0f),
                     m_ao(1.0f),
                     //  m_material(nullptr),
                     m_diffuse(Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
                     m_specular(Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
                     m_shiness(16),
                     m_lights(nullptr),
                     m_mainTex(nullptr),
                     m_normalTex(nullptr),
                     m_metallicTex(nullptr),
                     m_roughnessTex(nullptr),
                     m_aoTex(nullptr),
                     m_cubeMap(nullptr)
{
}

Uniform::Uniform(const Mat4x4 m, const Mat4x4 v, const Mat4x4 p) : m_eyePos(Vec3(0.0f, 0.0f, 0.0f)),
                                                                   m_modelMatrix(m),
                                                                   m_normalMatrix(m.GetInverseTranspose().GetMat3x3()),
                                                                   m_viewMatrix(v),
                                                                   m_projectMatrix(p),
                                                                   m_ambient(),
                                                                   m_roughness(0.99f),
                                                                   m_metallic(1.0f),
                                                                   m_ao(1.0f),
                                                                   m_diffuse(Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
                                                                   m_specular(Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
                                                                   m_shiness(16),
                                                                   // m_material(nullptr),
                                                                   m_lights(nullptr),
                                                                   m_mainTex(nullptr),
                                                                   m_normalTex(nullptr),
                                                                   m_metallicTex(nullptr),
                                                                   m_roughnessTex(nullptr),
                                                                   m_aoTex(nullptr),
                                                                   m_cubeMap(nullptr)

{
}
