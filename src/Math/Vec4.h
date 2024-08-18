#ifndef Vec_4_H
#define Vec_4_H

#include <cmath>
#include "MathUtils.h"
#include "Vec3.h"
class Vec4
{
public:
    union
    {
        struct
        {
            float x, y, z, w;
        };
        struct
        {
            float r, g, b, a;
        };
        float vec[4];
    };

    Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vec4(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}
    Vec4(const Vec4 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
    Vec4(const float *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]), w(ptr[3]) {}
    Vec4(const Vec3 &rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f) {}
    ~Vec4() = default;

    // setter getter
    void Set(float X, float Y, float Z, float W)
    {
        x = X;
        y = Y;
        z = Z;
        w = W;
    }
    void SetX(float X) { x = X; }
    void SetY(float Y) { y = Y; }
    void SetZ(float Z) { y = Z; }
    void SetW(float W) { w = W; }
    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetZ() const { return z; }
    float GetW() const { return w; }

    // overloaded operators
    Vec4 operator+(const Vec4 &rhs) const { return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
    Vec4 operator-(const Vec4 &rhs) const { return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
    Vec4 operator*(const float rhs) const { return Vec4(x * rhs, y * rhs, z * rhs, w * rhs); }
    Vec4 operator/(const float rhs) const { return (rhs == 0) ? Vec4(0.0f, 0.0f, 0.0f, 0.0f) : Vec4(x / rhs, y / rhs, z / rhs, w / rhs); }

    bool operator==(const Vec4 &rhs) const { return (Equal(x, rhs.x) && Equal(y, rhs.y) && Equal(z, rhs.z) && Equal(w, rhs.w)); }
    bool operator!=(const Vec4 &rhs) const { return !((*this) == rhs); }
    float &operator[](size_t i) { return vec[i]; }
    const float &operator[](size_t i) const { return vec[i]; }

    void operator+=(const Vec4 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
    }
    void operator-=(const Vec4 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
    }
    void operator*=(const float rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
    }
    void operator/=(const float rhs)
    {
        if (!Equal(rhs, 0.0))
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            w /= rhs;
        }
    }

    Vec4 operator-() const { return Vec4(-x, -y, -z, -w); }
    Vec4 operator+() const { return *this; }
    Vec4 operator-(float val) const { return Vec4(x - val, y - val, z - val, w - val); }
    Vec4 operator+(float val) const { return Vec4(x + val, y + val, z + val, w + val); }

    // interpolation
    Vec4 GetLerp(const Vec4 &v2, const float factor) const { return (*this) * (1.0f - factor) + v2 * factor; }
    Vec4 GetQuadraticInterpolate(const Vec4 &v2, const Vec4 &v3, const float factor) const
    {
        return (*this) * (1.0f - factor) * (1.0f - factor) + v2 * 2.0f * factor * (1.0f - factor) + v3 * factor * factor;
    }
    friend std::ostream &operator<<(std::ostream &os, Vec4 &m);
    Vec3 GetNormalize3D() const;
};
std::ostream &operator<<(std::ostream &os, Vec4 &m);

#endif // Vec_4_H
