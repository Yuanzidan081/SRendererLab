#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H
#include "Shader.h"
class SimpleShader : public Shader
{

private:
    SimpleShader() = default;

    SimpleShader(const SimpleShader &s) = delete;
    static SimpleShader *s_shader;

public:
    static SimpleShader *GetInstance();
    ~SimpleShader() {};
    virtual void Destroy();
    virtual VertexOut VertexShader(const Vertex &in);
    virtual Vec4 FragmentShader(const VertexOut &in);
};
#endif // SIMPLE_SHADER_H