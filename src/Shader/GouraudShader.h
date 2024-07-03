#ifndef GOURAUDSHADER_H
#define GOURAUDSHADER_H
#include "Shader.h"
#include "Math/Mat.h"
#include "Math/Vec.h"
#include "Render/Texture2D.h"
#include "Render/Model.h"
class GouraudShader : public Shader
{
public:
    Vec3f m_intensity;
    float oneDivideZ[4];

    Vec3f VertexShader(Model *model, int faceInd, int VertInd) override;
    bool FragmentShader(v2f *v2fData, Vec4f &color) override;
};

#endif // GOURAUDSHADER_H