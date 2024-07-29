#ifndef SHADER_H
#define SHADER_H
#include "Math/Vec.h"
#include "Render/Model.h"
#include "Core/Base.h"
#include "Render/ShaderData.h"
class Shader
{
public:
    Model *model;
    Shader() = default;
    virtual ~Shader() = default;
    virtual Vec3f VertexShader(int faceInd, int VertInd) = 0;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) = 0;
    void SetModel(Model *model) { this->model = model; }
    virtual void SetEyePos(const Vec3f &eye) = 0;
};

#endif // SHADER_H