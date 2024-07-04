#ifndef CARTOONSHADER_H
#define CARTOONSHADER_H
#include "Shader.h"

class CartoonShader : public Shader
{
public:
    Vec3f m_intensity;

    virtual Vec3f VertexShader(int faceInd, int VertInd) override;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) override;
};

#endif // CARTOONSHADER_H