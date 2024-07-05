#include "PhongShader.h"

Vec3f PhongShader::VertexShader(int faceInd, int VertInd)
{
    varying.varying_M = shaderData.cameraViewMat * shaderData.modelTransMat;
    varying.varying_MIT = MatGetInverse(varying.varying_M);
    varying.varying_uv[VertInd] = model->m_UVCoords[model->m_Faces[faceInd][VertInd][1]];
    Vec4f position(model->m_Vertices[model->m_Faces[faceInd][VertInd][0]], 1.0f);
    return Vec3f(shaderData.screenViewportMat *
                 shaderData.cameraProjectionMat *
                 shaderData.cameraViewMat *
                 shaderData.modelTransMat * position);
}

bool PhongShader::FragmentShader(v2f *v2fData, Vec4f &color)
{
    Vec2f uv = interpolateCorrection(v2fData, varying.varying_uv);
    Vec3f n = VecGetNormalize(Vec3f(varying.varying_MIT * Vec4f(model->GetNormalColor(uv))));
    Vec3f l = VecGetNormalize(Vec3f(varying.varying_M * Vec4f(shaderData.lightDir, 1.0f)));
    Vec3f r = VecGetNormalize(VecGetDotProduct(n, l) * 2.0f * n - l);
    float spec = pow(std::max(0.0f, r.z), model->GetSpecularColor(uv));
    float diffuse = std::max(0.0f, VecGetDotProduct(n, l));

    Vec4f c = model->GetDiffuseColor(uv);

    color.a = 1.0f;
    for (int i = 0; i < 3; ++i)
        color[i] = std::min(5.0f / 255.0f + c[i] * (0.6f * diffuse + spec), 1.0f);
    return false;
}
