#ifndef NORMALSHADER_H
#define NORMALSHADER_H
#include "Shader.h"
class DirectionalLight;
class PointLight;
class SpotLight;
class NormalShader : public Shader
{
private:
    NormalShader() = default;
    NormalShader(const NormalShader &s) = delete;
    static NormalShader *s_shader;

public:
    static NormalShader *GetInstance();
    virtual void Destroy();
    ~NormalShader() = default;
    virtual VertexOut VertexShader(const Vertex &in);
    virtual Vec4 FragmentShader(const VertexOut &in);

    Vec3 CalDirectionalLight(DirectionalLight *light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec3 &albedo);

    Vec3 CalPointLight(PointLight *light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo);

    Vec3 CalSpotLight(SpotLight *light, const Vec3 &worldNormal, const Vec3 &worldViewDirs, const Vec4 &worldPos, const Vec3 &albedo);
};

#endif // GOURAUDSHADER_H