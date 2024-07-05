#ifndef SHADERDATA_H
#define SHADERDATA_H
#include "Math/Vec.h"
#include "Math/Mat.h"

class Model;
class Shader;
struct ShaderData
{
    Mat4x4f screenViewportMat;
    Mat4x4f cameraViewMat;
    Mat4x4f cameraProjectionMat;
    Mat4x4f modelTransMat;
    Vec3f lightDir;
};
struct DrawData
{
    Model *model = nullptr;
    Shader *shader = nullptr;
    ~DrawData()
    {
        if (model)
            delete model;
        if (shader)
            delete shader;
        model = nullptr;
        shader = nullptr;
    }
};
struct v2f
{
    Vec3f oneDivideZ;
    float oneDividepixelZ;
    Vec3f triangleCoeff;
};

template <typename T>
T interpolateCorrection(v2f *v2fData, T *varying)
{
    return ((v2fData->triangleCoeff.u * varying[0] * v2fData->oneDivideZ[0] +
             v2fData->triangleCoeff.v * varying[1] * v2fData->oneDivideZ[1] +
             v2fData->triangleCoeff.w * varying[2] * v2fData->oneDivideZ[2]) /
            v2fData->oneDividepixelZ);
}

#endif // SHADERDATA_H
