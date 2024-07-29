#ifndef GOURAUDSHADER_H
#define GOURAUDSHADER_H
#include "Shader.h"
#include "Math/Vec.h"

class GouraudShader : public Shader
{
public:
    Vec3f m_intensity;
    GouraudShader();
    ~GouraudShader() = default;
    virtual Vec3f VertexShader(int faceInd, int VertInd) override;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) override;
    virtual void SetEyePos(const Vec3f &eye) { m_eyePos = eye; }

private:
    Vec3f m_eyePos;
};

#endif // GOURAUDSHADER_H