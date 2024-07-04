#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H
#include "Shader.h"

class TextureShader : public Shader
{
public:
    Varying varying;

    virtual Vec3f VertexShader(int faceInd, int VertInd) override;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) override;
};

#endif // TEXTURESHADER_H