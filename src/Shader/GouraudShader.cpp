#include "GouraudShader.h"
#include "Render/Light.h"
#include "Render/Material.h"
GouraudShader *GouraudShader::s_shader = nullptr;

GouraudShader *GouraudShader::GetInstance()
{
    if (s_shader == nullptr)
        s_shader = new GouraudShader();
    return s_shader;
}

void GouraudShader::Destroy()
{
    // m_uniform = nullptr;

    if (s_shader)
        delete s_shader;
    s_shader = nullptr;
}

VertexOut GouraudShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_uniform.m_modelMatrix * in.position;
    result.posProj = m_uniform.m_projectMatrix * m_uniform.m_viewMatrix * result.posWorld;
    result.color = in.color;
    result.texcoord = in.texcoord;
    result.normal = m_uniform.m_normalMatrix * Vec4(in.normal);

    if (m_uniform.m_mainTex)
        result.color = m_uniform.m_mainTex->SampleTexture(result.texcoord);
    Vec3 amb, diff, spec;

    if (m_uniform.m_lights)
    {
        Vec3 eyeDir = m_uniform.m_eyePos - result.posWorld;
        eyeDir.Normalize();
        Vec3 ambTmp, diffTmp, specTmp;
        for (int i = 0; i < m_uniform.m_lights->size(); ++i)
        {
            (*m_uniform.m_lights)[i]->lighting(*m_uniform.m_material, result.posWorld, result.normal, eyeDir, ambTmp, diffTmp, specTmp);
            amb += ambTmp;
            diff += diffTmp;
            spec += specTmp;
        }

        result.color.x *= (amb.x + diff.x + spec.x);
        result.color.y *= (amb.y + diff.y + spec.y);
        result.color.z *= (amb.z + diff.z + spec.z);
        result.color.w = 1.0f;
    }
    return result;
}

Vec4 GouraudShader::fragmentShader(const VertexOut &in)
{
    Vec4 litColor = in.color;
    return litColor;
}
