#include "FPSCamera.h"
#include "Algorithm/Clip.h"
QuaternionFPSCamera::QuaternionFPSCamera(const Vec3 &pos) : m_translation(pos), m_updateFlag(true) {}

Mat4x4 QuaternionFPSCamera::GetViewMatrix()
{
    if (m_updateFlag)
    {
        m_updateFlag = false;
        m_viewMatrix.LoadIdentity();
        m_viewMatrix = m_rotation.Conjugate().ToMatrix();
        Mat4x4 trans;
        trans.SetTranslation(-m_translation);
        m_viewMatrix *= trans;
    }
    return m_viewMatrix;
}

void QuaternionFPSCamera::Translate(const Vec3 &dt)
{
    m_updateFlag = true;
    m_translation += dt;
}

void QuaternionFPSCamera::Rotate(const Vec3 &axis, float angle)
{
    m_updateFlag = true;
    Quaternion newRot;
    newRot.SetRotationAxis(axis, angle);
    m_rotation = newRot * m_rotation;
}

void QuaternionFPSCamera::SetTranslation(const Vec3 &t)
{
    m_updateFlag = true;
    m_translation = t;
}

void QuaternionFPSCamera::SetRotation(const Quaternion &r)
{
    m_updateFlag = true;
    m_rotation = r;
}

Vec3 QuaternionFPSCamera::Forward() const
{
    return m_rotation * LocalForward;
}

Vec3 QuaternionFPSCamera::Up() const
{
    return m_rotation * LocalUp;
}

Vec3 QuaternionFPSCamera::Right() const
{
    return m_rotation * LocalRight;
}

// void QuaternionFPSCamera::Update()
// {
//     if (m_updateFlag)
//     {
//         m_updateFlag = false;
//         m_viewMatrix.SetLookAt(m_translation, Vec3(0, 0, 0), LocalUp);
//     }
// }

/* ----------------------- EulerFPSCamera ---------------------------*/
EulerFPSCamera::EulerFPSCamera(const Vec3 &pos, Vec3 up, Vec3 lookat, float fov, int w, int h, float near, float far)
    : m_position(pos), m_worldUp(up), m_fov(fov), m_aspect((float)w / h), m_pitch(0), m_yaw(0),
      m_updateViewFlag(true), m_updatePerspectiveFlag(true), m_near(near), m_far(far)
{

    m_front = (m_position - lookat).GetNormalize();
    m_right = m_worldUp.GetCrossProduct(m_front).GetNormalize();
    m_up = m_front.GetCrossProduct(m_right).GetNormalize();
    Vec3 WorldFront(0, 0, 1);
    Vec3 FrontXZ = (Vec3(m_front.x, 0, m_front.z)).GetNormalize();
    m_pitch = rad2deg(atan2(m_front.y, sqrt(m_front.z * m_front.z + m_front.x * m_front.x)));
    m_yaw = rad2deg(atan2(m_front.z, m_front.x));

    Clip::s_near = m_near;
    Clip::s_far = m_far;

    // std::cout << m_pitch << "," << m_yaw << std::endl;
}

Mat4x4 EulerFPSCamera::GetViewMatrix()
{
    if (m_updateViewFlag)
    {
        m_updateViewFlag = false;
        UpdateCameraVectors();
        m_viewMatrix.SetLookAt(m_position, m_front, m_right, m_up);
        // std::cout << m_viewMatrix << std::endl;
    }
    return m_viewMatrix;
}

Mat4x4 &EulerFPSCamera::GetPerspectiveMatrix()
{
    if (m_updatePerspectiveFlag)
    {
        m_updatePerspectiveFlag = false;
        m_perspectiveMatrix.SetPerspective(m_fov, m_aspect, 0.1f, 100);
    }
    return m_perspectiveMatrix;
}

void EulerFPSCamera::MoveForward(float distance)
{
    m_position += m_front * distance;
    m_updateViewFlag = true;
}

void EulerFPSCamera::MoveRight(float distance)
{
    m_position += m_right * distance;
    m_updateViewFlag = true;
}

void EulerFPSCamera::MoveUp(float distance)
{
    m_position += m_up * distance;
    m_updateViewFlag = true;
}

void EulerFPSCamera::Translate(const Vec3 &dt)
{
    m_position += dt;
    m_updateViewFlag = true;
}

void EulerFPSCamera::RotatePitch(float angle)
{

    m_pitch += angle;
    if (m_pitch > 89.0)
        m_pitch = 89.0;
    if (m_pitch < -89.0)
        m_pitch = -89.0;
    m_updateViewFlag = true;
    // UpdateCameraVectors();
}

void EulerFPSCamera::RotateYaw(float angle)
{

    m_yaw += angle;
    if (m_yaw > 360)
        m_yaw = 0;
    if (m_yaw < 0)
        m_yaw = 360;
    m_updateViewFlag = true;
    // UpdateCameraVectors();
}

void EulerFPSCamera::Zoom(float delta)
{
    m_updatePerspectiveFlag = true;
    m_fov += delta;
    if (m_fov < 1.0f)
        m_fov = 1.0f;
    if (m_fov > 90.0f)
        m_fov = 90.0f;
}

void EulerFPSCamera::UpdateCameraVectors()
{

    Vec3 front;
    front.x = cos(deg2rad(m_yaw)) * cos(deg2rad(m_pitch));
    front.y = sin(deg2rad(m_pitch));
    front.z = sin(deg2rad(m_yaw)) * cos(deg2rad(m_pitch));
    m_front = front.GetNormalize();
    // also re-calculate the Right and Up vector
    m_right = m_worldUp.GetCrossProduct(m_front).GetNormalize();
    m_up = m_front.GetCrossProduct(m_right).GetNormalize();
}
