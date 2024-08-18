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
    m_uniform = nullptr;

    if (s_shader)
        delete s_shader;
    s_shader = nullptr;
}

VertexOut SkyBoxShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    Mat4x4 rotView = m_uniform->m_viewMatrix.GetNoTranslate();

    result.posWorld = in.position;
    Vec4 clipPos = m_uniform->m_projectMatrix * rotView * in.position;
    result.posProj = Vec4(clipPos.x, clipPos.y, clipPos.w, clipPos.w);
    return result;
}

Vec4 SkyBoxShader::fragmentShader(const VertexOut &in)
{

    // Vec3 uv = in.posWorld.GetNormalize3D();
    Vec4 litColor = in.color;
    if (m_uniform->m_cubeMap)
        litColor = m_uniform->m_cubeMap->SampleCubeMap(in.posWorld);
    return litColor;
}