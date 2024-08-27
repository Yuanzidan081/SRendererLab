#include "Material.h"
#include "Shader/Shader.h"
void Material::SetupUniform(Uniform &uniform)
{
    uniform.m_mainTex = m_mainTex.get();
    uniform.m_normalTex = m_normalTex.get();
    uniform.m_metallicTex = m_metallicTex.get();
    uniform.m_roughness = m_roughness;
    uniform.m_ao = m_ao;
}
