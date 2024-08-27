#ifndef PBRSHADER_H
#define PBRSHADER_H
#include "Shader.h"
class DirectionalLight;
class PointLight;
class SpotLight;
class PBRShader : public Shader
{
private:
    PBRShader() = default;
    PBRShader(const PBRShader &s) = delete;
    static PBRShader *s_shader;

    float D_GGX_TR(const Vec3 &nDir, const Vec3 &hDir, float roughness);
    float GeometrySchlickGGX(float NdotV, float roughness);

    float GeometrySmith(const Vec3 &N, const Vec3 &V, const Vec3 &L, float k);
    Vec3 fresnelSchlick(float cosTheta, const Vec3 &F0);

public:
    static PBRShader *GetInstance();
    virtual void Destroy();
    ~PBRShader() = default;
    virtual VertexOut VertexShader(const Vertex &in);
    virtual Vec4 FragmentShader(const VertexOut &in);
    Vec3 CalDirectionalLight(DirectionalLight *light, const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec3 &albedo, const float metallic, const Vec3 &F0);

    Vec3 CalPointLight(PointLight *light,  const Vec3 &worldNormal, const Vec3 &worldViewDir, const Vec4 &worldPos, const Vec3 &albedo, const float metallic, const Vec3 &F0);

    Vec3 CalSpotLight(SpotLight *light,  const Vec3 &worldNormal, const Vec3 &worldViewDirs, const Vec4 &worldPos, const Vec3 &albedo, const float metallic, const Vec3 &F0);
};
#endif // PBRSHADER_H