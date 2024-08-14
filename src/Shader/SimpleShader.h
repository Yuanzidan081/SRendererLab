#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H
#include "Shader.h"
class SimpleShader : public Shader
{
private:
    SimpleShader();
    SimpleShader(const SimpleShader &s) = delete;
    static SimpleShader *s_shader;

public:
    static SimpleShader *GetInstance();
    virtual ~SimpleShader() = default;
    void Destroy();
    virtual VertexOut vertexShader(const Vertex &in);
    virtual Vec4 fragmentShader(const VertexOut &in);
    virtual void BindShaderTexture(Texture2D *tex) { m_tex = tex; }
    virtual void SetEyePos(const Vec3 &eye) {}
    virtual void SetModelMatrix(const Mat4x4 &world)
    {
        m_modelMatrix = world;
    }
    virtual void SetViewMatrix(const Mat4x4 &view)
    {
        m_viewMatrix = view;
    }
    virtual void SetProjectMatrix(const Mat4x4 &project)
    {
        m_projectMatrix = project;
    }

private:
    Texture2D *m_tex;
    Mat4x4 m_modelMatrix;
    Mat4x4 m_viewMatrix;
    Mat4x4 m_projectMatrix;
};
#endif // SIMPLE_SHADER_H