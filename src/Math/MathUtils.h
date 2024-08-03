#ifndef MATHUTIL_H
#define MATHUTIL_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define deg2rad(x) (x * M_PI / 180.0f)
#define rad2deg(x) (x * 180.0f / M_PI)
const double tolerance = 1e-5f;
inline bool equal(double a, double b)
{
    return fabs(a - b) < tolerance;
}
#endif