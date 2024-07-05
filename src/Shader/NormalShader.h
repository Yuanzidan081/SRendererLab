#ifndef NORMALSHADER_H
#define NORMALSHADER_H

#include "Shader.h"

class NormalShader : public Shader
{
public:
    struct Varying
    {
        Vec2f varying_uv[3];
        Mat4x4f varying_M;
        Mat4x4f varying_MIT;
    };
    Varying varying;

    virtual Vec3f VertexShader(int faceInd, int VertInd) override;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) override;
};

#endif // NORMALSHADER_H