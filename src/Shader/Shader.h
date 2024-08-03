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
    virtual void BindShaderTexture(Texture2D *tex) = 0;
    virtual Vec3f VertexShader(int faceInd, int VertInd) = 0;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) = 0;
    virtual VertexOut vertexShader(const Vertex &in) = 0;
    virtual Vec4f fragmentShader(const VertexOut &in) = 0;
    void SetModel(Model *model)
    {
        this->model = model;
    }
    virtual void SetEyePos(const Vec3f &eye) = 0;
    virtual void SetModelMatrix(const Mat4x4f &world) = 0;
    virtual void SetViewMatrix(const Mat4x4f &view) = 0;
    virtual void SetProjectMatrix(const Mat4x4f &project) = 0;
};

#endif // SHADER_H