#ifndef FPSCAMERA_H
#define FPSCAMERA_H
#include "Math/Vec3.h"
#include "Math/Mat4x4.h"
#include "BasicCamera.h"
#include "Math/Quaternion.h"
class QuaternionFPSCamera : public BasicCamera
{

public:
    QuaternionFPSCamera(const Vec3 &pos);
    ~QuaternionFPSCamera() = default;

    virtual Mat4x4 GetViewMatrix();

    virtual Vec3 GetPosition() { return m_translation; }

    void Translate(const Vec3 &dt);
    void Rotate(const Vec3 &axis, float angle);

    void SetTranslation(const Vec3 &t);
    void SetRotation(const Quaternion &r);

    Vec3 Forward() const;
    Vec3 Up() const;
    Vec3 Right() const;

private:
    Mat4x4 m_viewMatrix;
    bool m_updateFlag;
    Vec3 m_translation;
    Quaternion m_rotation;
};

class EulerFPSCamera : public BasicCamera
{

public:
    EulerFPSCamera(const Vec3 &pos, Vec3 up = Vec3(0.0f, 1.0f, 0.0f),
                   Vec3 lookat = Vec3(0.0f, 0.0f, 0.0f),
                   float fov = 45.0f,
                   int w = 500,
                   int h = 500,
                   float near = 0.01f,
                   float far = 100.0f);
    ~EulerFPSCamera() = default;

    virtual Mat4x4 GetViewMatrix();
    Mat4x4 &GetPerspectiveMatrix();
    void UpdateFov();
    virtual Vec3 GetPosition() { return m_position; }

    // virtual void OnKeyPress(int key);
    // virtual void OnWheelMove(double delta);

    void MoveForward(float distance);
    void MoveRight(float distance);
    void MoveUp(float distance);

    void Translate(const Vec3 &dt);
    void RotatePitch(float angle);
    void RotateYaw(float angle);

    void Zoom(float delta);

    void UpdateCameraVectors();

    float m_pitch;
    float m_yaw;

private:
    // void Update();
    Vec3 m_position;
    Vec3 m_front;
    Vec3 m_up;
    Vec3 m_right;
    Vec3 m_worldUp;
    float m_fov;
    float m_aspect;

    float m_near;
    float m_far;

    Mat4x4 m_viewMatrix;
    Mat4x4 m_perspectiveMatrix;
    bool m_updateViewFlag, m_updatePerspectiveFlag;
};
#endif // CAMERA_H