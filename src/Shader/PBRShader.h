#ifndef PBRSHADER_H
#define PBRSHADER_H
#include "Shader.h"

class PBRShader : public Shader
{
private:
    PBRShader() = default;
    PBRShader(const PBRShader &s) = delete;
    static PBRShader *s_shader;

    float D_GGX_TR(const Vec3 &nDir, const Vec3 &hDir, float roughness);
    float GeometrySchlickGGX(float NdotV, float k);

    float GeometrySmith(const Vec3 &N, const Vec3 &V, const Vec3 &L, float k);
    Vec3 fresnelSchlick(float cosTheta, Vec3 &F0);

public:
    static PBRShader *GetInstance();
    virtual void Destroy();
    ~PBRShader() = default;
    virtual VertexOut VertexShader(const Vertex &in);
    virtual Vec4 FragmentShader(const VertexOut &in);
};
#endif // PBRSHADER_H