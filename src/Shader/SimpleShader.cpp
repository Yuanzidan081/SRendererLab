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

VertexOut SimpleShader::VertexShader(const Vertex &in)
{
    VertexOut result;
    result.worldPos = m_uniform->m_modelMatrix * in.position;
    result.clipPos = m_uniform->m_projectMatrix * m_uniform->m_viewMatrix * result.worldPos;
    result.color = in.color;
    result.normal = in.normal;
    result.texcoord = in.texcoord;

    return result;
}

Vec4 SimpleShader::FragmentShader(const VertexOut &in)
{
    Vec4 litColor = in.color;
    if (m_uniform->m_mainTex)
    {
        litColor = m_uniform->m_mainTex->SampleTexture(in.texcoord);
    }
    return litColor;
}
