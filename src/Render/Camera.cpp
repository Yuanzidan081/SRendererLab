#include "Camera.h"
Camera::Camera(const Vec3f &pos) : m_Pos(pos)
{
    m_CameraLookAt = Mat4x4GetLookAt(m_Pos, {0, 0, 0}, {0, 1, 0});
}

void Camera::SetCameraPos(const Vec3f &pos)
{
    m_Pos = {pos.x, pos.y, pos.z};
}

void Camera::SetCameraPosZ(float z)
{
    m_Pos.z = z;
}

void Camera::SetCameraLookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up)
{
    m_CameraLookAt = Mat4x4GetLookAt(eye, center, up);
}
