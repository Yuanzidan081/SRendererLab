#include "PBRShader.h"
#include "Render/Material.h"
#include "Render/Light.h"
#include "Algorithm/ToneMapping.h"
PBRShader *PBRShader::s_shader = nullptr;

float PBRShader::D_GGX_TR(const Vec3 &nDir, const Vec3 &hDir, float roughness)
{

    float roughness2 = roughness * roughness;
    // float a2 = roughness2 * roughness2;
    float NdotH = std::max(nDir.GetDotProduct(hDir), 0.0f);
    float NdotH2 = NdotH * NdotH;

    float nom = roughness2;
    // float nom = a2;
    float denom = (NdotH2 * (roughness2 - 1.0f) + 1.0f);
    denom = M_PI * denom * denom;

    return nom / denom;
}

float PBRShader::GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float nom = NdotV;
    float denom = NdotV * (1.0f - k) + k;
    return nom / denom;
}
// dirction k = (roughness + 1)^2/8 IBL: (roughness)^2/2
float PBRShader::GeometrySmith(const Vec3 &nDir, const Vec3 &vDir, const Vec3 &lDir, float k)
{

    float NdotV = std::max(nDir.GetDotProduct(vDir), 0.0f);
    float NdotL = std::max(nDir.GetDotProduct(lDir), 0.0f);
    float ggx1 = GeometrySchlickGGX(NdotV, k);
    float ggx2 = GeometrySchlickGGX(NdotL, k);

    return ggx1 * ggx2;
}

Vec3 PBRShader::fresnelSchlick(float cosTheta, const Vec3 &F0)
{
    return F0 + (-F0 + 1.0f) * pow(Clamp(1.0f - cosTheta, 0.0f, 1.0f), 5.0f);
}

PBRShader *PBRShader::GetInstance()
{
    if (s_shader == nullptr)
        s_shader = new PBRShader();
    return s_shader;
}

void PBRShader::Destroy()
{
    m_uniform = nullptr;

    if (s_shader)
        delete s_shader;
    s_shader = nullptr;
}

VertexOut PBRShader::VertexShader(const Vertex &in)
{
    VertexOut result;
    result.worldPos = m_uniform->m_modelMatrix * in.position;
    result.clipPos = m_uniform->m_projectMatrix * m_uniform->m_viewMatrix * result.worldPos;
    result.color = in.color;
    result.texcoord = in.texcoord;
    result.normal = m_uniform->m_normalMatrix * Vec4(in.normal);
    Vec3 tangent = Normalize(m_uniform->m_modelMatrix.GetMat3x3() * in.tangent);
    Vec3 binormal = Normalize(result.normal.GetCrossProduct(tangent));
    result.TBN = Mat3x3(tangent, binormal, result.normal);

    return result;
}

Vec4 PBRShader::FragmentShader(const VertexOut &in)
{
    // worldNormal
    Vec3 worldNormal;
    if (m_uniform->m_normalTex)
    {
        worldNormal = Normalize(in.TBN * (m_uniform->m_normalTex->SampleTexture(in.texcoord) * 2.0f - 1.0f));
    }
    else
        worldNormal = Normalize(in.normal);
    // worldViewDir
    Vec3 worldViewDir = Normalize(m_uniform->m_eyePos - in.worldPos);

    // Vec3 albedo = in.color;
    // albedo
    Vec3 albedo = Vec3(0.5f, 0.0f, 0.0f);
    if (m_uniform->m_mainTex)
        albedo = m_uniform->m_mainTex->SampleTexture(in.texcoord);
    // metallic
    float metallic = m_uniform->m_metallic;
    if (m_uniform->m_metallicTex)
        metallic = m_uniform->m_metallicTex->SampleTexture(in.texcoord).r;
    float roughness = m_uniform->m_roughness;
    if (m_uniform->m_roughnessTex)
        roughness = m_uniform->m_roughnessTex->SampleTexture(in.texcoord).r;
    float ao = m_uniform->m_ao;
    if (m_uniform->m_aoTex)
        ao = m_uniform->m_aoTex->SampleTexture(in.texcoord).r;
    // Fo for frenel function
    Vec3 F0 = Vec3(0.04f);
    F0 = F0 * (1 - metallic) + albedo * metallic;

    Vec3 emission = m_uniform->m_emission;
    if (m_uniform->m_emissionTex)
        emission = m_uniform->m_emissionTex->SampleTexture(in.texcoord);
    // result color
    Vec3 result(0.0f);

    for (size_t i = 0; i < m_uniform->m_lights->size(); ++i)
    {
        if ((*(m_uniform->m_lights))[i]->m_tag == "DirectionalLight")
            result += CalDirectionalLight(std::dynamic_pointer_cast<DirectionalLight>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, albedo, metallic, roughness, F0);
        else if ((*(m_uniform->m_lights))[i]->m_tag == "PointLight")
            result += CalPointLight(std::dynamic_pointer_cast<PointLight>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, in.worldPos, albedo, metallic, roughness, F0);
        else if ((*(m_uniform->m_lights))[i]->m_tag == "SpotLight")
            result += CalSpotLight(std::dynamic_pointer_cast<SpotLight>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, in.worldPos, albedo, metallic, roughness, F0);
    }

    Vec3 ambient = Vec3(0.03f) * albedo * ao;
    Vec3 color = ambient + result + emission;
    // color = color / (color + Vec3(1.0f));
    // color = Pow(color, Vec3(1.0f / 2.2f));
    for (size_t i = 0; i < 3; ++i)
    {
        color[i] = ACES_TONEMapping(color[i]);
        color[i] = std::pow(color[i], 1.0 / 2.2);
    }

    return color;
}

Vec3 PBRShader::CalDirectionalLight(const std::shared_ptr<DirectionalLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec3 &albedo,
                                    const float metallic, const float roughness, const Vec3 &F0)
{
    // prepare: light property
    Vec3 worldLightDir = Normalize(-light->m_direction);
    Vec3 halfwayDir = Normalize(worldViewDir + worldLightDir);
    Vec3 radiance = light->m_color;

    // Cook-Torrance BRDF
    float NDF = D_GGX_TR(worldNormal, halfwayDir, roughness);
    float G = GeometrySmith(worldNormal, worldViewDir, worldLightDir, roughness);
    Vec3 F = fresnelSchlick(Clamp(halfwayDir.GetDotProduct(worldViewDir), 0.0f, 1.0f), F0);

    Vec3 numerator = NDF * G * F;
    float denominator = 4.0 * std::max(worldNormal.GetDotProduct(worldViewDir), 0.0f) * std::max(worldNormal.GetDotProduct(worldLightDir), 0.0f) + 0.0001f;

    // specular
    Vec3 specular = numerator / denominator;
    Vec3 ks = F;
    Vec3 kd = Vec3(1.0f) - ks;
    kd *= (1.0f - metallic);
    // diffuse
    float NDotL = std::max(0.0f, worldNormal.GetDotProduct(worldLightDir));

    Vec3 result = (kd * albedo / M_PI + specular) * radiance * NDotL;
    return result;
}

Vec3 PBRShader::CalPointLight(const std::shared_ptr<PointLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir,
                              const Vec4 &worldPos, const Vec3 &albedo, const float metallic, const float roughness, const Vec3 &F0)
{
    // prepare: light property
    Vec3 worldLightDir = Normalize(light->m_position - worldPos);
    Vec3 halfwayDir = Normalize(worldViewDir + worldLightDir);
    float lightDistance = (light->m_position - worldPos).GetLength();
    float attenuation = 1.0 / (light->m_attenuation.x +
                               light->m_attenuation.y * lightDistance +
                               light->m_attenuation.z * (lightDistance * lightDistance));
    Vec3 radiance = light->m_color * attenuation;

    // Cook-Torrance BRDF
    float NDF = D_GGX_TR(worldNormal, halfwayDir, roughness);
    float G = GeometrySmith(worldNormal, worldViewDir, worldLightDir, roughness);
    Vec3 F = fresnelSchlick(Clamp(halfwayDir.GetDotProduct(worldViewDir), 0.0f, 1.0f), F0);

    Vec3 numerator = NDF * G * F;
    float denominator = 4.0 * std::max(worldNormal.GetDotProduct(worldViewDir), 0.0f) * std::max(worldNormal.GetDotProduct(worldLightDir), 0.0f) + 0.0001f;

    // specular
    Vec3 specular = numerator / denominator;
    Vec3 ks = F;
    Vec3 kd = Vec3(1.0f) - ks;
    kd *= (1.0f - metallic);
    // diffuse
    float NDotL = std::max(0.0f, worldNormal.GetDotProduct(worldLightDir));

    Vec3 result = (kd * albedo / M_PI + specular) * radiance * NDotL;
    return result;
}

Vec3 PBRShader::CalSpotLight(const std::shared_ptr<SpotLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo,
                             const float metallic, const float roughness, const Vec3 &F0)
{
    Vec3 worldLightDir = Normalize(light->m_position - worldPos);
    Vec3 halfwayDir = Normalize(worldViewDir + worldLightDir);
    float lightDistance = (light->m_position - worldPos).GetLength();
    float attenuation = 1.0 / (light->m_attenuation.x +
                               light->m_attenuation.y * lightDistance +
                               light->m_attenuation.z * (lightDistance * lightDistance));

    Vec3 spotLightDir = Normalize(light->m_direction);
    float theta = worldLightDir.GetDotProduct(-spotLightDir);

    float epsilon = light->m_cutoff - light->m_outcutoff;
    float intensity = Clamp((theta - light->m_outcutoff) / epsilon, 0.0f, 1.0f);
    Vec3 radiance = light->m_color * attenuation * intensity;

    // Cook-Torrance BRDF
    float NDF = D_GGX_TR(worldNormal, halfwayDir, roughness);
    float G = GeometrySmith(worldNormal, worldViewDir, worldLightDir, roughness);
    Vec3 F = fresnelSchlick(Clamp(halfwayDir.GetDotProduct(worldViewDir), 0.0f, 1.0f), F0);

    Vec3 numerator = NDF * G * F;
    float denominator = 4.0 * std::max(worldNormal.GetDotProduct(worldViewDir), 0.0f) * std::max(worldNormal.GetDotProduct(worldLightDir), 0.0f) + 0.0001f;

    // specular
    Vec3 specular = numerator / denominator;
    Vec3 ks = F;
    Vec3 kd = Vec3(1.0f) - ks;
    kd *= (1.0f - metallic);
    // diffuse
    float NDotL = std::max(0.0f, worldNormal.GetDotProduct(worldLightDir));

    Vec3 result = (kd * albedo / M_PI + specular) * radiance * NDotL;
    return result;
}