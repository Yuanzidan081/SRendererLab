#ifndef GOURAUDSHADER_H
#define GOURAUDSHADER_H
#include "Shader.h"

class GouraudShader : public Shader
{
private:
    GouraudShader() = default;
    GouraudShader(const GouraudShader &s) = delete;
    static GouraudShader *s_shader;

public:
    static GouraudShader *GetInstance();
    virtual void Destroy();
    ~GouraudShader() = default;
    virtual VertexOut vertexShader(const Vertex &in);
    virtual Vec4 fragmentShader(const VertexOut &in);
};

#endif // GOURAUDSHADER_H