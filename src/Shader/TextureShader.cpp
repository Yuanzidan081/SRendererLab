#include "TextureShader.h"

Vec3f TextureShader::VertexShader(int faceInd, int VertInd)
{
    varying.varying_intensity[VertInd] = std::max(0.0f, VecGetDotProduct(model->m_Normals[model->m_Faces[faceInd][VertInd][2]], VecGetNormalize(shaderData.lightDir)));
    varying.varying_uv[VertInd] = model->m_UVCoords[model->m_Faces[faceInd][VertInd][1]];
    Vec4f position(model->m_Vertices[model->m_Faces[faceInd][VertInd][0]], 1.0f);

    return Vec3f(shaderData.screenViewportMat *
                 shaderData.cameraProjectionMat *
                 shaderData.cameraViewMat *
                 shaderData.modelTransMat * position);
}

bool TextureShader::FragmentShader(v2f *v2fData, Vec4f &color)
{
    float intensity = interpolateCorrection(v2fData, varying.varying_intensity);
    Vec2f uv = interpolateCorrection(v2fData, varying.varying_uv);
    // color = model->diffuse(uv) * intensity;
    color = {1.0f, 0.3f, 0.3f, 1.0f};
    return false;
}
