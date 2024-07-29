#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H
#include "Shader.h"
class SimpleShader : public Shader
{
public:
    SimpleShader();
    virtual ~SimpleShader() = default;
    virtual Vec3f VertexShader(int faceInd, int VertInd);
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color);
    void SetModel(Model *model) { this->model = model; }
    virtual void SetEyePos(const Vec3f &eye) {}
};
#endif // SIMPLE_SHADER_H