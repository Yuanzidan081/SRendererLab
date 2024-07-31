#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H
#include "Shader.h"

class TextureShader : public Shader
{
public:
    struct Varying
    {
        float varying_intensity[3];
        Vec2f varying_uv[3];
    };
    Varying varying;

    virtual Vec3f VertexShader(int faceInd, int VertInd) override;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) override;
    virtual void BindShaderTexture(Texture2D *tex) { m_tex = tex; }
    virtual void SetEyePos(const Vec3f &eye) { m_eyePos = eye; }
    virtual void SetModelMatrix(const Mat4x4f &world)
    {
        m_modelMatrix = world;
        m_invModelMatrix = MatGetInverse(m_modelMatrix);
        m_invTransposeModelMatrix = m_invModelMatrix.GetTranspose();
    }
    virtual void SetViewMatrix(const Mat4x4f &view)
    {
        m_viewMatrix = view;
    }
    virtual void SetProjectMatrix(const Mat4x4f &project)
    {
        m_projectMatrix = project;
    }

private:
    Vec3f m_eyePos;
    Texture2D *m_tex;
    Mat4x4f m_modelMatrix;
    Mat4x4f m_invModelMatrix;
    Mat4x4f m_invTransposeModelMatrix;
    Mat4x4f m_viewMatrix;
    Mat4x4f m_projectMatrix;
};

#endif // TEXTURESHADER_H