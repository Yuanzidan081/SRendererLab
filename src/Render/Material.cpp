#include "Material.h"
#include "Shader/Shader.h"
#include "Core/Config.h"
Material::~Material()
{
    Config *config = Config::GetInstance();
    config->m_resourceManager->ReleaseFile(m_mainTexPath);
    config->m_resourceManager->ReleaseFile(m_normalTexPath);
    config->m_resourceManager->ReleaseFile(m_metallicTexPath);
    config->m_resourceManager->ReleaseFile(m_roughnessTexPath);
    config->m_resourceManager->ReleaseFile(m_aoTexPath);
}
void Material::SetupUniform(Uniform &uniform)
{
    Config *config = Config::GetInstance();
    uniform.m_mainTex = config->m_resourceManager->LoadFromFile(m_mainTexPath).get();
    uniform.m_normalTex = config->m_resourceManager->LoadFromFile(m_normalTexPath).get();
    uniform.m_metallicTex = config->m_resourceManager->LoadFromFile(m_metallicTexPath).get();
    uniform.m_roughnessTex = config->m_resourceManager->LoadFromFile(m_roughnessTexPath).get();
    uniform.m_aoTex = config->m_resourceManager->LoadFromFile(m_aoTexPath).get();
    uniform.m_roughness = m_roughness;
    uniform.m_specular = m_specular;
    uniform.m_diffuse = m_diffuse;
    uniform.m_ao = m_ao;
}
