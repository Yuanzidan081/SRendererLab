#include "Vec4.h"

std::ostream &operator<<(std::ostream &os, Vec4 &m)
{
    os << "(" << m.x << ", " << m.y << ", " << m.z << ", " << m.w << ")" << std::endl;
    return os;
}

Vec3 Vec4::GetNormalize3D() const
{
    Vec3 result(x, y, z);
    result.Normalize();
    return result;
}
