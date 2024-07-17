#include "NormalShader.h"
Vec3f NormalShader::VertexShader(int faceInd, int VertInd)
{
    varying.varying_uv[VertInd] = model->m_UVCoords[model->m_Faces[faceInd][VertInd][1]];
    varying.varying_normal[VertInd] = Vec3f(shaderData.modelTransViewMatInv * Vec4f(model->m_Normals[model->m_Faces[faceInd][VertInd][2]], 1.0f));
    Vec4f position = shaderData.modelTransViewMat * Vec4f(model->m_Vertices[model->m_Faces[faceInd][VertInd][0]], 1.0f);
    varying.triangleCoordClip[VertInd] = position;
    varying.triangleNdcNorm[VertInd] = Vec3f(position / position.w);
    return position;
}

bool NormalShader::FragmentShader(v2f *v2fData, Vec4f &color)
{
    Vec2f uv = interpolateCorrection(v2fData, varying.varying_uv);
    Vec3f bn = VecGetNormalize(interpolateCorrection(v2fData, varying.varying_normal));
    Mat3x3f A;
    A.SetRow(0, varying.triangleNdcNorm[1] - varying.triangleNdcNorm[0]);
    A.SetRow(1, varying.triangleNdcNorm[2] - varying.triangleNdcNorm[0]);
    A.SetRow(2, bn);
    Mat3x3f AI = MatGetInverse(A);
    Vec3f i = AI * Vec3f(varying.varying_uv[1][0] - varying.varying_uv[0][0],
                         varying.varying_uv[2][0] - varying.varying_uv[0][0], 0.0f);
    Vec3f j = AI * Vec3f(varying.varying_uv[1][1] - varying.varying_uv[0][1],
                         varying.varying_uv[2][1] - varying.varying_uv[0][1], 0.0f);
    Mat3x3f B;
    B.SetCol(0, VecGetNormalize(i));
    B.SetCol(1, VecGetNormalize(j));
    B.SetCol(2, bn);
    Vec3f n = VecGetNormalize(B * Vec3f(model->GetNormalColor(uv)));

    float diff = std::max(0.0f, VecGetDotProduct(n, shaderData.lightDir));
    color = model->GetDiffuseColor(uv) * diff;
    color.a = 1.0f;
    return false;
}