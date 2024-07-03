#include "GouraudShader.h"

Vec3f GouraudShader::VertexShader(Model *model, int faceInd, int VertInd)
{
    m_intensity[VertInd] = std::max(0.0f, VecGetDotProduct(model->m_Normals[model->m_Faces[faceInd][VertInd][2]], shaderData.lightDir));
    Vec4f position(model->m_Vertices[model->m_Faces[faceInd][VertInd][0]], 1.0f);

    return Vec3f(shaderData.screenViewportMat *
                 shaderData.cameraProjectionMat *
                 shaderData.cameraViewMat *
                 shaderData.modelTransMat * position);
}

bool GouraudShader::FragmentShader(v2f* v2fData, Vec4f &color)
{
    float intensity = (v2fData->triangleCoeff.u * m_intensity[0] * v2fData->oneDivideZ[0] +
                     v2fData->triangleCoeff.v * m_intensity[1] * v2fData->oneDivideZ[1] + 
                     v2fData->triangleCoeff.w * m_intensity[2] * v2fData->oneDivideZ[2]) / v2fData->oneDividepixelZ;
    intensity = (intensity > 1.f ? 1.f : (intensity < 0.f ? 0.f : intensity));

    color = Vec4f(intensity, intensity, intensity, 1.0f);
    return false;
}
