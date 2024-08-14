#include "SimpleShader.h"

SimpleShader *SimpleShader::s_shader = nullptr;
SimpleShader::SimpleShader()
{
    m_tex = nullptr;
}

SimpleShader *SimpleShader::GetInstance()
{
    if (s_shader == nullptr)
        s_shader = new SimpleShader();
    return s_shader;
}

void SimpleShader::Destroy()
{
    if (s_shader)
    {
        delete s_shader;
        s_shader = nullptr;
    }
}

VertexOut SimpleShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_modelMatrix * in.position;
    result.posProj = m_projectMatrix * m_viewMatrix * result.posWorld;
    result.color = in.color;
    result.normal = in.normal;
    result.texcoord = in.texcoord;

    return result;
}

Vec4 SimpleShader::fragmentShader(const VertexOut &in)
{
    Vec4 litColor = in.color;
    if (m_tex)
    {
        litColor = m_tex->SampleTexture(in.texcoord);
        // std::cout << litColor << std::endl;
    }
    return litColor;
}
