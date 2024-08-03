#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H
#include "Shader.h"
class SimpleShader : public Shader
{
public:
    SimpleShader();
    virtual ~SimpleShader() = default;
    virtual Vec3f VertexShader(int faceInd, int VertInd);
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color);
    virtual VertexOut vertexShader(const Vertex &in);
    virtual Vec4f fragmentShader(const VertexOut &in);
    void SetModel(Model *model) { this->model = model; }
    virtual void BindShaderTexture(Texture2D *tex) { m_tex = tex; }
    virtual void SetEyePos(const Vec3f &eye) {}
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
    Texture2D *m_tex;
    Mat4x4f m_modelMatrix;
    Mat4x4f m_invModelMatrix;
    Mat4x4f m_invTransposeModelMatrix;
    Mat4x4f m_viewMatrix;
    Mat4x4f m_projectMatrix;
};
#endif // SIMPLE_SHADER_H