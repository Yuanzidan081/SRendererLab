#include "Shader.h"

Uniform::Uniform() : m_eyePos(Vec3(0.0f, 0.0f, 0.0f)),
                     m_modelMatrix(),
                     m_normalMatrix(),
                     m_viewMatrix(),
                     m_projectMatrix(),
                     m_material(nullptr),
                     m_lights(nullptr),
                     m_mainTex(nullptr),
                     m_cubeMap(nullptr)
{
}

Uniform::Uniform(const Mat4x4 m, const Mat4x4 v, const Mat4x4 p) : m_eyePos(Vec3(0.0f, 0.0f, 0.0f)),
                                                                   m_modelMatrix(m),
                                                                   m_normalMatrix(m.GetInverseTranspose()),
                                                                   m_viewMatrix(v),
                                                                   m_projectMatrix(p),
                                                                   m_material(nullptr),
                                                                   m_lights(nullptr),
                                                                   m_mainTex(nullptr),
                                                                   m_cubeMap(nullptr)

{
}
