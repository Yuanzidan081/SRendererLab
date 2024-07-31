#ifndef NaiveCAMERA_H
#define NaiveCAMERA_H
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "BasicCamera.h"
class NaiveCamera : public BasicCamera
{

public:
    NaiveCamera(const Vec3f &pos);
    ~NaiveCamera() = default;
    void SetCameraPos(const Vec3f &pos);
    void SetCameraPosZ(float z);

    // void SetCameraLookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up);
    //  Mat4x4f &GetCameraLookAt() { return m_CameraLookAt; }
    virtual Mat4x4f GetViewMatrix()
    {
        Update();
        return m_CameraLookAt;
    }
    virtual Vec3f GetPosition() { return m_Pos; }

private:
    void Update();
    Vec3f m_Pos;
    Mat4x4f m_CameraLookAt;
    bool m_updateFlag;
};

#endif // CAMERA_H