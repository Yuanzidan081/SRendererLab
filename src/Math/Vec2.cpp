#include "Vec2.h"

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
