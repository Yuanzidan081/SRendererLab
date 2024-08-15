#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
class Vec3;
class Mat4x4;
class Transformation
{
public:
    static Mat4x4 GetTranslate(const Vec3 &trandslation);
    static Mat4x4 GetScale(const Vec3 &scale);
    static Mat4x4 GetRotationX(const double angle);
    static Mat4x4 GetRotationY(const double angle);
    static Mat4x4 GetRotationZ(const double angle);
    static Mat4x4 GetRotationAxis(const double angle, const Vec3 &axis);
    static Mat4x4 GetIdentity();
};
#endif // TRANSFORMATION_H