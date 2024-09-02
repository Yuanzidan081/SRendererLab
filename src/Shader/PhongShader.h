#ifndef PHONGSHADER_H
#define PHONGSHADER_H
#include "Shader.h"
class DirectionalLight;
class PointLight;
class SpotLight;
class PhongShader : public Shader
{
private:
    PhongShader() = default;
    PhongShader(const PhongShader &s) = delete;
    static PhongShader *s_shader;

public:
    static PhongShader *GetInstance();
    virtual void Destroy();
    ~PhongShader() = default;
    virtual VertexOut VertexShader(const Vertex &in);
    virtual Vec4 FragmentShader(const VertexOut &in);

    Vec3 CalDirectionalLight(const std::shared_ptr<DirectionalLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec3 &albedo);

    Vec3 CalPointLight(const std::shared_ptr<PointLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo);

    Vec3 CalSpotLight(const std::shared_ptr<SpotLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDirs, const Vec4 &worldPos, const Vec3 &albedo);
};

#endif // PHONGSHADER_H