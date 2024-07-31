#include "NaiveCamera.h"
NaiveCamera::NaiveCamera(const Vec3f &pos) : m_Pos(pos), m_updateFlag(false)
{
    m_CameraLookAt = Mat4x4GetLookAt(m_Pos, {0, 0, 0}, LocalUp);
}

void NaiveCamera::SetCameraPos(const Vec3f &pos)
{
    m_Pos = {pos.x, pos.y, pos.z};
}

void NaiveCamera::SetCameraPosZ(float z)
{
    m_Pos.z = z;
}

/* void NaiveCamera::SetCameraLookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up)
{
    m_CameraLookAt = Mat4x4GetLookAt(eye, center, LocalUp);
} */

void NaiveCamera::Update()
{
    if (m_updateFlag)
    {
        m_updateFlag = false;
        m_CameraLookAt = Mat4x4GetLookAt(m_Pos, Vec3f(0.0f, 0.0f, 0.0f), LocalUp);
    }
}
