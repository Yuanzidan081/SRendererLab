#include "SimpleShader.h"

SimpleShader *SimpleShader::s_shader = nullptr;

SimpleShader *SimpleShader::GetInstance()
{
    if (s_shader == nullptr)
        s_shader = new SimpleShader();
    return s_shader;
}

void SimpleShader::Destroy()
{
    m_uniform = nullptr;

    if (s_shader)
    {
        delete s_shader;
    }
    s_shader = nullptr;
}

VertexOut SimpleShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_uniform->m_modelMatrix * in.position;
    result.posProj = m_uniform->m_projectMatrix * m_uniform->m_viewMatrix * result.posWorld;
    result.color = in.color;
    result.normal = in.normal;
    result.texcoord = in.texcoord;

    return result;
}

Vec4 SimpleShader::fragmentShader(const VertexOut &in)
{
    Vec4 litColor = in.color;
    if (m_uniform->m_mainTex)
    {
        litColor = m_uniform->m_mainTex->SampleTexture(in.texcoord);
    }
    return litColor;
}
