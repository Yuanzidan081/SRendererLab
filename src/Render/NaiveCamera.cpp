#include "NaiveCamera.h"
NaiveCamera::NaiveCamera(const Vec3 &pos) : m_Pos(pos), m_updateFlag(false)
{
    // m_ViewMatrix = Mat4x4GetLookAt(m_Pos, {0, 0, 0}, LocalUp);
    m_ViewMatrix.SetLookAt(m_Pos, Vec3(0, 0, 0), LocalUp);
}

void NaiveCamera::SetCameraPos(const Vec3 &pos)
{
    m_Pos = {pos.x, pos.y, pos.z};
}

void NaiveCamera::SetCameraPosZ(float z)
{
    m_Pos.z = z;
}

void NaiveCamera::Update()
{
    if (m_updateFlag)
    {
        m_updateFlag = false;
        // m_ViewMatrix = Mat4x4GetLookAt(m_Pos, Vec3(0.0f, 0.0f, 0.0f), LocalUp);
        m_ViewMatrix.SetLookAt(m_Pos, Vec3(0, 0, 0), LocalUp);
    }
}
