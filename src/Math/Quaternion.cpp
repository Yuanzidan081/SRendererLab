#include "Quaternion.h"
const Quaternion Quaternion::identity(0, 0, 0, 1);
Quaternion::Quaternion()
{
    x = y = z = 0;
    w = 1;
}

Quaternion::Quaternion(float X, float Y, float Z, float W)
{
    double mag = X * X + Y * Y + Z * Z + W * W;
    x = X / mag;
    y = Y / mag;
    z = Z / mag;
    w = W / mag;
}

Quaternion::Quaternion(float yaw, float pitch, float roll)
{
    SetEulerAngle(yaw, pitch, roll);
}

void Quaternion::Set(float X, float Y, float Z, float W)
{
    x = X;
    y = Y;
    z = Z;
    w = W;
}
// rad
void Quaternion::SetEulerAngle(float yaw, float pitch, float roll)
{
    float angle;
    float sinRoll, sinPitch, sinYaw, cosRoll, cosPitch, cosYaw;

    angle = yaw * 0.5f;
    sinYaw = sin(angle);
    cosYaw = cos(angle);

    angle = pitch * 0.5f;
    sinPitch = sin(angle);
    cosPitch = cos(angle);

    angle = roll * 0.5f;
    sinRoll = sin(angle);
    cosRoll = cos(angle);

    float X = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
    float Y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
    float Z = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
    float W = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;

    double mag = X * X + Y * Y + Z * Z + W * W;
    x = X / mag;
    y = Y / mag;
    z = Z / mag;
    w = W / mag;
}

void Quaternion::SetRotationAxis(Vec3 axis, double angle)
{
    angle = deg2rad(angle);
    axis.Normalize();
    double angleDiv2 = angle * 0.5;
    double sinAngle = sin(angleDiv2);
    x = axis.x * sinAngle;
    y = axis.y * sinAngle;
    z = axis.z * sinAngle;
    w = cos(angleDiv2);
}

Quaternion Quaternion::Inverse() const
{
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::Conjugate() const
{
    return Quaternion(-x, -y, -z, w);
}

Vec3 Quaternion::EulerAngle() const
{
    float yaw = atan2(2 * (w * x + z * y), 1 - 2 * (x * x + y * y));
    float pitch = asin(2 * (w * y - x * z));
    float roll = atan2(2 * (w * z + x * y), 1 - 2 * (z * z + y * y));
    if (pitch < -1.0f)
        pitch = -1.0f;
    if (pitch > +1.0f)
        pitch = +1.0f;
    return Vec3(
        rad2deg(yaw),
        rad2deg(pitch),
        rad2deg(roll));
}

Mat4x4 Quaternion::ToMatrix() const
{
    Mat4x4 result(
        1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * z * w, 2.0f * x * z + 2.0f * y * w, 0.0f,
        2.0f * x * y + 2.0f * z * w, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * x * w, 0.0f,
        2.0f * x * z - 2.0f * y * w, 2.0f * y * z + 2.0f * x * w, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    result.Transpose();
    return result;
}

float Quaternion::Dot(const Quaternion &lhs, const Quaternion &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Quaternion Quaternion::Lerp(const Quaternion &a, const Quaternion &b, float t)
{
    return Quaternion(
        (1 - t) * a.x + t * b.x,
        (1 - t) * a.y + t * b.y,
        (1 - t) * a.z + t * b.z,
        (1 - t) * a.w + t * b.w);
}

Quaternion Quaternion::Slerp(const Quaternion &a, const Quaternion &b, float t)
{
    float cos_theta = Dot(a, b);

    // if B is on opposite hemisphere from A, use -B instead
    float sign;
    if (cos_theta < 0.f)
    {
        cos_theta = -cos_theta;
        sign = -1.f;
    }
    else
        sign = 1.f;

    float c1, c2;
    if (cos_theta > 1.f - 0.000001f)
    {
        // if q2 is (within precision limits) the same as q1,
        // just linear interpolate between A and B
        c2 = t;
        c1 = 1.f - t;
    }
    else
    {
        float theta = acos(cos_theta);
        float sin_theta = sin(theta);
        float t_theta = t * theta;
        float inv_sin_theta = 1.f / sin_theta;
        c2 = sin(t_theta) * inv_sin_theta;
        c1 = sin(theta - t_theta) * inv_sin_theta;
    }
    c2 *= sign;
    // interpolate
    return Quaternion(
        a.x * c1 + b.x * c2,
        a.y * c1 + b.y * c2,
        a.z * c1 + b.z * c2,
        a.w * c1 + b.w * c2);
}

float Quaternion::Angle(const Quaternion &lhs, const Quaternion &rhs)
{
    float cos_theta = Dot(lhs, rhs);
    if (cos_theta < 0.0f)
        cos_theta = -cos_theta;
    return 2.0f * rad2deg(acos(cos_theta));
}

void Quaternion::operator*(float s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;
}

void Quaternion::operator+(const Quaternion &q)
{
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;
}

void Quaternion::operator-(const Quaternion &q)
{
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;
}

Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs)
{
    float w1 = lhs.w;
    float w2 = rhs.w;
    Vec3 v1(lhs.x, lhs.y, lhs.z);
    Vec3 v2(rhs.x, rhs.y, rhs.z);
    float w3 = w1 * w2 - v1.GetDotProduct(v2);
    Vec3 v3 = v1.GetCrossProduct(v2) + v2 * w1 + v1 * w2;
    return Quaternion(v3.x, v3.y, v3.z, w3);
}

Vec3 operator*(const Quaternion &rotation, const Vec3 &point)
{
    // Extract the vector part of the quaternion
    Vec3 u(rotation.x, rotation.y, rotation.z);
    // Extract the scalar part of the quaternion
    float s = rotation.w;
    // Do the math
    return u * 2.0f * u.GetDotProduct(point) + point * (s * s - u.GetDotProduct(u)) + u.GetDotProduct(point) * 2.0f * s;
}

std::ostream &operator<<(std::ostream &os, Quaternion &q)
{
    os << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    return os;
}
