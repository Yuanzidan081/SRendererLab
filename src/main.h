#ifndef MAIN_H
#define MAIN_H
#include "Core/Base.h"
#include "Math/Mat.h"
void RendererInit()
{
    // cameraEye = {1.5f, 1.0f, 10.0f};
    cameraEye = {1.0f, 1.0f, 3.0f};
    cameraCenter = {0.0f, 0.0f, 0.0f};
    cameraUp = {0.0f, 1.0f, 0.0f};

    shaderData.screenViewportMat = Mat4x4f::GetIdentity();
    shaderData.cameraProjectionMat = Mat4x4f::GetIdentity();
    shaderData.cameraViewMat = Mat4x4f::GetIdentity();
    shaderData.modelTransMat = Mat4x4f::GetIdentity();
    // shaderData.modelTransMat = Mat4x4GetScale(Vec3f(0.6f, 0.6f, 0.6f));
    shaderData.modelTransViewMat = shaderData.cameraViewMat * shaderData.modelTransMat;
    shaderData.modelTransViewMatInv = MatGetInverse(shaderData.modelTransViewMat);
    shaderData.lightDir = {1.0f, 1.0f, 1.0f};
}

#endif // MAIN_H