#ifndef MAT3x3_H
#define MAT3x3_H

#include "MathUtils.h"
#include "Vec4.h"
#include <iostream>
class Mat3x3
{
public:
    union
    {
        float mat[9];
        float entries[3][3];
    };

    // constructors
    Mat3x3() { LoadIdentity(); }
    Mat3x3(float e00, float e01, float e02,
           float e10, float e11, float e12,
           float e20, float e21, float e22);
    Mat3x3(const float *rhs);
    Mat3x3(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);
    Mat3x3(const Mat3x3 &rhs);
    ~Mat3x3() = default;

    // setter,getter
    Vec4 GetRow(int position) const;
    Vec4 GetColumn(int position) const;
    Mat3x3 Mat3x3::GetTranspose();
    void LoadIdentity();
    void LoadZero();

    // overloaded operators
    Mat3x3 operator+(const Mat3x3 &rhs) const;
    Mat3x3 operator-(const Mat3x3 &rhs) const;
    Mat3x3 operator*(const Mat3x3 &rhs) const;
    Mat3x3 operator*(const float rhs) const;
    Mat3x3 operator/(const float rhs) const;

    bool operator==(const Mat3x3 &rhs) const;
    bool operator!=(const Mat3x3 &rhs) const;

    void operator+=(const Mat3x3 &rhs);
    void operator-=(const Mat3x3 &rhs);
    void operator*=(const Mat3x3 &rhs);
    void operator*=(const float rhs);
    void operator/=(const float rhs);

    Mat3x3 operator-() const;
    Mat3x3 operator+() const { return (*this); }
    Vec3 operator*(const Vec3 rhs) const;
    float *operator[](size_t i) { return entries[i]; }
    const float *operator[](size_t i) const { return entries[i]; }

    friend std::ostream &operator<<(std::ostream &os, Mat3x3 &m);
    Mat3x3 GetLerp(const Mat3x3 &v2, const float factor) const { return (*this) * (1.0f - factor) + v2 * factor; }
};
std::ostream &operator<<(std::ostream &os, Mat3x3 &m);

#endif // Mat3x3_H