#ifndef NaiveCAMERA_H
#define NaiveCAMERA_H
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "BasicCamera.h"
class NaiveCamera : public BasicCamera
{

public:
    NaiveCamera(const Vec3f &pos = Vec3f(1.0f, 0.0f, 0.0f));
    ~NaiveCamera() = default;
    void SetCameraPos(const Vec3f &pos);
    void SetCameraPosZ(float z);

    void SetCameraLookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up);
    // Mat4x4f &GetCameraLookAt() { return m_CameraLookAt; }
    virtual Mat4x4f GetViewMatrix() { return m_CameraLookAt; }
    virtual Vec3f GetPosition() { return m_Pos; }

private:
    Vec3f m_Pos = {2.0f, 1.0f, 3.0f};
    Mat4x4f m_CameraLookAt;
};

#endif // CAMERA_H