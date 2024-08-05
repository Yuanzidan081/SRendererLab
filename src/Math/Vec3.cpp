#include "Vec3.h"

void Vec3::Normalize()
{
    float length;
    float scalefactor;
    length = GetLength();
    if (Equal(length, 1.0) || Equal(length, 0))
        return;
    scalefactor = 1.0f / length;
    x *= scalefactor;
    y *= scalefactor;
    z *= scalefactor;
}

Vec3 Vec3::GetNormalize() const
{
    Vec3 result(*this);
    result.Normalize();
    return result;
}

std::ostream &operator<<(std::ostream &os, Vec3 &m)
{
    os << "(" << m.x << ", " << m.y << ", " << m.z << ")" << std::endl;
    return os;
}
