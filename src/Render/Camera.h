#ifndef CAMERA_H
#define CAMERA_H
#include "Math/Vec.h"
class Camera
{

public:
    Camera(Vec3f &pos = Vec3f(0.0f, 0.0f, 0.0f));
    ~Camera() = default;
    void SetCameraPos(float x, float y, float z);
    void SetCameraPosZ(float z);
    Vec3f &GetCameraPos() { return m_Pos; }

private:
    Vec3f m_Pos;
};

#endif // CAMERA_H