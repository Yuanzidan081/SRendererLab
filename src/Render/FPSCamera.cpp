#include "FPSCamera.h"
FPSCamera::FPSCamera(const Vec3 &pos) : m_Pos(pos), m_updateFlag(false)
{
    // m_ViewMatrix = Mat4x4GetLookAt(m_Pos, {0, 0, 0}, LocalUp);
    m_viewMatrix.SetLookAt(m_Pos, Vec3(0, 0, 0), LocalUp);
}

void FPSCamera::OnKeyPress(char key)
{
}

void FPSCamera::OnWheelMove(double delta)
{
}

void FPSCamera::OnMouseMove(double deltaX, double deltaY)
{
}

void FPSCamera::Update()
{
    if (m_updateFlag)
    {
        m_updateFlag = false;
        m_viewMatrix.SetLookAt(m_Pos, Vec3(0, 0, 0), LocalUp);
    }
}
