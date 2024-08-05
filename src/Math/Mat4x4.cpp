#include "Mat4x4.h"
#include "string.h"
Mat4x4::Mat4x4(float e00, float e01, float e02, float e03,
               float e10, float e11, float e12, float e13,
               float e20, float e21, float e22, float e23,
               float e30, float e31, float e32, float e33)
{
    entries[0][0] = e00, entries[0][1] = e01, entries[0][2] = e02, entries[0][3] = e03;
    entries[1][0] = e10, entries[1][1] = e11, entries[1][2] = e12, entries[1][3] = e13;
    entries[2][0] = e20, entries[2][1] = e21, entries[2][2] = e22, entries[2][3] = e23;
    entries[3][0] = e30, entries[3][1] = e31, entries[3][2] = e32, entries[3][3] = e33;
}

Mat4x4::Mat4x4(const float *rhs)
{
    memcpy(entries, rhs, 16 * sizeof(float));
}

Mat4x4::Mat4x4(const Mat4x4 &rhs)
{
    memcpy(entries, rhs.entries, 16 * sizeof(float));
}

Vec4 Mat4x4::GetRow(int position) const
{
    switch (position)
    {
    case 0:
        return Vec4(entries[0][0], entries[0][1], entries[0][2], entries[0][3]);
    case 1:
        return Vec4(entries[1][0], entries[1][1], entries[1][2], entries[1][3]);
    case 2:
        return Vec4(entries[2][0], entries[2][1], entries[2][2], entries[2][3]);
    case 3:
        return Vec4(entries[3][0], entries[3][1], entries[3][2], entries[3][3]);
    }
    return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

Vec4 Mat4x4::GetColumn(int position) const
{
    switch (position)
    {
    case 0:
        return Vec4(entries[0][0], entries[1][0], entries[2][0], entries[3][0]);
    case 1:
        return Vec4(entries[0][1], entries[1][1], entries[2][1], entries[3][1]);
    case 2:
        return Vec4(entries[0][2], entries[1][2], entries[2][2], entries[3][2]);
    case 3:
        return Vec4(entries[0][3], entries[1][3], entries[2][3], entries[3][3]);
    }
    return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void Mat4x4::LoadIdentity()
{
    memset(entries, 0, 16 * sizeof(float));
    entries[0][0] = 1.0f;
    entries[1][1] = 1.0f;
    entries[2][2] = 1.0f;
    entries[3][3] = 1.0f;
}

void Mat4x4::LoadZero()
{
    memset(entries, 0, 16 * sizeof(float));
}

Mat4x4 Mat4x4::operator+(const Mat4x4 &rhs) const
{
    return Mat4x4(entries[0][0] + rhs.entries[0][0],
                  entries[0][1] + rhs.entries[0][1],
                  entries[0][2] + rhs.entries[0][2],
                  entries[0][3] + rhs.entries[0][3],
                  entries[1][0] + rhs.entries[1][0],
                  entries[1][1] + rhs.entries[1][1],
                  entries[1][2] + rhs.entries[1][2],
                  entries[1][3] + rhs.entries[1][3],
                  entries[2][0] + rhs.entries[2][0],
                  entries[2][1] + rhs.entries[2][1],
                  entries[2][2] + rhs.entries[2][2],
                  entries[2][3] + rhs.entries[2][3],
                  entries[3][0] + rhs.entries[3][0],
                  entries[3][1] + rhs.entries[3][1],
                  entries[3][2] + rhs.entries[3][2],
                  entries[3][3] + rhs.entries[3][3]);
}

Mat4x4 Mat4x4::operator-(const Mat4x4 &rhs) const
{
    return Mat4x4(entries[0][0] - rhs.entries[0][0],
                  entries[0][1] - rhs.entries[0][1],
                  entries[0][2] - rhs.entries[0][2],
                  entries[0][3] - rhs.entries[0][3],
                  entries[1][0] - rhs.entries[1][0],
                  entries[1][1] - rhs.entries[1][1],
                  entries[1][2] - rhs.entries[1][2],
                  entries[1][3] - rhs.entries[1][3],
                  entries[2][0] - rhs.entries[2][0],
                  entries[2][1] - rhs.entries[2][1],
                  entries[2][2] - rhs.entries[2][2],
                  entries[2][3] - rhs.entries[2][3],
                  entries[3][0] - rhs.entries[3][0],
                  entries[3][1] - rhs.entries[3][1],
                  entries[3][2] - rhs.entries[3][2],
                  entries[3][3] - rhs.entries[3][3]);
}

Mat4x4 Mat4x4::operator*(const Mat4x4 &rhs) const
{
    return Mat4x4(entries[0][0] * rhs.entries[0][0] + entries[0][1] * rhs.entries[1][0] + entries[0][2] * rhs.entries[2][0] + entries[0][3] * rhs.entries[3][0],
                  entries[0][0] * rhs.entries[0][1] + entries[0][1] * rhs.entries[1][1] + entries[0][2] * rhs.entries[2][1] + entries[0][3] * rhs.entries[3][1],
                  entries[0][0] * rhs.entries[0][2] + entries[0][1] * rhs.entries[1][2] + entries[0][2] * rhs.entries[2][2] + entries[0][3] * rhs.entries[3][2],
                  entries[0][0] * rhs.entries[0][3] + entries[0][1] * rhs.entries[1][3] + entries[0][2] * rhs.entries[2][3] + entries[0][3] * rhs.entries[3][3],
                  entries[1][0] * rhs.entries[0][0] + entries[1][1] * rhs.entries[1][0] + entries[1][2] * rhs.entries[2][0] + entries[1][3] * rhs.entries[3][0],
                  entries[1][0] * rhs.entries[0][1] + entries[1][1] * rhs.entries[1][1] + entries[1][2] * rhs.entries[2][1] + entries[1][3] * rhs.entries[3][1],
                  entries[1][0] * rhs.entries[0][2] + entries[1][1] * rhs.entries[1][2] + entries[1][2] * rhs.entries[2][2] + entries[1][3] * rhs.entries[3][2],
                  entries[1][0] * rhs.entries[0][3] + entries[1][1] * rhs.entries[1][3] + entries[1][2] * rhs.entries[2][3] + entries[1][3] * rhs.entries[3][3],
                  entries[2][0] * rhs.entries[0][0] + entries[2][1] * rhs.entries[1][0] + entries[2][2] * rhs.entries[2][0] + entries[2][3] * rhs.entries[3][0],
                  entries[2][0] * rhs.entries[0][1] + entries[2][1] * rhs.entries[1][1] + entries[2][2] * rhs.entries[2][1] + entries[2][3] * rhs.entries[3][1],
                  entries[2][0] * rhs.entries[0][2] + entries[2][1] * rhs.entries[1][2] + entries[2][2] * rhs.entries[2][2] + entries[2][3] * rhs.entries[3][2],
                  entries[2][0] * rhs.entries[0][3] + entries[2][1] * rhs.entries[1][3] + entries[2][2] * rhs.entries[2][3] + entries[2][3] * rhs.entries[3][3],
                  entries[3][0] * rhs.entries[0][0] + entries[3][1] * rhs.entries[1][0] + entries[3][2] * rhs.entries[2][0] + entries[3][3] * rhs.entries[3][0],
                  entries[3][0] * rhs.entries[0][1] + entries[3][1] * rhs.entries[1][1] + entries[3][2] * rhs.entries[2][1] + entries[3][3] * rhs.entries[3][1],
                  entries[3][0] * rhs.entries[0][2] + entries[3][1] * rhs.entries[1][2] + entries[3][2] * rhs.entries[2][2] + entries[3][3] * rhs.entries[3][2],
                  entries[3][0] * rhs.entries[0][3] + entries[3][1] * rhs.entries[1][3] + entries[3][2] * rhs.entries[2][3] + entries[3][3] * rhs.entries[3][3]);
}

Mat4x4 Mat4x4::operator*(const float rhs) const
{
    return Mat4x4(entries[0][0] * rhs,
                  entries[0][1] * rhs,
                  entries[0][2] * rhs,
                  entries[0][3] * rhs,
                  entries[1][0] * rhs,
                  entries[1][1] * rhs,
                  entries[1][2] * rhs,
                  entries[1][3] * rhs,
                  entries[2][0] * rhs,
                  entries[2][1] * rhs,
                  entries[2][2] * rhs,
                  entries[2][3] * rhs,
                  entries[3][0] * rhs,
                  entries[3][1] * rhs,
                  entries[3][2] * rhs,
                  entries[3][3] * rhs);
}

Mat4x4 Mat4x4::operator/(const float rhs) const
{
    if (Equal(rhs, 0.0f) || Equal(rhs, 1.0f))
        return (*this);
    float temp = 1 / rhs;
    return (*this) * temp;
}

bool Mat4x4::operator==(const Mat4x4 &rhs) const
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (!Equal(entries[i][j], rhs.entries[i][j]))
                return false;
        }
    }
    return true;
}

bool Mat4x4::operator!=(const Mat4x4 &rhs) const
{
    return !((*this) == rhs);
}

void Mat4x4::operator+=(const Mat4x4 &rhs)
{
    (*this) = (*this) + rhs;
}

void Mat4x4::operator-=(const Mat4x4 &rhs)
{
    (*this) = (*this) - rhs;
}

void Mat4x4::operator*=(const Mat4x4 &rhs)
{
    (*this) = (*this) * rhs;
}

void Mat4x4::operator*=(const float rhs)
{
    (*this) = (*this) * rhs;
}

void Mat4x4::operator/=(const float rhs)
{
    (*this) = (*this) / rhs;
}

Mat4x4 Mat4x4::operator-() const
{
    Mat4x4 result(*this);
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; ++j)
            result.entries[i][j] = -result.entries[i][j];
    }

    return result;
}

Vec4 Mat4x4::operator*(const Vec4 rhs) const
{
    return Vec4(
        entries[0][0] * rhs.x + entries[0][1] * rhs.y + entries[0][2] * rhs.z + entries[0][3] * rhs.w,
        entries[1][0] * rhs.x + entries[1][1] * rhs.y + entries[1][2] * rhs.z + entries[1][3] * rhs.w,
        entries[2][0] * rhs.x + entries[2][1] * rhs.y + entries[2][2] * rhs.z + entries[2][3] * rhs.w,
        entries[3][0] * rhs.x + entries[3][1] * rhs.y + entries[3][2] * rhs.z + entries[3][3] * rhs.w);
}

void Mat4x4::Inverted()
{
    *this = GetInverse();
}

Mat4x4 Mat4x4::GetInverse() const
{
    Mat4x4 result = GetInverseTranspose();
    result.Transpose();
    return result;
}

void Mat4x4::Transpose()
{
    *this = GetTranspose();
}

Mat4x4 Mat4x4::GetTranspose() const
{
    return Mat4x4(entries[0][0], entries[1][0], entries[2][0], entries[3][0],
                  entries[0][1], entries[1][1], entries[2][1], entries[3][1],
                  entries[0][2], entries[1][2], entries[2][2], entries[3][2],
                  entries[0][3], entries[1][3], entries[2][3], entries[3][3]);
}

void Mat4x4::InvertTranspose()
{
    *this = GetInverseTranspose();
}

Mat4x4 Mat4x4::GetInverseTranspose() const
{
    Mat4x4 result;
    float tmp[12];
    float det;

    // calculate pairs for first 8 elements (cofactors)
    tmp[0] = entries[2][2] * entries[3][3];
    tmp[1] = entries[3][2] * entries[2][3];
    tmp[2] = entries[1][2] * entries[3][3];
    tmp[3] = entries[3][2] * entries[1][3];
    tmp[4] = entries[1][2] * entries[2][3];
    tmp[5] = entries[2][2] * entries[1][3];
    tmp[6] = entries[0][2] * entries[3][3];
    tmp[7] = entries[3][2] * entries[0][3];
    tmp[8] = entries[0][2] * entries[2][3];
    tmp[9] = entries[2][2] * entries[0][3];
    tmp[10] = entries[0][2] * entries[1][3];
    tmp[11] = entries[1][2] * entries[0][3];

    // calculate first 8 elements (cofactors)
    result.entries[0][0] = tmp[0] * entries[1][1] + tmp[3] * entries[2][1] + tmp[4] * entries[3][1] - tmp[1] * entries[1][1] - tmp[2] * entries[2][1] - tmp[5] * entries[3][1];

    result.entries[1][0] = tmp[1] * entries[0][1] + tmp[6] * entries[2][1] + tmp[9] * entries[3][1] - tmp[0] * entries[0][1] - tmp[7] * entries[2][1] - tmp[8] * entries[3][1];

    result.entries[2][0] = tmp[2] * entries[0][1] + tmp[7] * entries[1][1] + tmp[10] * entries[3][1] - tmp[3] * entries[0][1] - tmp[6] * entries[1][1] - tmp[11] * entries[3][1];

    result.entries[3][0] = tmp[5] * entries[0][1] + tmp[8] * entries[1][1] + tmp[11] * entries[2][1] - tmp[4] * entries[0][1] - tmp[9] * entries[1][1] - tmp[10] * entries[2][1];

    result.entries[0][1] = tmp[1] * entries[1][0] + tmp[2] * entries[2][0] + tmp[5] * entries[3][0] - tmp[0] * entries[1][0] - tmp[3] * entries[2][0] - tmp[4] * entries[3][0];

    result.entries[1][1] = tmp[0] * entries[0][0] + tmp[7] * entries[2][0] + tmp[8] * entries[3][0] - tmp[1] * entries[0][0] - tmp[6] * entries[2][0] - tmp[9] * entries[3][0];

    result.entries[2][1] = tmp[3] * entries[0][0] + tmp[6] * entries[1][0] + tmp[11] * entries[3][0] - tmp[2] * entries[0][0] - tmp[7] * entries[1][0] - tmp[10] * entries[3][0];

    result.entries[3][1] = tmp[4] * entries[0][0] + tmp[9] * entries[1][0] + tmp[10] * entries[2][0] - tmp[5] * entries[0][0] - tmp[8] * entries[1][0] - tmp[11] * entries[2][0];

    // calculate pairs for second 8 elements (cofactors)
    tmp[0] = entries[2][0] * entries[3][1];
    tmp[1] = entries[3][0] * entries[2][1];
    tmp[2] = entries[1][0] * entries[3][1];
    tmp[3] = entries[3][0] * entries[1][1];
    tmp[4] = entries[1][0] * entries[2][1];
    tmp[5] = entries[2][0] * entries[1][1];
    tmp[6] = entries[0][0] * entries[3][1];
    tmp[7] = entries[3][0] * entries[0][1];
    tmp[8] = entries[0][0] * entries[2][1];
    tmp[9] = entries[2][0] * entries[0][1];
    tmp[10] = entries[0][0] * entries[1][1];
    tmp[11] = entries[1][0] * entries[0][1];

    // calculate second 8 elements (cofactors)
    result.entries[0][2] = tmp[0] * entries[1][3] + tmp[3] * entries[2][3] + tmp[4] * entries[3][3] - tmp[1] * entries[1][3] - tmp[2] * entries[2][3] - tmp[5] * entries[3][3];

    result.entries[1][2] = tmp[1] * entries[0][3] + tmp[6] * entries[2][3] + tmp[9] * entries[3][3] - tmp[0] * entries[0][3] - tmp[7] * entries[2][3] - tmp[8] * entries[3][3];

    result.entries[2][2] = tmp[2] * entries[0][3] + tmp[7] * entries[1][3] + tmp[10] * entries[3][3] - tmp[3] * entries[0][3] - tmp[6] * entries[1][3] - tmp[11] * entries[3][3];

    result.entries[3][2] = tmp[5] * entries[0][3] + tmp[8] * entries[1][3] + tmp[11] * entries[2][3] - tmp[4] * entries[0][3] - tmp[9] * entries[1][3] - tmp[10] * entries[2][3];

    result.entries[0][3] = tmp[2] * entries[2][2] + tmp[5] * entries[3][2] + tmp[1] * entries[1][2] - tmp[4] * entries[3][2] - tmp[0] * entries[1][2] - tmp[3] * entries[2][2];

    result.entries[1][3] = tmp[8] * entries[3][2] + tmp[0] * entries[0][2] + tmp[7] * entries[2][2] - tmp[6] * entries[2][2] - tmp[9] * entries[3][2] - tmp[1] * entries[0][2];

    result.entries[2][3] = tmp[6] * entries[1][2] + tmp[11] * entries[3][2] + tmp[3] * entries[0][2] - tmp[10] * entries[3][2] - tmp[2] * entries[0][2] - tmp[7] * entries[1][2];

    result.entries[3][3] = tmp[10] * entries[2][2] + tmp[4] * entries[0][2] + tmp[9] * entries[1][2] - tmp[8] * entries[1][2] - tmp[11] * entries[2][2] - tmp[5] * entries[0][2];

    // calculate determinant
    det = entries[0][0] * result.entries[0][0] + entries[1][0] * result.entries[1][0] + entries[2][0] * result.entries[2][0] + entries[3][0] * result.entries[3][0];

    if (det == 0.0f)
        return Mat4x4();

    result = result / det;
    return result;
}

void Mat4x4::SetTranslation(const Vec3 &translation)
{
    LoadIdentity();
    entries[0][3] = translation.x;
    entries[1][3] = translation.y;
    entries[2][3] = translation.z;
}

void Mat4x4::SetScale(const Vec3 &scaleFactor)
{
    LoadIdentity();
    entries[0][0] = scaleFactor.x;
    entries[1][1] = scaleFactor.y;
    entries[2][2] = scaleFactor.z;
}

void Mat4x4::SetRotationAxis(const double angle, const Vec3 &axis)
{
    Vec3 u = axis.GetNormalize();

    float sinAngle = static_cast<float>(sin(M_PI * angle / 180));
    float cosAngle = static_cast<float>(cos(M_PI * angle / 180));
    float oneMinusCosAngle = 1.0f - cosAngle;

    LoadIdentity();

    entries[0][0] = (u.x) * (u.x) + cosAngle * (1 - (u.x) * (u.x));
    entries[0][1] = (u.x) * (u.y) * (oneMinusCosAngle)-sinAngle * u.z;
    entries[0][2] = (u.x) * (u.z) * (oneMinusCosAngle) + sinAngle * u.y;

    entries[1][0] = (u.x) * (u.y) * (oneMinusCosAngle) + sinAngle * u.z;
    entries[1][1] = (u.y) * (u.y) + cosAngle * (1 - (u.y) * (u.y));
    entries[1][2] = (u.y) * (u.z) * (oneMinusCosAngle)-sinAngle * u.x;

    entries[2][0] = (u.x) * (u.z) * (oneMinusCosAngle)-sinAngle * u.y;
    entries[2][1] = (u.y) * (u.z) * (oneMinusCosAngle) + sinAngle * u.x;
    entries[2][2] = (u.z) * (u.z) + cosAngle * (1 - (u.z) * (u.z));
}

void Mat4x4::SetRotationX(const double angle)
{
    LoadIdentity();
    entries[1][1] = cos(M_PI * angle / 180);
    entries[1][2] = -sin(M_PI * angle / 180);
    entries[2][1] = -entries[1][2];
    entries[2][2] = entries[1][1];
}

void Mat4x4::SetRotationY(const double angle)
{
    LoadIdentity();
    entries[0][0] = cos(M_PI * angle / 180);
    entries[0][2] = sin(M_PI * angle / 180);
    entries[2][0] = -entries[0][2];
    entries[2][2] = entries[0][0];
}

void Mat4x4::SetRotationZ(const double angle)
{
    LoadIdentity();
    entries[0][0] = cos(M_PI * angle / 180);
    entries[0][1] = -sin(M_PI * angle / 180);
    entries[1][0] = -entries[0][1];
    entries[1][1] = entries[0][0];
}

void Mat4x4::SetRotationEuler(const double angleX, const double angleY, const double angleZ)
{
    // pitch yaw roll
    // take the order from right to left Rz * Ry * Rx
    LoadIdentity();
    double cr = cos(M_PI * angleX / 180);
    double sr = sin(M_PI * angleX / 180);
    double cp = cos(M_PI * angleY / 180);
    double sp = sin(M_PI * angleY / 180);
    double cy = cos(M_PI * angleZ / 180);
    double sy = sin(M_PI * angleZ / 180);

    entries[0][0] = static_cast<float>(cp * cy);
    entries[1][0] = static_cast<float>(cp * sy);
    entries[2][0] = static_cast<float>(-sp);

    double srsp = sr * sp;
    double crsp = cr * sp;

    entries[0][1] = static_cast<float>(srsp * cy - cr * sy);
    entries[1][1] = static_cast<float>(srsp * sy + cr * cy);
    entries[2][1] = static_cast<float>(sr * cp);
    entries[0][2] = static_cast<float>(crsp * cy + sr * sy);
    entries[1][2] = static_cast<float>(crsp * sy - sr * cy);
    entries[2][2] = static_cast<float>(cr * cp);
}

void Mat4x4::SetPerspective(float fovy, float aspect, float near, float far)
{
    LoadZero();
    // convert fov from degrees to radians
    float rFovy = fovy * M_PI / 180;
    const float tanHalfFovy = tanf(static_cast<float>(rFovy * 0.5f));
    entries[0][0] = 1.0f / (aspect * tanHalfFovy);
    entries[1][1] = 1.0f / (tanHalfFovy);
    entries[2][2] = -(far + near) / (far - near);
    entries[3][2] = -1.0f;
    entries[2][3] = (-2.0f * near * far) / (far - near);
}

void Mat4x4::SetOrtho(float left, float right, float bottom, float top, float near, float far)
{
    LoadIdentity();
    entries[0][0] = 2.0f / (right - left);
    entries[1][1] = 2.0f / (top - bottom);
    entries[2][2] = -2.0f / (far - near);
    entries[0][3] = -(right + left) / (right - left);
    entries[1][3] = -(top + bottom) / (top - bottom);
    entries[2][3] = -(far + near) / (far - near);
}

void Mat4x4::SetLookAt(Vec3 cameraPos, Vec3 target, Vec3 worldUp)
{
    Vec3 zAxis = cameraPos - target;
    zAxis.Normalize();
    Vec3 xAxis = worldUp.GetCrossProduct(zAxis);
    xAxis.Normalize();
    Vec3 yAxis = zAxis.GetCrossProduct(xAxis);
    yAxis.Normalize();

    LoadIdentity();
    entries[0][0] = xAxis.x;
    entries[0][1] = xAxis.y;
    entries[0][2] = xAxis.z;

    entries[1][0] = yAxis.x;
    entries[1][1] = yAxis.y;
    entries[1][2] = yAxis.z;

    entries[2][0] = zAxis.x;
    entries[2][1] = zAxis.y;
    entries[2][2] = zAxis.z;

    entries[0][3] = -(xAxis.GetDotProduct(cameraPos));
    entries[1][3] = -(yAxis.GetDotProduct(cameraPos));
    entries[2][3] = -(zAxis.GetDotProduct(cameraPos));
}

void Mat4x4::SetViewPort(int left, int top, int width, int height)
{
    LoadIdentity();
    entries[0][0] = static_cast<float>(width) / 2.0f;
    entries[1][1] = -static_cast<float>(height) / 2.0f;
    entries[0][3] = static_cast<float>(left) + static_cast<float>(width) / 2.0f;
    entries[1][3] = static_cast<float>(top) + static_cast<float>(height) / 2.0f;
}

std::ostream &operator<<(std::ostream &os, Mat4x4 &m)
{
    os << "[";
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            os << m.entries[i][j] << " ";
        }
        if (i != 3)
            os << std::endl;
    }
    os << "]" << std::endl;

    return os;
}
