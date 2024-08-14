#include "PhongShader.h"
#include "Render/Material.h"
#include "Render/Light.h"
PhongShader::PhongShader() : Shader()
{
}

VertexOut PhongShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_modelMatrix * in.position;
    result.posProj = m_projectMatrix * m_viewMatrix * result.posWorld;
    result.color = in.color;
    result.normal = m_invTransposeModelMatrix * Vec4(in.normal);
    result.texcoord = in.texcoord;

    return result;
}

Vec4 PhongShader::fragmentShader(const VertexOut &in)
{
    Vec4 litColor = in.color;
    if (m_tex)
        litColor = m_tex->SampleTexture(in.texcoord);
    Vec3 amb, diff, spec;
    if (m_lights)
    {
        Vec3 eyeDir = m_eyePos - in.posWorld;
        eyeDir.Normalize();
        Vec3 ambTmp, diffTmp, specTmp;
        for (int i = 0; i < (*m_lights).size(); ++i)
        {
            (*m_lights)[i]->lighting(*m_material, in.posWorld, in.normal, eyeDir, ambTmp, diffTmp, diffTmp);
            amb += ambTmp;
            diff += diffTmp;
            spec += specTmp;
        }

        litColor.x *= (amb.x + diff.x + spec.x);
        litColor.y *= (amb.y + diff.y + spec.y);
        litColor.z *= (amb.z + diff.z + spec.z);
        litColor.w = 1.0f;
    }
    return litColor;
}

void PhongShader::SetMaterial(const Material *material)
{
    m_material = material;
}

void PhongShader::SetLight(const std::vector<Light *> *lights)
{
    m_lights = lights;
}
