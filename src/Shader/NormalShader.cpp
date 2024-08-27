#include "NormalShader.h"
#include "Render/Light.h"
#include "Render/Material.h"
NormalShader *NormalShader::s_shader = nullptr;

NormalShader *NormalShader::GetInstance()
{
    if (s_shader == nullptr)
        s_shader = new NormalShader();
    return s_shader;
}

void NormalShader::Destroy()
{
    m_uniform = nullptr;

    if (s_shader)
        delete s_shader;
    s_shader = nullptr;
}

VertexOut NormalShader::VertexShader(const Vertex &in)
{
    VertexOut result;
    result.worldPos = m_uniform->m_modelMatrix * in.position;
    result.clipPos = m_uniform->m_projectMatrix * m_uniform->m_viewMatrix * result.worldPos;
    result.texcoord = in.texcoord;
    result.normal = Normalize(m_uniform->m_normalMatrix * in.normal);
    Vec3 tangent = Normalize(m_uniform->m_modelMatrix.GetMat3x3() * in.tangent);
    Vec3 binormal = Normalize(result.normal.GetCrossProduct(tangent));
    result.TBN = Mat3x3(tangent, binormal, result.normal);
    return result;
}

Vec4 NormalShader::FragmentShader(const VertexOut &in)
{
    Vec3 worldViewDir = Normalize(m_uniform->m_eyePos - in.worldPos);
    Vec3 worldNormal = in.normal;
    if (m_uniform->m_normalTex)
    {
        Vec3 sampledNormal = m_uniform->m_normalTex->SampleTexture(in.texcoord);
        Vec3 worldNormal = (sampledNormal * 2.0f - 1.0f);
        // float scale = 0.1f;
        // worldNormal.x *= scale;
        // worldNormal.y *= scale;
        // worldNormal.z = sqrtf(1.0f - (worldNormal.x * worldNormal.x + worldNormal.y * worldNormal.y));
        worldNormal = Normalize(in.TBN * worldNormal);
    }
    Vec4 albedo = in.color;
    if (m_uniform->m_mainTex)
        albedo = m_uniform->m_mainTex->SampleTexture(in.texcoord);
    Vec3 result = albedo;
    for (size_t i = 0; i < m_uniform->m_lights->size(); ++i)
    {
        if ((*(m_uniform->m_lights))[i]->m_tag == "DirectionalLight")
            result += CalDirectionalLight(static_cast<DirectionalLight *>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, albedo);
        else if ((*(m_uniform->m_lights))[i]->m_tag == "PointLight")
            result += CalPointLight(static_cast<PointLight *>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, in.worldPos, albedo);
        else if ((*(m_uniform->m_lights))[i]->m_tag == "SpotLight")
            result += CalSpotLight(static_cast<SpotLight *>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, in.worldPos, albedo);
    }
    return Vec4(result, 1.0f);
}

Vec3 NormalShader::CalDirectionalLight(DirectionalLight *light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec3 &albedo)
{
    Vec3 worldLightDir = Normalize(-light->m_direction);

    // diffuse
    float diff = std::max(0.0f, worldNormal.GetDotProduct(worldLightDir));
    Vec3 diffuse = diff * (m_uniform->m_diffuse * albedo) * (light->m_color);

    // specular
    Vec3 halfwayDir = Normalize(worldViewDir + worldLightDir);
    float spec = std::pow(std::max(0.0f, halfwayDir.GetDotProduct(worldNormal)), m_uniform->m_shiness);
    Vec3 specular = spec * (m_uniform->m_specular) * (light->m_color);
    Vec3 result = diffuse + specular;
    return result;
}

Vec3 NormalShader::CalPointLight(PointLight *light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo)
{
    Vec3 worldLightDir = Normalize(light->m_position - worldPos);

    // diffuse
    float diff = std::max(0.0f, worldNormal.GetDotProduct(worldLightDir));
    Vec3 diffuse = diff * (m_uniform->m_diffuse * albedo) * (light->m_color);

    // specular
    Vec3 halfwayDir = Normalize(worldViewDir + worldLightDir);
    float spec = std::pow(std::max(0.0f, halfwayDir.GetDotProduct(worldNormal)), m_uniform->m_shiness);
    Vec3 specular = spec * (m_uniform->m_specular) * (light->m_color);
    // attenuation
    float lightDistance = (light->m_position - worldPos).GetLength();
    float attenuation = 1.0 / (light->m_attenuation.x +
                               light->m_attenuation.y * lightDistance +
                               light->m_attenuation.z * (lightDistance * lightDistance));
    Vec3 result = (diffuse + specular) * attenuation;
    return result;
}

Vec3 NormalShader::CalSpotLight(SpotLight *light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo)
{
    Vec3 worldLightDir = Normalize(light->m_position - worldPos);

    // diffuse
    float diff = std::max(0.0f, worldNormal.GetDotProduct(worldLightDir));
    Vec3 diffuse = diff * (m_uniform->m_diffuse * albedo) * (light->m_color);

    // specular
    Vec3 halfwayDir = Normalize(worldViewDir + worldLightDir);
    float spec = std::pow(std::max(0.0f, halfwayDir.GetDotProduct(worldNormal)), m_uniform->m_shiness);
    Vec3 specular = spec * (m_uniform->m_specular) * (light->m_color);

    // spotLight
    float theta = worldLightDir.GetDotProduct(-light->m_direction);
    float epsilon = light->m_cutoff - light->m_outcutoff;
    float intensity = Clamp((theta - light->m_outcutoff), 0.0f, 1.0f);
    diffuse *= intensity;
    specular *= intensity;

    // attenuation
    float lightDistance = (light->m_position - worldPos).GetLength();
    float attenuation = 1.0 / (light->m_attenuation.x +
                               light->m_attenuation.y * lightDistance +
                               light->m_attenuation.z * (lightDistance * lightDistance));
    Vec3 result = (diffuse + specular) * attenuation;
    return result;
}