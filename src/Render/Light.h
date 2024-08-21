#ifndef LIGHT_H
#define LIGHT_H
#include "Math/Vec3.h"
#include <string>
class Material;
class Light
{
public:
    std::string m_tag;
    std::string m_name;
    Light() = default;
    virtual ~Light() = default;
    virtual void lighting(const Material &material,
                          const Vec3 &position, const Vec3 &normal,
                          const Vec3 &eyeDir, Vec3 &ambient, Vec3 &diffuse, Vec3 &specular) const = 0;
};

class DirectionalLight : public Light
{
public:
    Vec3 m_ambient;
    Vec3 m_diffuse;
    Vec3 m_specular;
    Vec3 m_direction;
    virtual ~DirectionalLight() = default;

    virtual void lighting(const Material &material,
                          const Vec3 &position, const Vec3 &normal,
                          const Vec3 &eyeDir, Vec3 &ambient, Vec3 &diffuse, Vec3 &specular) const;
    void SetDirectionalLight(Vec3 amb, Vec3 diff, Vec3 spec, Vec3 dir)
    {
        m_ambient = amb;
        m_diffuse = diff;
        m_specular = spec;
        m_direction = dir;
        m_direction.Normalize();
        m_tag = "Directional Light";
        m_name = "Default Directional Light";
    }
};

class PointLight : public Light
{
public:
    Vec3 m_ambient;
    Vec3 m_diffuse;
    Vec3 m_specular;
    Vec3 m_position;
    Vec3 m_attenuation;
    virtual ~PointLight() = default;
    virtual void lighting(const Material &material,
                          const Vec3 &position, const Vec3 &normal,
                          const Vec3 &eyeDir, Vec3 &ambient, Vec3 &diffuse, Vec3 &specular) const;

    void SetPointLight(Vec3 amb, Vec3 diff, Vec3 spec, Vec3 pos, Vec3 atte)
    {
        m_ambient = amb;
        m_diffuse = diff;
        m_specular = spec;
        m_position = pos;
        m_attenuation = atte;
        m_tag = "Point Light";
        m_name = "Default Point Light";
    }
};

class SpotLight : public Light
{
public:
    double m_cutoff, m_outcutoff;

    Vec3 m_ambient;
    Vec3 m_diffuse;
    Vec3 m_specular;
    Vec3 m_position;
    Vec3 m_direction;
    Vec3 m_attenuation;
    virtual ~SpotLight() = default;
    virtual void lighting(const Material &material,
                          const Vec3 &position, const Vec3 &normal,
                          const Vec3 &eyeDir, Vec3 &ambient, Vec3 &diffuse, Vec3 &specular) const;

    void SetSpotLight(Vec3 amb, Vec3 diff, Vec3 spec, Vec3 pos, Vec3 dir, Vec3 atte,
                      double cut)
    {
        m_cutoff = cos(cut * M_PI / 180.0);
        m_outcutoff = cos((cut + 10.0) * M_PI / 180.0);
        m_ambient = amb;
        m_diffuse = diff;
        m_specular = spec;
        m_position = pos;
        m_direction = dir;
        m_direction.Normalize();
        m_attenuation = atte;
        m_tag = "Spot Light";
        m_name = "Default Spot Light";
    }
};

#endif // LIGHT_H