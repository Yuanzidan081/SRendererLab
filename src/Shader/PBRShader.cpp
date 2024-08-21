#include "PBRShader.h"

PBRShader *PBRShader::s_shader = nullptr;

float PBRShader::D_GGX_TR(Vec3 &nDir, Vec3 &hDir, float roughness)
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

float PBRShader::GeometrySmith(Vec3 &nDir, Vec3 &vDir, Vec3 &lDir, float k)
{

    float NdotV = std::max(nDir.GetDotProduct(vDir), 0.0f);
    float NdotL = std::max(nDir.GetDotProduct(lDir), 0.0f);
    float ggx1 = GeometrySchlickGGX(NdotV, k);
    float ggx2 = GeometrySchlickGGX(NdotL, k);

    return ggx1 * ggx2;
}

Vec3 PBRShader::fresnelSchlick(float cosTheta, Vec3 &F0)
{
    return F0 + (-F0 + 1.0f) * pow(1.0f - cosTheta, 5.0f);
}

// https://zhuanlan.zhihu.com/p/261667233
// https://www.zhihu.com/question/263829818/answer/2798853006
// https://zhuanlan.zhihu.com/p/139593847

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

VertexOut PBRShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_uniform->m_modelMatrix * in.position;
    result.posProj = m_uniform->m_projectMatrix * m_uniform->m_viewMatrix * result.posWorld;
    result.color = in.color;
    result.texcoord = in.texcoord;
    result.normal = m_uniform->m_normalMatrix * Vec4(in.normal);
    return VertexOut();
}

Vec4 PBRShader::fragmentShader(const VertexOut &in)
{
    return Vec4();
}
