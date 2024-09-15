#include "Vec4.h"

std::ostream &operator<<(std::ostream &os, Vec4 &m)
{
    os << "(" << m.x << ", " << m.y << ", " << m.z << ", " << m.w << ")" << std::endl;
    return os;
}

Vec4 Lerp3(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, const Vec3 &weight)
{
    return Vec4(
        v1.x * weight.x + v2.x * weight.y + v3.x * weight.z,
        v1.y * weight.x + v2.y * weight.y + v3.y * weight.z,
        v1.z * weight.x + v2.z * weight.y + v3.z * weight.z,
        v1.w * weight.x + v2.w * weight.y + v3.w * weight.z);
}

Vec3 Vec4::GetNormalize3D() const
{
    Vec3 result(x, y, z);
    result.Normalize();
    return result;
}
