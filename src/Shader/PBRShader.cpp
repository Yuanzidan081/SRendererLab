#include "PBRShader.h"

PBRShader *PBRShader::s_shader = nullptr;

float PBRShader::D_GGX_TR(const Vec3 &nDir, const Vec3 &hDir, float roughness)
{

    float roughness2 = roughness * roughness;
    float NdotH = std::max(nDir.GetDotProduct(hDir), 0.0f);
    float NdotH2 = NdotH * NdotH;

    float nom = roughness2;
    float denom = (NdotH2 * (roughness2 - 1.0f) + 1.0f);
    denom = M_PI * denom * denom;

    return nom / denom;
}

float PBRShader::GeometrySchlickGGX(float NdotV, float k)
{

    float nom = NdotV;
    float denom = NdotV * (1.0f - k) + k;
    return nom / denom;
}
// dirction k = (roughness + 1)^2/8 IBL: (roughness)^2/2
float PBRShader::GeometrySmith(const Vec3 &nDir, const Vec3 &vDir, const Vec3 &lDir, float k)
{

    float NdotV = std::max(nDir.GetDotProduct(vDir), 0.0f);
    float NdotL = std::max(nDir.GetDotProduct(lDir), 0.0f);
    float ggx1 = GeometrySchlickGGX(NdotV, k);
    float ggx2 = GeometrySchlickGGX(NdotL, k);

    return ggx1 * ggx2;
}

Vec3 PBRShader::fresnelSchlick(float cosTheta, Vec3 &F0)
{
    return F0 + (-F0 + 1.0f) * pow(Clamp(1.0f - cosTheta, 0.0f, 1.0f), 5.0f);
}

PBRShader *PBRShader::GetInstance()
{
    if (s_shader == nullptr)
        s_shader = new PBRShader();
    return s_shader;
}

void PBRShader::Destroy()
{
    m_uniform = nullptr;

    if (s_shader)
        delete s_shader;
    s_shader = nullptr;
}

VertexOut PBRShader::VertexShader(const Vertex &in)
{
    VertexOut result;
    result.worldPos = m_uniform->m_modelMatrix * in.position;
    result.clipPos = m_uniform->m_projectMatrix * m_uniform->m_viewMatrix * result.worldPos;
    result.color = in.color;
    result.texcoord = in.texcoord;
    result.normal = m_uniform->m_normalMatrix * Vec4(in.normal);
    return VertexOut();
}

Vec4 PBRShader::FragmentShader(const VertexOut &in)
{
    return Vec4();
}
