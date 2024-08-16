#include "SkyBoxShader.h"

SkyBoxShader *SkyBoxShader::s_shader = nullptr;

SkyBoxShader *SkyBoxShader::GetInstance()
{
    if (s_shader == nullptr)
        s_shader = new SkyBoxShader();
    return s_shader;
}

void SkyBoxShader::Destroy()
{
    //m_uniform = nullptr;

    if (s_shader)
        delete s_shader;
    s_shader = nullptr;
}

VertexOut SkyBoxShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_uniform.m_modelMatrix * in.position;
    result.posProj = m_uniform.m_projectMatrix * m_uniform.m_viewMatrix * result.posWorld;

    result.color = in.color;
    result.normal = m_uniform.m_normalMatrix * Vec4(in.normal);
    result.texcoord = in.texcoord;

    return result;
}

Vec4 SkyBoxShader::fragmentShader(const VertexOut &in)
{
    Vec4 litColor = in.color;

    return litColor;
}