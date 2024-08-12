#include "GouraudShader.h"
#include "Render/Light.h"
#include "Render/Material.h"
GouraudShader::GouraudShader()
{
}
VertexOut GouraudShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_modelMatrix * in.position;
    result.posProj = m_projectMatrix * m_viewMatrix * result.posWorld;
    result.color = in.color;
    result.texcoord = in.texcoord;
    result.normal = m_invTransposeModelMatrix * Vec4(in.normal);

    if (m_tex)
        result.color = m_tex->SampleTexture(result.texcoord);
    Vec3 amb, diff, spec;
    if (m_light)
    {
        Vec3 eyeDir = m_eyePos - result.posWorld;
        eyeDir.Normalize();
        m_light->lighting(*m_material, result.posWorld, result.normal, eyeDir, amb, diff, spec);

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

void GouraudShader::SetMaterial(const Material *material)
{

    m_material = material;
}

void GouraudShader::SetLight(const Light *light)
{

    m_light = light;
}
