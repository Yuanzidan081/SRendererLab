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
    Model *model;
    Shader *shader;
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

#endif // SHADERDATA_H
