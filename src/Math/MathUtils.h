#ifndef MATHUTIL_H
#define MATHUTIL_H
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const double pi = static_cast<double>(3.1415926535);
inline double deg2rad(double angle)
{
    return angle * pi / 180.0f;
}

inline double rad2deg(double radians)
{
    return radians * 180.0 / pi;
}
const double tolerance = 1e-5f;
inline bool Equal(double a, double b)
{
    return fabs(a - b) < tolerance;
}

template <typename T>
T min(T a, T b)
{
    return a > b ? b : a;
}

template <typename T>
T max(T a, T b)
{
    return a < b ? b : a;
}

// template <>
// Vec3 max(Vec3 a, Vec3 b)
// {
//     return Vec3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
// }
// float max(float a, float b);

inline float Clamp(float val, float min, float max)
{
    return (val > max ? max : (val < min ? min : val));
}

#endif