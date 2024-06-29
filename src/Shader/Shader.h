#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
    Shader() {}
    virtual ~Shader() {}
    virtual void VertexShader() = 0;
    virtual void FragmentShader() = 0;
};

#endif // SHADER_H