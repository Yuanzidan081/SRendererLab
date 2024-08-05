#ifndef NaiveCAMERA_H
#define NaiveCAMERA_H
#include "Math/Vec3.h"
#include "Math/Mat4x4.h"
#include "BasicCamera.h"
class NaiveCamera : public BasicCamera
{

public:
    NaiveCamera(const Vec3 &pos);
    ~NaiveCamera() = default;
    void SetCameraPos(const Vec3 &pos);
    void SetCameraPosZ(float z);

    virtual Mat4x4 GetViewMatrix()
    {
        Update();
        return m_ViewMatrix;
    }
    virtual Vec3 GetPosition() { return m_Pos; }

private:
    void Update();
    Vec3 m_Pos;
    Mat4x4 m_ViewMatrix;
    bool m_updateFlag;
};

#endif // CAMERA_H