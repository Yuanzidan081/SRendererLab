#include "Camera.h"

Camera::Camera(Vec3f &pos) : m_Pos(pos)
{
}

void Camera::SetCameraPos(float x, float y, float z)
{
    m_Pos = {x, y, z};
}

void Camera::SetCameraPosZ(float z)
{
    m_Pos.z = z;
}
