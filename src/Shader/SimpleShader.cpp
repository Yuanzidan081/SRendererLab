#include "SimpleShader.h"

SimpleShader::SimpleShader()
{
}

Vec3f SimpleShader::VertexShader(int faceInd, int VertInd)
{
    return Vec3f();
}

bool SimpleShader::FragmentShader(v2f *v2fData, Vec4f &color)
{
    return false;
}
