#ifndef BASIC_CAMERA_H
#define BASIC_CAMERA_H
#include "Math/MathGroup.h"
class BasicCamera
{
public:
    // local axis
    // Here LocalForward should (0,0,-1).
    static const Vec3 LocalForward;
    static const Vec3 LocalUp;
    static const Vec3 LocalRight;
    BasicCamera() = default;
    virtual ~BasicCamera() {}

    // Getter
    virtual Mat4x4 GetViewMatrix() = 0;
    virtual Vec3 GetPosition() = 0;


};
#endif // BASIC_CAMERA_H