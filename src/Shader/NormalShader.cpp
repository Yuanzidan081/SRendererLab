#include "NormalShader.h"
// Vec3f NormalShader::VertexShader(int faceInd, int VertInd)
// {
//     varying.varying_M = shaderData.cameraViewMat * shaderData.modelTransMat;
//     varying.varying_MIT = MatGetInverse(varying.varying_M);
//     varying.varying_uv[VertInd] = model->m_UVCoords[model->m_Faces[faceInd][VertInd][1]];
//     Vec4f position(model->m_Vertices[model->m_Faces[faceInd][VertInd][0]], 1.0f);
//     return Vec3f(shaderData.screenViewportMat *
//                  shaderData.cameraProjectionMat *
//                  shaderData.cameraViewMat *
//                  shaderData.modelTransMat *
//                  position);
// }

// bool NormalShader::FragmentShader(v2f *v2fData, Vec4f &color)
// {
//     Vec2f uv = interpolateCorrection(v2fData, varying.varying_uv);
//     Vec3f n = VecGetNormalize(VecProject<3>(varying.varying_MIT * Vec4f(model->GetNormalColor(uv))));

//     Vec3f l = VecGetNormalize(VecProject<3>(varying.varying_M * Vec4f(shaderData.lightDir, 1.0f)));
//     float intensity = std::max(0.0f, VecGetDotProduct(n, l));

//     color = model->GetDiffuseColor(uv) * intensity;
//     color.a = 1.0f;
//     return false;
// }

VertexOut NormalShader::vertexShader(const Vertex &in)
{
    return VertexOut();
}

Vec4 NormalShader::fragmentShader(const VertexOut &in)
{
    return Vec4();
}
