#include "PhongShader.h"
#include "Render/Material.h"
#include "Render/Light.h"
#include <iostream>
PhongShader *PhongShader::s_shader = nullptr;
PhongShader *PhongShader::GetInstance()
{

    if (s_shader == nullptr)
        s_shader = new PhongShader();
    return s_shader;
}

void PhongShader::Destroy()
{
    m_uniform = nullptr;
    // std::cout << "delete PhongShader" << std::endl;
    if (s_shader)
        delete s_shader;
    s_shader = nullptr;
}

VertexOut PhongShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_uniform->m_modelMatrix * in.position;
    result.posProj = m_uniform->m_projectMatrix * m_uniform->m_viewMatrix * result.posWorld;

    result.color = in.color;
    result.normal = m_uniform->m_normalMatrix * in.normal;

    result.texcoord = in.texcoord;

    return result;
}

Vec4 PhongShader::fragmentShader(const VertexOut &in)
{
    Vec3 normal = Normalize(in.normal);
    Vec4 litColor = in.color;
    if (m_uniform->m_mainTex)
        litColor = m_uniform->m_mainTex->SampleTexture(in.texcoord);
    Vec3 amb, diff, spec;
    if (m_uniform->m_lights)
    {
        Vec3 a = m_uniform->m_eyePos - in.posWorld;
        Vec3 eyeDir = Normalize(m_uniform->m_eyePos - in.posWorld);
        Vec3 ambTmp, diffTmp, specTmp;
        for (int i = 0; i < m_uniform->m_lights->size(); ++i)
        {
            (*(m_uniform->m_lights))[i]->lighting(*(m_uniform->m_material), in.posWorld, normal, eyeDir, ambTmp, diffTmp, specTmp);
            amb += ambTmp;
            diff += diffTmp;
            spec += specTmp;
        }
        litColor.x *= (amb.x + diff.x + spec.x);
        litColor.y *= (amb.y + diff.y + spec.y);
        litColor.z *= (amb.z + diff.z + spec.z);
        litColor.w = 1.0f;
    }
    litColor.x /= (litColor.x + 1.0f);
    litColor.y /= (litColor.y + 1.0f);
    litColor.z /= (litColor.z + 1.0f);
    return litColor;
}
