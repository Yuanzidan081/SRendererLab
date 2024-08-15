#include "Transformation.h"
#include "Math/Vec3.h"
#include "Math/Mat4x4.h"
Mat4x4 Transformation::GetTranslate(const Vec3 &v)
{
    Mat4x4 result;
    result.SetTranslation(v);
    return result;
}

Mat4x4 Transformation::GetScale(const Vec3 &scale)
{
    Mat4x4 result;
    result.SetScale(scale);
    return result;
}

Mat4x4 Transformation::GetRotationX(const double angle)
{
    Mat4x4 result;
    result.SetRotationX(angle);
    return result;
}

Mat4x4 Transformation::GetRotationY(const double angle)
{
    Mat4x4 result;
    result.SetRotationY(angle);
    return result;
}

Mat4x4 Transformation::GetRotationZ(const double angle)
{
    Mat4x4 result;
    result.SetRotationZ(angle);
    return result;
}

Mat4x4 Transformation::GetRotationAxis(const double angle, const Vec3 &axis)
{
    Mat4x4 result;
    result.SetRotationAxis(angle, axis);
    return result;
}

Mat4x4 Transformation::GetIdentity()
{
    Mat4x4 result;
    result.LoadIdentity();
    return result;
}
