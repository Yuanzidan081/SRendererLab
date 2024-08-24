#ifndef LIGHT_H
#define LIGHT_H
#include "Math/Vec3.h"
#include "Math/Vec4.h"
#include <string>
#include <vector>
class Material;
class Light
{
public:
    std::string m_tag;
    std::string m_name;
    Vec4 m_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    Light() = default;
    virtual ~Light() = default;
};

class DirectionalLight : public Light
{
public:
    Vec3 m_direction;

    virtual ~DirectionalLight() = default;

    void SetDirectionalLight(Vec3 dir, const Vec4 &color)
    {
        m_direction = dir;
        m_color = color;
        m_tag = "DirectionalLight";
        m_name = "Default Directional Light";
    }
};

class PointLight : public Light
{
public:
    Vec3 m_position;
    Vec3 m_attenuation;
    virtual ~PointLight() = default;

    void SetPointLight(Vec3 pos, Vec3 atte, const Vec4 &color)
    {
        m_position = pos;
        m_attenuation = atte;
        m_color = color;

        m_tag = "PointLight";
        m_name = "Default Point Light";
    }
};

class SpotLight : public Light
{
public:
    double m_cutoff, m_outcutoff;
    Vec3 m_position;
    Vec3 m_direction;
    Vec3 m_attenuation;
    virtual ~SpotLight() = default;

    void SetSpotLight(Vec3 pos, Vec3 dir, Vec3 atte,
                      double cut, const Vec4 &color)
    {
        m_cutoff = cos(cut * M_PI / 180.0);
        m_outcutoff = cos((cut + 10.0) * M_PI / 180.0);
        m_position = pos;
        m_direction = dir;
        m_attenuation = atte;
        m_color = color;
        m_tag = "SpotLight";
        m_name = "Default Spot Light";
    }
};

#endif // LIGHT_H