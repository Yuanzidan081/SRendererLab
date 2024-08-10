#include "PhongShader.h"

PhongShader::PhongShader(): Shader()
{
}

VertexOut PhongShader::vertexShader(const Vertex &in)
{
    VertexOut result;
    result.posWorld = m_modelMatrix * in.position;
    result.posProj = m_projectMatrix * m_viewMatrix * result.posWorld;
    result.color = in.color;
    result.normal = in.normal;
    result.texcoord = in.texcoord;

    return result;
}

Vec4 PhongShader::fragmentShader(const VertexOut &in)
{
    return Vec4();
}

// Vec3f PhongShader::VertexShader(int faceInd, int VertInd)
// {

//     varying.varying_uv[VertInd] = model->m_UVCoords[model->m_Faces[faceInd][VertInd][1]];
//     varying.varying_normal[VertInd] = VecProject<3>(shaderData.modelTransViewMatInv * Vec4f(model->m_Normals[model->m_Faces[faceInd][VertInd][2]], 1.0f));
//     Vec4f position(model->m_Vertices[model->m_Faces[faceInd][VertInd][0]], 1.0f);
//     return Vec3f(shaderData.screenViewportMat *
//                  shaderData.modelTransViewMat * position);
// }

// bool PhongShader::FragmentShader(v2f *v2fData, Vec4f &color)
// {
//     Vec2f uv = interpolateCorrection(v2fData, varying.varying_uv);
//     Vec3f n = VecGetNormalize(interpolateCorrection(v2fData, varying.varying_normal));
//     Vec3f l = VecGetNormalize(VecProject<3>(shaderData.modelTransViewMat * Vec4f(shaderData.lightDir, 1.0f)));
//     Vec3f r = VecGetNormalize(VecGetDotProduct(n, l) * 2.0f * n - l);
//     float spec = pow(std::max(0.0f, r.z), model->GetSpecularColor(uv)); // 以上都是定义在相机空间
//     float diffuse = std::max(0.0f, VecGetDotProduct(n, l));

//     Vec4f c = model->GetDiffuseColor(uv);

//     color.a = 1.0f;
//     for (int i = 0; i < 3; ++i)
//         color[i] = std::min(c[i] * (diffuse + spec), 1.0f);
//     return false;
// }
