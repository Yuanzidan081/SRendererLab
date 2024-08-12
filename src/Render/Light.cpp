#include "Light.h"
#include "Material.h"
void DirectionalLight::lighting(const Material &material,
                                const Vec3 &position, const Vec3 &normal,
                                const Vec3 &eyeDir, Vec3 &ambient, Vec3 &diffuse, Vec3 &specular) const
{

    // ambient
    ambient = m_ambient;

    float diff = max(normal.GetDotProduct(-this->m_direction), 0.0f);
    diffuse = m_diffuse * diff;

    // specular
    Vec3 halfwayDir = eyeDir - this->m_direction;
    halfwayDir.Normalize();
    float spec = pow(max(halfwayDir.GetDotProduct(eyeDir), 0.0f), material.m_gloss);
    specular = m_specular * spec;
}

void PointLight::lighting(const Material &material,
                          const Vec3 &position, const Vec3 &normal,
                          const Vec3 &eyeDir, Vec3 &ambient, Vec3 &diffuse, Vec3 &specular) const
{

    // ambient
    ambient = m_ambient;

    // diffuse
    Vec3 lightDir = m_position - position;
    float lightDistance = lightDir.GetLength();
    lightDir.Normalize();
    float diff = max(normal.GetDotProduct(lightDir), 0.0f);
    diffuse = m_diffuse * diff;

    // specular
    Vec3 halfwayDir = eyeDir + lightDir;
    halfwayDir.Normalize();
    float spec = pow(max(halfwayDir.GetDotProduct(normal), 0.0f), material.m_gloss);
    specular = m_specular * spec;

    // attenuation
    float attenuation = 1.0 / (m_attenuation.x +
                               m_attenuation.y * lightDistance +
                               m_attenuation.z * (lightDistance * lightDistance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
}

void SpotLight::lighting(const Material &material,
                         const Vec3 &position, const Vec3 &normal,
                         const Vec3 &eyeDir, Vec3 &ambient, Vec3 &diffuse, Vec3 &specular) const
{
    // ambient
    ambient = m_ambient;

    // diffuse
    Vec3 lightDir = m_position - position;
    float lightDistance = lightDir.GetLength();
    lightDir.Normalize();
    float diff = max(normal.GetDotProduct(lightDir), 0.0f);
    diffuse = m_diffuse * diff;

    // specular
    Vec3 halfwayDir = eyeDir + lightDir;
    halfwayDir.Normalize();
    float spec = pow(max(halfwayDir.GetDotProduct(eyeDir), 0.0f), material.m_gloss);
    specular = m_specular * spec;

    // spotLight
    float theta = lightDir.GetDotProduct(-m_direction);
    float epsilon = (m_cutoff - m_outcutoff);
    float intensity = (theta - this->m_outcutoff) / epsilon;
    if (intensity < 0.0f)
        intensity = 0.0f;
    if (intensity > 1.0f)
        intensity = 1.0f;
    diffuse *= intensity;
    specular *= intensity;

    // attenuation
    float attenuation = 1.0 / (m_attenuation.x +
                               m_attenuation.y * lightDistance +
                               m_attenuation.z * (lightDistance * lightDistance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
}
