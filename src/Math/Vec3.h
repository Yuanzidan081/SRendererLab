#ifndef VEC_3_H
#define VEC_3_H
#include <cmath>
#include "MathUtils.h"
#include <iostream>
class Vec4;
class Vec3
{
public:
    union
    {
        struct
        {
            float x, y, z;
        };
        struct
        {
            float r, g, b;
        };
        struct
        {
            float u, v, w;
        };
        float vec[3];
    };

    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    Vec3(const Vec3 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
    Vec3(const Vec4 &rhs);
    Vec3(const float *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}
    ~Vec3() = default;
    Vec3 operator=(Vec4 &v);

    // setter getter
    void Set(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
    }
    void SetX(float X) { x = X; }
    void SetY(float Y) { y = Y; }
    void SetZ(float Z) { y = Z; }
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetZ() const { return z; }

    // normalize
    void Normalize();
    Vec3 GetNormalize() const;

    // length
    float GetLength() const { return static_cast<float>(sqrt(x * x + y * y + z * z)); }
    float GetSquareLength() const { return static_cast<float>(x * x + y * y + z * z); }

    // product
    float GetDotProduct(const Vec3 &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    Vec3 GetCrossProduct(const Vec3 &rhs) const
    {
        return Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
    }

    // overloaded operators
    Vec3 operator+(const Vec3 &rhs) const { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
    Vec3 operator-(const Vec3 &rhs) const { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
    Vec3 operator*(const float rhs) const { return Vec3(x * rhs, y * rhs, z * rhs); }
    Vec3 operator/(const float rhs) const { return (rhs == 0) ? Vec3(0.0f, 0.0f, 0.0f) : Vec3(x / rhs, y / rhs, z / rhs); }

    bool operator==(const Vec3 &rhs) const { return (Equal(x, rhs.x) && Equal(y, rhs.y) && Equal(z, rhs.z)); }
    bool operator!=(const Vec3 &rhs) const { return !((*this) == rhs); }

    void operator+=(const Vec3 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
    }
    void operator-=(const Vec3 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
    }
    void operator*=(const float rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
    }
    void operator/=(const float rhs)
    {
        if (!Equal(rhs, 0.0))
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
        }
    }

    void operator/=(const Vec3 &rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
    }

    Vec3 operator-() const { return Vec3(-x, -y, -z); }
    Vec3 operator+() const { return *this; }
    Vec3 operator-(float val) const { return Vec3(x - val, y - val, z + val); }
    Vec3 operator+(float val) const { return Vec3(x + val, y + val, z + val); }
    float &operator[](size_t i) { return vec[i]; }
    const float &operator[](size_t i) const { return vec[i]; }
    // interpolation
    Vec3 GetLerp(const Vec3 &v2, const float factor) const { return (*this) * (1.0f - factor) + v2 * factor; }
    Vec3 GetQuadraticInterpolate(const Vec3 &v2, const Vec3 &v3, const float factor) const
    {
        return (*this) * (1.0f - factor) * (1.0f - factor) + v2 * 2.0f * factor * (1.0f - factor) + v3 * factor * factor;
    }
    friend std::ostream &operator<<(std::ostream &os, Vec3 &m);
};
std::ostream &operator<<(std::ostream &os, Vec3 &m);
Vec3 Normalize(const Vec3 &v);
Vec3 operator*(const float rhs, const Vec3 &v);

#endif // VEC_2_H