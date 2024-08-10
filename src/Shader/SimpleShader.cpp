#include "SimpleShader.h"

SimpleShader::SimpleShader()
{
    m_tex = nullptr;
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
    }
    return litColor;
}
