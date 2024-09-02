#include "GouraudShader.h"
#include "Render/Light.h"
#include "Render/Material.h"
GouraudShader *GouraudShader::s_shader = nullptr;

GouraudShader *GouraudShader::GetInstance()
{
    if (s_shader == nullptr)
        s_shader = new GouraudShader();
    return s_shader;
}

void GouraudShader::Destroy()
{
    m_uniform = nullptr;

    if (s_shader)
        delete s_shader;
    s_shader = nullptr;
}

VertexOut GouraudShader::VertexShader(const Vertex &in)
{
    VertexOut result;
    result.worldPos = m_uniform->m_modelMatrix * in.position;
    result.clipPos = m_uniform->m_projectMatrix * m_uniform->m_viewMatrix * result.worldPos;
    result.texcoord = in.texcoord;
    result.normal = m_uniform->m_normalMatrix * in.normal;

    Vec3 worldNormal = Normalize(result.normal);
    Vec4 albedo = in.color;
    if (m_uniform->m_mainTex)
        albedo = m_uniform->m_mainTex->SampleTexture(in.texcoord);
    Vec3 resultColor = m_uniform->m_ambient * albedo;
    Vec3 worldViewDir = Normalize(Vec3(m_uniform->m_eyePos - result.worldPos));
    for (size_t i = 0; i < m_uniform->m_lights->size(); ++i)
    {
        if ((*(m_uniform->m_lights))[i]->m_tag == "DirectionalLight")
            resultColor += CalDirectionalLight(std::dynamic_pointer_cast<DirectionalLight>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, albedo);
        else if ((*(m_uniform->m_lights))[i]->m_tag == "PointLight")
            resultColor += CalPointLight(std::dynamic_pointer_cast<PointLight>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, result.worldPos, albedo);
        else if ((*(m_uniform->m_lights))[i]->m_tag == "SpotLight")
            resultColor += CalSpotLight(std::dynamic_pointer_cast<SpotLight>((*(m_uniform->m_lights))[i]), worldNormal, worldViewDir, result.worldPos, albedo);
    }
    result.color = Vec4(resultColor, 1.0f);
    return result;
}

Vec4 GouraudShader::FragmentShader(const VertexOut &in)
{
    Vec4 litColor = in.color;
    return litColor;
}

Vec3 GouraudShader::CalDirectionalLight(const std::shared_ptr<DirectionalLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec3 &albedo)
{
    Vec3 worldLightDir = Normalize(-light->m_direction);

    // ambient

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

Vec3 GouraudShader::CalPointLight(const std::shared_ptr<PointLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo)
{
    Vec3 worldLightDir = Normalize(light->m_position - worldPos);

    // ambient
    Vec4 ambient = m_uniform->m_ambient;

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

Vec3 GouraudShader::CalSpotLight(const std::shared_ptr<SpotLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo)
{
    Vec3 worldLightDir = Normalize(light->m_position - worldPos);

    // ambient
    Vec4 ambient = m_uniform->m_ambient;

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