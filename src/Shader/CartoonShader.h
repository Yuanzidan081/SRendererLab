#ifndef CARTOONSHADER_H
#define CARTOONSHADER_H
#include "Shader.h"

class CartoonShader : public Shader
{
public:
    virtual VertexOut vertexShader(const Vertex &in);
    virtual Vec4 fragmentShader(const VertexOut &in);
    virtual void BindShaderTexture(Texture2D *tex) {}
    virtual void SetEyePos(const Vec3 &eye) { m_eyePos = eye; }
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
    Vec3 m_eyePos;
    Mat4x4 m_modelMatrix;
    Mat4x4 m_viewMatrix;
    Mat4x4 m_projectMatrix;
};

#endif // CARTOONSHADER_H