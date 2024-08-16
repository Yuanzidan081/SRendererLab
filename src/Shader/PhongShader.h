#ifndef PHONGSHADER_H
#define PHONGSHADER_H
#include "Shader.h"
class PhongShader : public Shader
{
private:
    PhongShader() = default;
    PhongShader(const PhongShader &s) = delete;
    static PhongShader *s_shader;

public:
    static PhongShader *GetInstance();
    virtual void Destroy();
    ~PhongShader() = default;
    virtual VertexOut vertexShader(const Vertex &in);
    virtual Vec4 fragmentShader(const VertexOut &in);
};

#endif // PHONGSHADER_H