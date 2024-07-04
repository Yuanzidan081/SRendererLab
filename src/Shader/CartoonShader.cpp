#include "CartoonShader.h"

Vec3f CartoonShader::VertexShader(int faceInd, int VertInd)
{
    m_intensity[VertInd] = std::max(0.0f, VecGetDotProduct(model->m_Normals[model->m_Faces[faceInd][VertInd][2]], VecGetNormalize(shaderData.lightDir)));
    Vec4f position(model->m_Vertices[model->m_Faces[faceInd][VertInd][0]], 1.0f);

    return Vec3f(shaderData.screenViewportMat *
                 shaderData.cameraProjectionMat *
                 shaderData.cameraViewMat *
                 shaderData.modelTransMat * position);
}

bool CartoonShader::FragmentShader(v2f *v2fData, Vec4f &color)
{
    float intensity = (v2fData->triangleCoeff.u * m_intensity[0] * v2fData->oneDivideZ[0] +
                       v2fData->triangleCoeff.v * m_intensity[1] * v2fData->oneDivideZ[1] +
                       v2fData->triangleCoeff.w * m_intensity[2] * v2fData->oneDivideZ[2]) /
                      v2fData->oneDividepixelZ;
    if (intensity > 0.85f)
        intensity = 1.0f;
    else if (intensity > 0.60f)
        intensity = 0.80f;
    else if (intensity > 0.45f)
        intensity = 0.60f;
    else if (intensity > 0.30f)
        intensity = 0.45f;
    else if (intensity > 0.15f)
        intensity = 0.30f;
    else
        intensity = 0.0f;
    color = Vec4f(intensity, intensity, intensity, 1.0f) * Vec4f(1.0f, 0.6f, 0.0f, 1.0f);
    return false;
}
