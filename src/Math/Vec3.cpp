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
    if (Equal(length, 1.0) || Equal(length, 0))
        return v;
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

Vec3 Pow(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(std::pow(v1.x, v2.x), std::pow(v1.y, v2.y), std::pow(v1.z, v2.z));
}

Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}
