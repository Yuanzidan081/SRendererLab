#ifndef FPSCAMERA_H
#define FPSCAMERA_H
#include "Math/Vec3.h"
#include "Math/Mat4x4.h"
#include "BasicCamera.h"
class FPSCamera : public BasicCamera
{

public:
    FPSCamera(const Vec3 &pos);
    ~FPSCamera() = default;

    virtual Mat4x4 GetViewMatrix()
    {
        Update();
        return m_viewMatrix;
    }
    virtual Vec3 GetPosition() { return m_Pos; }

    virtual void OnKeyPress(char key);
    virtual void OnWheelMove(double delta);
    virtual void OnMouseMove(double deltaX, double deltaY);

private:
    void Update();
    Vec3 m_Pos;
    Mat4x4 m_viewMatrix;
    bool m_updateFlag;
};

#endif // CAMERA_H