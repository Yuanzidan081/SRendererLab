#include "FPSCamera.h"
#include "Core/KeyCode.h"
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

void QuaternionFPSCamera::OnKeyPress(int key)
{
    switch (key)
    {
    case SKey_W:
        this->Translate(Forward() * 0.2f);
        break;
    case SKey_S:
        this->Translate(-Forward() * 0.2f);
        break;
    case SKey_A:
        this->Translate(-Right() * 0.2f);
        break;
    case SKey_D:
        this->Translate(+Right() * 0.2f);
        break;
    case SKey_Q:
        this->Translate(Up() * 0.2f);
        break;
    case SKey_E:
        this->Translate(-Up() * 0.2f);
        break;
    case SKey_Down:
        this->Rotate(LocalRight, 1.0f);
        break;
    case SKey_Up:
        this->Rotate(LocalRight, -1.0f);
        break;
    case SKey_Left:
        this->Rotate(LocalUp, -1.0f);
        break;
    case SKey_Right:
        this->Rotate(LocalUp, 1.0f);
        break;

    default:
        break;
    }
}

void QuaternionFPSCamera::OnWheelMove(double delta)
{
}

void QuaternionFPSCamera::OnMouseMove(double deltaX, double deltaY)
{
    double speed = 0.1f;
    deltaX *= speed;
    deltaY *= speed;
    this->Rotate(LocalUp, -deltaX);
    this->Rotate(Right(), -deltaY);
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
EulerFPSCamera::EulerFPSCamera(const Vec3 &pos, Vec3 up, Vec3 lookat, float fov, int w, int h)
    : m_position(pos), m_worldUp(up), m_fov(fov), m_aspect((float)w / h), m_pitch(0), m_yaw(0),
      m_updateViewFlag(true), m_updatePerspectiveFlag(true)
{

    m_front = (m_position - lookat).GetNormalize();
    m_right = m_worldUp.GetCrossProduct(m_front).GetNormalize();
    m_up = m_front.GetCrossProduct(m_right).GetNormalize();
    Vec3 WorldFront(0, 0, 1);
    Vec3 FrontXZ = (Vec3(m_front.x, 0, m_front.z)).GetNormalize();
    m_pitch = rad2deg(atan2(m_front.y, sqrt(m_front.z * m_front.z + m_front.x * m_front.x)));
    m_yaw = rad2deg(atan2(m_front.z, m_front.x));
    // std::cout << m_pitch << "," << m_yaw << std::endl;
}

Mat4x4 EulerFPSCamera::GetViewMatrix()
{
    if (m_updateViewFlag)
    {
        m_updateViewFlag = false;
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

void EulerFPSCamera::OnKeyPress(int key)
{
    switch (key)
    {
    case SKey_W:
        this->Translate(-m_front * 0.2f);
        break;
    case SKey_S:
        this->Translate(m_front * 0.2f);
        break;
    case SKey_A:
        this->Translate(-m_right * 0.2f);
        break;
    case SKey_D:
        this->Translate(+m_right * 0.2f);
        break;
    case SKey_Q:
        this->Translate(m_up * 0.2f);
        break;
    case SKey_E:
        this->Translate(-m_up * 0.2f);
        break;
    case SKey_Down:
        this->RotatePitch(1.0f);
        break;
    case SKey_Up:
        this->RotatePitch(-1.0f);
        break;
    case SKey_Left:
        this->RotateYaw(-1.0f);
        break;
    case SKey_Right:
        this->RotateYaw(1.0f);
        break;
    default:
        break;
    }
}

void EulerFPSCamera::OnWheelMove(double delta)
{
    m_fov -= 0.5f;
    Zoom(m_fov);
}

void EulerFPSCamera::OnMouseMove(double deltaX, double deltaY)
{
    /* m_yaw += deltaX * 0.1f;
    m_pitch += deltaY * 0.1f;
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f; */
    RotateYaw(deltaX * 0.1f);
    RotatePitch(deltaY * 0.1f);
    UpdateCameraVectors();
}

void EulerFPSCamera::Translate(const Vec3 &dt)
{
    m_updateViewFlag = true;
    m_position += dt;
}

void EulerFPSCamera::RotatePitch(float angle)
{
    m_updateViewFlag = true;
    m_pitch += angle;
    if (m_pitch > 89.0)
        m_pitch = 89.0;
    if (m_pitch < -89.0)
        m_pitch = -89.0;
    UpdateCameraVectors();
}

void EulerFPSCamera::RotateYaw(float angle)
{
    m_updateViewFlag = true;
    m_yaw += angle;
    if (m_yaw > 360)
        m_yaw = 0;
    if (m_yaw < 0)
        m_yaw = 360;
    UpdateCameraVectors();
}

void EulerFPSCamera::Zoom(float fov)
{
    m_updatePerspectiveFlag = true;
    if (m_fov < 1.0f)
        m_fov = 1.0f;
    if (m_fov > 45.0f)
        m_fov = 45.0f;
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
