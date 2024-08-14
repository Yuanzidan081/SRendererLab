#ifndef GOURAUDSHADER_H
#define GOURAUDSHADER_H
#include "Shader.h"

class GouraudShader : public Shader
{
public:
    GouraudShader();
    ~GouraudShader() = default;
    virtual VertexOut vertexShader(const Vertex &in);
    virtual Vec4 fragmentShader(const VertexOut &in);
    virtual void BindShaderTexture(Texture2D *tex) { m_tex = tex; }

    virtual void SetEyePos(const Vec3 &eye) { m_eyePos = eye; }
    virtual void SetModelMatrix(const Mat4x4 &world)
    {
        m_modelMatrix = world;
        m_invTransposeModelMatrix = m_modelMatrix.GetInverseTranspose();
    }
    virtual void SetViewMatrix(const Mat4x4 &view)
    {
        m_viewMatrix = view;
    }
    virtual void SetProjectMatrix(const Mat4x4 &project)
    {
        m_projectMatrix = project;
    }
    virtual void SetMaterial(const Material *material);

    virtual void SetLight(const std::vector<Light *> *light);

private:
    Vec3 m_eyePos;
    Texture2D *m_tex;
    Mat4x4 m_modelMatrix;
    Mat4x4 m_invModelMatrix;
    Mat4x4 m_invTransposeModelMatrix;
    Mat4x4 m_viewMatrix;
    Mat4x4 m_projectMatrix;

    const std::vector<Light *> *m_lights;
    const Material *m_material;
};

#endif // GOURAUDSHADER_H