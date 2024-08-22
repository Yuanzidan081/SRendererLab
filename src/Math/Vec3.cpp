#include "Vec3.h"
#include "Vec4.h"
Vec3::Vec3(const Vec4 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
{
}

Vec3 Vec3::operator=(Vec4 &v)
{
    return Vec3(v.x, v.y, v.z);
}

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

Vec3 Normalize(const Vec3 &v)
{
    float length;
    float scalefactor;
    length = v.GetLength();
    scalefactor = 1.0f / length;
    Vec3 result = v;
    result.x *= scalefactor;
    result.y *= scalefactor;
    result.z *= scalefactor;
    return result;
}

Vec3 operator*(const float rhs, const Vec3 &v)
{
    return Vec3(v.x * rhs, v.y * rhs, v.z * rhs);
}
