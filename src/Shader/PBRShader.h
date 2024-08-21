#ifndef PBRSHADER_H
#define PBRSHADER_H
#include "Shader.h"

class PBRShader : public Shader
{
private:
    PBRShader() = default;
    PBRShader(const PBRShader &s) = delete;
    static PBRShader *s_shader;

    float D_GGX_TR(Vec3 &nDir, Vec3 &hDir, float roughness);
    float GeometrySchlickGGX(float NdotV, float k);

    float GeometrySmith(Vec3 &N, Vec3 &V, Vec3 &L, float k);
    Vec3 fresnelSchlick(float cosTheta, Vec3 &F0);

public:
    static PBRShader *GetInstance();
    virtual void Destroy();
    ~PBRShader() = default;
    virtual VertexOut vertexShader(const Vertex &in);
    virtual Vec4 fragmentShader(const VertexOut &in);
};
#endif // PBRSHADER_H