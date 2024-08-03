#include "SimpleShader.h"

SimpleShader::SimpleShader()
{
    m_tex = nullptr;
}

Vec3f SimpleShader::VertexShader(int faceInd, int VertInd)
{
    return Vec3f();
}

bool SimpleShader::FragmentShader(v2f *v2fData, Vec4f &color)
{
    return false;
}

VertexOut SimpleShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_modelMatrix * in.position;
    result.posProj = m_projectMatrix * m_viewMatrix * result.posWorld;
    result.color = in.color;
    result.normal = in.normal;
    result.texcoord = in.texcoord;

    // oneDivzZ to correct lerp
    result.oneDivZ = 1.0f / result.posProj.w;
    result.posWorld *= result.oneDivZ;
    result.texcoord *= result.oneDivZ;
    result.color *= result.oneDivZ;
    return result;
}

Vec4f SimpleShader::fragmentShader(const VertexOut &in)
{
    Vec4f litColor = in.color;
    if (m_tex)
    {
        litColor = m_tex->SampleTexture(in.texcoord);
    }
    return litColor;
}
