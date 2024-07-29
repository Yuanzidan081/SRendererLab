#ifndef PHONGSHADER_H
#define PHONGSHADER_H
#include "Shader.h"

class PhongShader : public Shader
{
public:
    struct Varying
    {
        Vec2f varying_uv[3];
        Vec3f varying_normal[3];
    };
    Varying varying;
    PhongShader();
    virtual ~PhongShader() = default;
    virtual Vec3f VertexShader(int faceInd, int VertInd) override;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) override;
    virtual void SetEyePos(const Vec3f &eye) { m_eyePos = eye; }

private:
    Vec3f m_eyePos;
};

#endif // PHONGSHADER_H