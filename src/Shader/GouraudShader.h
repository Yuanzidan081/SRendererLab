#ifndef GOURAUDSHADER_H
#define GOURAUDSHADER_H
#include "Shader.h"


class GouraudShader : public Shader
{
public:
    Vec3 m_intensity;
    GouraudShader();
    ~GouraudShader() = default;
    // virtual Vec3 VertexShader(int faceInd, int VertInd) override;
    // virtual bool FragmentShader(v2f *v2fData, Vec4f &color) override;
    virtual VertexOut vertexShader(const Vertex &in);
    virtual Vec4 fragmentShader(const VertexOut &in);
    virtual void BindShaderTexture(Texture2D *tex) { m_tex = tex; }

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
    Texture2D *m_tex;
    Mat4x4 m_modelMatrix;
    Mat4x4 m_invModelMatrix;
    Mat4x4 m_invTransposeModelMatrix;
    Mat4x4 m_viewMatrix;
    Mat4x4 m_projectMatrix;
};

#endif // GOURAUDSHADER_H