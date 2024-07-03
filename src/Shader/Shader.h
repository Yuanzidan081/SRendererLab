#ifndef SHADER_H
#define SHADER_H
#include "Math/Vec.h"
#include "Render/Model.h"
#include "Core/Base.h"

class Shader
{
public:
    virtual ~Shader();
    virtual Vec3f VertexShader(Model *model, int faceInd, int VertInd) = 0;
    virtual bool FragmentShader(v2f *v2fData, Vec4f &color) = 0;
};

#endif // SHADER_H