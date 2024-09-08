#include "Vec2.h"
#include "Vec3.h"
void Vec2::Normalize()
{
    float length;
    float scalefactor;
    length = GetLength();
    if (Equal(length, 1.0) || Equal(length, 0))
        return;
    scalefactor = 1.0f / length;
    x *= scalefactor;
    y *= scalefactor;
}

Vec2 Vec2::GetNormalize() const
{
    Vec2 result(*this);
    result.Normalize();
    return result;
}

std::ostream &operator<<(std::ostream &os, Vec2 &m)
{
    os << "(" << m.x << ", " << m.y << ")" << std::endl;
    return os;
}

Vec2 Lerp3(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec3 &weight)
{
    return Vec2(
        v1.x * weight.x + v2.x * weight.y + v3.x * weight.z,
        v1.y * weight.x + v2.y * weight.y + v3.y * weight.z);
}
