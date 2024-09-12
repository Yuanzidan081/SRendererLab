#ifndef GOURAUDSHADER_H
#define GOURAUDSHADER_H
#include "Shader.h"
class DirectionalLight;
class PointLight;
class SpotLight;
class GouraudShader : public Shader
{
private:
    GouraudShader();
    GouraudShader(const GouraudShader &s) = delete;
    static GouraudShader *s_shader;

public:
    static GouraudShader *GetInstance();
    virtual void Destroy();
    ~GouraudShader() = default;
    virtual VertexOut VertexShader(const Vertex &in);
    virtual Vec4 FragmentShader(const VertexOut &in);

    Vec3 CalDirectionalLight(const std::shared_ptr<DirectionalLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec3 &albedo);

    Vec3 CalPointLight(const std::shared_ptr<PointLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo);

    Vec3 CalSpotLight(const std::shared_ptr<SpotLight> &light, const Vec3 &worldNormal, const Vec3 &worldViewDirs, const Vec4 &worldPos, const Vec3 &albedo);
};

#endif // GOURAUDSHADER_H