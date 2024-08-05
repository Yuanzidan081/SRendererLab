#ifndef NORMALSHADER_H
#define NORMALSHADER_H

#include "Shader.h"

class NormalShader : public Shader
{
public:
    // struct Varying
    // {
    //     Vec2f varying_uv[3];
    //     Mat4x4 varying_M;
    //     Mat4x4 varying_MIT;
    // };
    // Varying varying;

    // virtual Vec3 VertexShader(int faceInd, int VertInd) override;
    // virtual bool FragmentShader(v2f *v2fData, Vec4 &color) override;
    virtual VertexOut vertexShader(const Vertex &in);
    virtual Vec4 fragmentShader(const VertexOut &in);
    virtual void SetEyePos(const Vec3 &eye) { m_eyePos = eye; }
    virtual void BindShaderTexture(Texture2D *tex) { m_tex = tex; }
    virtual void SetModelMatrix(const Mat4x4 &world)
    {
        m_modelMatrix = world;
        m_invModelMatrix = m_modelMatrix.GetInverse();
        m_invTransposeModelMatrix = m_invModelMatrix.GetTranspose();
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
    Texture2D *m_tex;
    Mat4x4 m_modelMatrix;
    Mat4x4 m_invModelMatrix;
    Mat4x4 m_invTransposeModelMatrix;
    Mat4x4 m_viewMatrix;
    Mat4x4 m_projectMatrix;
};

#endif // NORMALSHADER_H