#include "Shader.h"

Uniform::Uniform() : eye(Vec3(0.0f, 0.0f, 0.0f)),
                     world(),
                     normalMatrix(),
                     view(),
                     project(),
                     material(nullptr),
                     lights(nullptr),
                     mainTexture(nullptr)
{
}

Uniform::Uniform(const Mat4x4 m, const Mat4x4 v, const Mat4x4 p) : eye(Vec3(0.0f, 0.0f, 0.0f)),
                                                                   world(m),
                                                                   normalMatrix(m.GetInverseTranspose()),
                                                                   view(v),
                                                                   project(p),
                                                                   material(nullptr),
                                                                   lights(nullptr),
                                                                   mainTexture(nullptr)
{
}
