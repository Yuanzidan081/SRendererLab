#ifndef BASIC_CAMERA_H
#define BASIC_CAMERA_H
#include "Math/Vec.h"
#include "Math/Mat.h"

class BasicCamera
{
public:
    // local axis
    // Here LocalForward should (0,0,-1).
    static const Vec3f LocalForward;
    static const Vec3f LocalUp;
    static const Vec3f LocalRight;
    BasicCamera() = default;
    virtual ~BasicCamera() {}

    // Getter
    virtual Mat4x4f GetViewMatrix() = 0;
    virtual Vec3f GetPosition() = 0;
};
#endif // BASIC_CAMERA_H