#include "Material.h"
#include "Shader/Shader.h"
void Material::SetupUniform(Uniform &uniform)
{
    uniform.m_mainTex = m_mainTex.get();
    uniform.m_normalTex = m_normalTex.get();
}
