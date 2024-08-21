#ifndef MAT4x4_H
#define MAT4x4_H

#include "MathUtils.h"
#include "Vec4.h"
#include "Mat3x3.h"
#include <iostream>
class Mat4x4
{
public:
    union
    {
        float mat[16];
        float entries[4][4];
    };

    // constructors
    Mat4x4() { LoadIdentity(); }
    Mat4x4(float e00, float e01, float e02, float e03,
           float e10, float e11, float e12, float e13,
           float e20, float e21, float e22, float e23,
           float e30, float e31, float e32, float e33);
    Mat4x4(const float *rhs);
    Mat4x4(const Mat4x4 &rhs);
    Mat4x4(const Mat3x3 &rhs);
    ~Mat4x4() = default;

    // setter,getter
    Vec4 GetRow(int position) const;
    Vec4 GetColumn(int position) const;
    void LoadIdentity();
    void LoadZero();

    // overloaded operators
    Mat4x4 operator+(const Mat4x4 &rhs) const;
    Mat4x4 operator-(const Mat4x4 &rhs) const;
    Mat4x4 operator*(const Mat4x4 &rhs) const;
    Mat4x4 operator*(const float rhs) const;
    Mat4x4 operator/(const float rhs) const;

    bool operator==(const Mat4x4 &rhs) const;
    bool operator!=(const Mat4x4 &rhs) const;

    void operator+=(const Mat4x4 &rhs);
    void operator-=(const Mat4x4 &rhs);
    void operator*=(const Mat4x4 &rhs);
    void operator*=(const float rhs);
    void operator/=(const float rhs);

    Mat4x4 operator-() const;
    Mat4x4 operator+() const { return (*this); }
    Vec4 operator*(const Vec4 rhs) const;
    float *operator[](size_t i) { return entries[i]; }
    const float *operator[](size_t i) const { return entries[i]; }

    // inverse, transpose
    void Inverted();
    Mat4x4 GetInverse() const;
    void Transpose();
    Mat4x4 GetTranspose() const;
    void InvertTranspose();
    Mat4x4 GetInverseTranspose() const;
    Mat4x4 GetNormalMatrix() const;

    // operation on space
    void SetTranslation(const Vec3 &translation);
    void SetScale(const Vec3 &scaleFactor);
    void SetRotationAxis(const double angle, const Vec3 &axis);
    void SetRotationX(const double angle);
    void SetRotationY(const double angle);
    void SetRotationZ(const double angle);
    void SetRotationEuler(const double angleX, const double angleY, const double angleZ);
    void SetPerspective(float fovy, float aspect, float near, float far);
    void SetOrtho(float left, float right, float bottom, float top, float near, float far);
    void SetLookAt(Vec3 cameraPos, Vec3 target, Vec3 worldUp);
    void SetLookAt(Vec3 cameraPos, Vec3 front, Vec3 right, Vec3 up);
    void SetViewPort(int left, int bottom, int width, int height);
    Mat3x3 GetMat3x3();

    friend std::ostream &operator<<(std::ostream &os, Mat4x4 &m);
};
std::ostream &operator<<(std::ostream &os, Mat4x4 &m);

#endif // MAT4x4_H