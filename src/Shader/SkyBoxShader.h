#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H
#include "Shader.h"
class SkyBoxShader : public Shader
{
private:
    SkyBoxShader() = default;
    SkyBoxShader(const SkyBoxShader &s) = delete;
    static SkyBoxShader *s_shader;

public:
    static SkyBoxShader *GetInstance();
    virtual ~SkyBoxShader() = default;
    virtual void SkyBoxShader::Destroy();
    virtual VertexOut VertexShader(const Vertex &in);
    virtual Vec4 FragmentShader(const VertexOut &in);
};
#endif // SKYBOXSHADER_H