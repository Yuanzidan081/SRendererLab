#ifndef CAMERA_H
#define CAMERA_H
#include "Math/Vec.h"
#include "Math/Mat.h"
class Camera
{

public:
    Camera(const Vec3f &pos = Vec3f(1.0f, 0.0f, 0.0f));
    ~Camera() = default;
    void SetCameraPos(const Vec3f &pos);
    void SetCameraPosZ(float z);
    Vec3f &GetCameraPos() { return m_Pos; }

    void SetCameraLookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up);
    Mat4x4f &GetCameraLookAt() { return m_CameraLookAt; }

private:
    Vec3f m_Pos = {2.0f, 1.0f, 3.0f};
    Mat4x4f m_CameraLookAt;
};

#endif // CAMERA_H