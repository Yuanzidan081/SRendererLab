#include "Material.h"
#include "Shader/Shader.h"
#include "Core/Config.h"
void Material::SetupUniform(Uniform &uniform)
{
    Config *config = Config::GetInstance();
    uniform.m_mainTex = config->m_resourceManager->LoadFromFile(m_mainTexPath).get();
    uniform.m_normalTex = config->m_resourceManager->LoadFromFile(m_normalTexPath).get();
    uniform.m_metallicTex = config->m_resourceManager->LoadFromFile(m_metallicTexPath).get();
    uniform.m_roughness = m_roughness;
    uniform.m_ao = m_ao;
}
