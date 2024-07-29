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
    virtual void SetEyePos(const Vec3f &eye) { m_eyePos = eye; }

private:
    Vec3f m_eyePos;
};

#endif // TEXTURESHADER_H