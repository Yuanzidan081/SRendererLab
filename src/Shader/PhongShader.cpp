#include "PhongShader.h"
#include "Render/Material.h"
#include "Render/Light.h"
#include <iostream>
#include "Algorithm/ToneMapping.h"
PhongShader *PhongShader::s_shader = nullptr;
PhongShader *PhongShader::GetInstance()
{

    if (s_shader == nullptr)
        s_shader = new PhongShader();
    return s_shader;
}

void PhongShader::Destroy()
{
    m_uniform = nullptr;
    if (s_shader)
        delete s_shader;
    s_shader = nullptr;
}

VertexOut PhongShader::VertexShader(const Vertex &in)
{
    VertexOut result;
    result.worldPos = m_uniform->m_modelMatrix * in.position;
    result.clipPos = m_uniform->m_projectMatrix * m_uniform->m_viewMatrix * result.worldPos;

    result.color = in.color;
    result.normal = m_uniform->m_normalMatrix * in.normal;
    Vec3 tangent = Normalize(m_uniform->m_modelMatrix.GetMat3x3() * in.tangent);
    Vec3 binormal = Normalize(result.normal.GetCrossProduct(tangent));
    result.TBN = Mat3x3(tangent, binormal, result.normal);

    result.texcoord = in.texcoord;

    return result;
}

Vec4 PhongShader::FragmentShader(const VertexOut &in)
{
    Vec3 worldNormal;
    Vec3 albedo;
    if (m_uniform->m_shadingMode == ForwardMode)
    {
        worldNormal = Normalize(in.normal);
        if (m_uniform->m_normalTex)
        {
            worldNormal = Normalize(in.TBN * (m_uniform->m_normalTex->SampleTexture(in.texcoord) * 2.0f - 1.0f));
        }

        // Vec4 albedo = in.color;
        albedo = m_uniform->m_diffuse;

        if (m_uniform->m_mainTex)
            albedo = m_uniform->m_mainTex->SampleTexture(in.texcoord);
    }
    else
    {
        worldNormal = in.normal;

        // worldViewDir
        albedo = in.color;
    }
    // Deferred Mode
    // worldNormal

    Vec3 result = m_uniform->m_ambient * albedo;
    Vec3 worldViewDir = Normalize(Vec3(m_uniform->m_eyePos - in.worldPos));
    for (size_t i = 0; i < m_uniform->m_lights->size(); ++i)
    {
        if ((*(m_uniform->m_lights))[i]->m_tag == "DirectionalLight")
            result += CalDirectionalLight(std::dynamic_pointer_cast<DirectionalLight>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, albedo);
        else if ((*(m_uniform->m_lights))[i]->m_tag == "PointLight")
            result += CalPointLight(std::dynamic_pointer_cast<PointLight>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, in.worldPos, albedo);
        else if ((*(m_uniform->m_lights))[i]->m_tag == "SpotLight")
            result += CalSpotLight(std::dynamic_pointer_cast<SpotLight>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, in.worldPos, albedo);
    }
    // tone mapping
    // result /= (result + Vec3(0.5f, 0.5f, 0.5f));
    // result = Vec3(1.0f) - Vec3(std::exp(-result.x * 1.0f), std::exp(-result.y * 1.0f), std::exp(-result.z * 1.0f));
    // result = result / (result + Vec3(1.0f));
    // result = Pow(result, Vec3(1.0f / 2.2f));
    for (size_t i = 0; i < 3; ++i)
    {
        result[i] = ACES_TONEMapping(result[i]);
        result[i] = std::pow(result[i], 1.0 / 2.2);
    }
    return Vec4(result, 1.0f);
}

Vec3 PhongShader::CalDirectionalLight(const std::shared_ptr<DirectionalLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec3 &albedo)
{
    Vec3 worldLightDir = Normalize(-light->m_direction);

    // ambient

    // diffuse
    float diff = std::max(0.0f, worldNormal.GetDotProduct(worldLightDir));
    Vec3 diffuse = diff * (albedo) * (light->m_color);

    // specular
    Vec3 halfwayDir = Normalize(worldViewDir + worldLightDir);
    float spec = std::pow(std::max(0.0f, halfwayDir.GetDotProduct(worldNormal)), m_uniform->m_shiness);
    Vec3 specular = spec * (m_uniform->m_specular) * (light->m_color);
    Vec3 result = diffuse + specular;
    return result;
}

Vec3 PhongShader::CalPointLight(const std::shared_ptr<PointLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo)
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

Vec3 PhongShader::CalSpotLight(const std::shared_ptr<SpotLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo)
{
    Vec3 worldLightDir = Normalize(light->m_position - worldPos);
    Vec3 spotLightDir = Normalize(light->m_direction);

    // diffuse
    float diff = std::max(0.0f, worldNormal.GetDotProduct(worldLightDir));
    Vec3 diffuse = diff * (m_uniform->m_diffuse * albedo) * (light->m_color);

    // specular
    Vec3 halfwayDir = Normalize(worldViewDir + worldLightDir);
    float spec = std::pow(std::max(0.0f, halfwayDir.GetDotProduct(worldNormal)), m_uniform->m_shiness);
    Vec3 specular = spec * (m_uniform->m_specular) * (light->m_color);

    // spotLight
    float theta = worldLightDir.GetDotProduct(-spotLightDir);

    float epsilon = light->m_cutoff - light->m_outcutoff;
    float intensity = Clamp((theta - light->m_outcutoff) / epsilon, 0.0f, 1.0f);

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
