#ifndef GOURAUDSHADER_H
#define GOURAUDSHADER_H
#include "Shader.h"
#include "Math/Vec.h"

class GouraudShader : public Shader
{
public:
    Vec3f m_intensity;

    virtual Vec3f VertexShader(int faceInd, int VertInd) override;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) override;
};



#endif // GOURAUDSHADER_H