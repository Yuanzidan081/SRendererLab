#ifndef VEC_2_H
#define VEC_2_H
#include <cmath>
#include "MathUtils.h"
#include <iostream>
class Vec3;
class Vec2
{
public:
    union
    {
        struct
        {
            float x, y;
        };
        struct
        {
            float u, v;
        };
        float vec[2];
    };
    Vec2() : x(0.0f), y(0.0f) {}

    Vec2(float X, float Y) : x(X), y(Y) {}
    Vec2(const Vec2 &rhs) : x(rhs.x), y(rhs.y) {}
    Vec2(const float *ptr) : x(ptr[0]), y(ptr[1]) {}
    ~Vec2() = default;

    // setter getter
    void Set(float X, float Y)
    {
        x = X;
        y = Y;
    }
    void SetX(float X) { x = X; }
    void SetY(float Y) { y = Y; }
    float GetX() const { return x; }
    float GetY() const { return y; }

    // normalize
    void Normalize();
    Vec2 GetNormalize() const;

    // length
    float GetLength() const { return static_cast<float>(sqrt(x * x + y * y)); }
    float GetSquareLength() const { return static_cast<float>(x * x + y * y); }

    // overloaded operators
    Vec2 operator+(const Vec2 &rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
    Vec2 operator-(const Vec2 &rhs) const { return Vec2(x - rhs.x, y - rhs.y); }
    Vec2 operator*(const float rhs) const { return Vec2(x * rhs, y * rhs); }
    Vec2 operator/(const float rhs) const { return (rhs == 0) ? Vec2(0.0f, 0.0f) : Vec2(x / rhs, y / rhs); }

    bool operator==(const Vec2 &rhs) const { return (Equal(x, rhs.x) && Equal(y, rhs.y)); }
    bool operator!=(const Vec2 &rhs) const { return !((*this) == rhs); }

    void operator+=(const Vec2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }
    void operator-=(const Vec2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
    }
    void operator*=(const float rhs)
    {
        x *= rhs;
        y *= rhs;
    }
    void operator/=(const float rhs)
    {
        if (!Equal(rhs, 0.0))
        {
            x /= rhs;
            y /= rhs;
        }
    }

    Vec2 operator-() const { return Vec2(-x, -y); }
    Vec2 operator+() const { return *this; }
    Vec2 operator-(float val) const { return Vec2(x - val, y - val); }
    Vec2 operator+(float val) const { return Vec2(x + val, y + val); }

    float &operator[](size_t i) { return vec[i]; }
    const float &operator[](size_t i) const { return vec[i]; }

    // interpolation
    Vec2 GetLerp(const Vec2 &v2, const float factor) const { return (*this) * (1.0f - factor) + v2 * factor; }
    Vec2 GetQuadraticInterpolate(const Vec2 &v2, const Vec2 &v3, const float factor) const
    {
        return (*this) * (1.0f - factor) * (1.0f - factor) + v2 * 2.0f * factor * (1.0f - factor) + v3 * factor * factor;
    }
};
std::ostream &operator<<(std::ostream &os, Vec2 &m);
Vec2 Lerp3(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec3 &weight);

#endif // VEC_2_H