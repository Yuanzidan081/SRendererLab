#ifndef GOURAUDSHADER_H
#define GOURAUDSHADER_H
#include "Shader.h"
class GouraudShader : public Shader
{
private:
public:
    GouraudShader();
    ~GouraudShader();
    virtual void VertexShader() override;
    virtual void FragmentShader() override;
};

#endif // GOURAUDSHADER_H