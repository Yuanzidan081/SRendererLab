#include "SkyBoxShader.h"
#include "Algorithm/ColorAlgorithm.h"
SkyBoxShader *SkyBoxShader::s_shader = nullptr;

SkyBoxShader::SkyBoxShader()
{
    m_name = "SkyBoxShader";
}

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

VertexOut SkyBoxShader::VertexShader(const Vertex &in)
{
    VertexOut result;
    Mat4x4 rotView = static_cast<Mat4x4>(m_uniform->m_viewMatrix.GetMat3x3());

    result.worldPos = in.position;
    Vec4 clipPos = m_uniform->m_projectMatrix * rotView * in.position;
    result.clipPos = Vec4(clipPos.x, clipPos.y, clipPos.w, clipPos.w);
    return result;
}

Vec4 SkyBoxShader::FragmentShader(const VertexOut &in)
{
    Vec4 litColor;
    // Vec3 uv = in.worldPos.GetNormalize3D();
    if (m_uniform->m_shadingMode == ForwardMode)
    {
        litColor = in.color;
        if (m_uniform->m_cubeMap)
            litColor = m_uniform->m_cubeMap->SampleCubeMap(in.worldPos);
        // litColor = GammaCorrection(litColor);
    }
    else
    {
        litColor = in.color;
    }

    return litColor;
}