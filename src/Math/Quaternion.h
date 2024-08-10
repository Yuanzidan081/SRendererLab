#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vec3.h"
#include "Mat4x4.h"
#include <iostream>
class Quaternion
{

public:
    const static Quaternion identity;
    double x, y, z, w;

    Quaternion();
    Quaternion(float X, float Y, float Z, float W);
    Quaternion(float yaw, float pitch, float roll);
    ~Quaternion() = default;

    void Set(float X, float Y, float Z, float W);
    void SetEulerAngle(float yaw, float pitch, float roll);
    void SetRotationAxis(Vec3 axis, double angle);

    Quaternion Inverse() const;
    Quaternion Conjugate() const;
    Vec3 EulerAngle() const;
    Mat4x4 ToMatrix() const;

    static float Dot(const Quaternion &lhs, const Quaternion &rhs);
    static Quaternion Lerp(const Quaternion &a, const Quaternion &b, float t);
    static Quaternion Slerp(const Quaternion &a, const Quaternion &b, float t);
    static float Angle(const Quaternion &lhs, const Quaternion &rhs);

    void operator*(float s);
    void operator+(const Quaternion &q);
    void operator-(const Quaternion &q);

    friend Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs);
    friend Vec3 operator*(const Quaternion &rotation, const Vec3 &point);
    friend std::ostream &operator<<(std::ostream &os, Quaternion &q);

private:
    Vec3 eulerAngles;
};

std::ostream &operator<<(std::ostream &os, Quaternion &q);
#endif // QUATERNION_H
