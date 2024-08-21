#include "Mat3x3.h"
#include "string.h"
Mat3x3::Mat3x3(float e00, float e01, float e02,
               float e10, float e11, float e12,
               float e20, float e21, float e22)
{
    entries[0][0] = e00, entries[0][1] = e01, entries[0][2] = e02;
    entries[1][0] = e10, entries[1][1] = e11, entries[1][2] = e12;
    entries[2][0] = e20, entries[2][1] = e21, entries[2][2] = e22;
}

Mat3x3::Mat3x3(const float *rhs)
{
    memcpy(entries, rhs, 9 * sizeof(float));
}

Mat3x3::Mat3x3(const Mat3x3 &rhs)
{
    memcpy(entries, rhs.entries, 9 * sizeof(float));
}

Vec4 Mat3x3::GetRow(int position) const
{
    switch (position)
    {
    case 0:
        return Vec3(entries[0][0], entries[0][1], entries[0][2]);
    case 1:
        return Vec3(entries[1][0], entries[1][1], entries[1][2]);
    case 2:
        return Vec3(entries[2][0], entries[2][1], entries[2][2]);
    }
    return Vec3(0.0f, 0.0f, 0.0f);
}

Vec4 Mat3x3::GetColumn(int position) const
{
    switch (position)
    {
    case 0:
        return Vec3(entries[0][0], entries[1][0], entries[2][0]);
    case 1:
        return Vec3(entries[0][1], entries[1][1], entries[2][1]);
    case 2:
        return Vec3(entries[0][2], entries[1][2], entries[2][2]);
    }
    return Vec3(0.0f, 0.0f, 0.0f);
}

void Mat3x3::LoadIdentity()
{
    memset(entries, 0, 9 * sizeof(float));
    entries[0][0] = 1.0f;
    entries[1][1] = 1.0f;
    entries[2][2] = 1.0f;
}

void Mat3x3::LoadZero()
{
    memset(entries, 0, 9 * sizeof(float));
}

Mat3x3 Mat3x3::operator+(const Mat3x3 &rhs) const
{
    return Mat3x3(entries[0][0] + rhs.entries[0][0],
                  entries[0][1] + rhs.entries[0][1],
                  entries[0][2] + rhs.entries[0][2],
                  entries[1][0] + rhs.entries[1][0],
                  entries[1][1] + rhs.entries[1][1],
                  entries[1][2] + rhs.entries[1][2],
                  entries[2][0] + rhs.entries[2][0],
                  entries[2][1] + rhs.entries[2][1],
                  entries[2][2] + rhs.entries[2][2]);
}

Mat3x3 Mat3x3::operator-(const Mat3x3 &rhs) const
{
    return Mat3x3(entries[0][0] - rhs.entries[0][0],
                  entries[0][1] - rhs.entries[0][1],
                  entries[0][2] - rhs.entries[0][2],
                  entries[1][0] - rhs.entries[1][0],
                  entries[1][1] - rhs.entries[1][1],
                  entries[1][2] - rhs.entries[1][2],
                  entries[2][0] - rhs.entries[2][0],
                  entries[2][1] - rhs.entries[2][1],
                  entries[2][2] - rhs.entries[2][2]);
}

Mat3x3 Mat3x3::operator*(const Mat3x3 &rhs) const
{
    return Mat3x3(entries[0][0] * rhs.entries[0][0] + entries[0][1] * rhs.entries[1][0] + entries[0][2] * rhs.entries[2][0],
                  entries[0][0] * rhs.entries[0][1] + entries[0][1] * rhs.entries[1][1] + entries[0][2] * rhs.entries[2][1],
                  entries[0][0] * rhs.entries[0][2] + entries[0][1] * rhs.entries[1][2] + entries[0][2] * rhs.entries[2][2],
                  entries[1][0] * rhs.entries[0][0] + entries[1][1] * rhs.entries[1][0] + entries[1][2] * rhs.entries[2][0],
                  entries[1][0] * rhs.entries[0][1] + entries[1][1] * rhs.entries[1][1] + entries[1][2] * rhs.entries[2][1],
                  entries[1][0] * rhs.entries[0][2] + entries[1][1] * rhs.entries[1][2] + entries[1][2] * rhs.entries[2][2],
                  entries[2][0] * rhs.entries[0][0] + entries[2][1] * rhs.entries[1][0] + entries[2][2] * rhs.entries[2][0],
                  entries[2][0] * rhs.entries[0][1] + entries[2][1] * rhs.entries[1][1] + entries[2][2] * rhs.entries[2][1],
                  entries[2][0] * rhs.entries[0][2] + entries[2][1] * rhs.entries[1][2] + entries[2][2] * rhs.entries[2][2]);
}

Mat3x3 Mat3x3::operator*(const float rhs) const
{
    return Mat3x3(entries[0][0] * rhs,
                  entries[0][1] * rhs,
                  entries[0][2] * rhs,
                  entries[1][0] * rhs,
                  entries[1][1] * rhs,
                  entries[1][2] * rhs,
                  entries[2][0] * rhs,
                  entries[2][1] * rhs,
                  entries[2][2] * rhs);
}

Mat3x3 Mat3x3::operator/(const float rhs) const
{
    if (Equal(rhs, 0.0f) || Equal(rhs, 1.0f))
        return (*this);
    float temp = 1 / rhs;
    return (*this) * temp;
}

bool Mat3x3::operator==(const Mat3x3 &rhs) const
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (!Equal(entries[i][j], rhs.entries[i][j]))
                return false;
        }
    }
    return true;
}

bool Mat3x3::operator!=(const Mat3x3 &rhs) const
{
    return !((*this) == rhs);
}

void Mat3x3::operator+=(const Mat3x3 &rhs)
{
    (*this) = (*this) + rhs;
}

void Mat3x3::operator-=(const Mat3x3 &rhs)
{
    (*this) = (*this) - rhs;
}

void Mat3x3::operator*=(const Mat3x3 &rhs)
{
    (*this) = (*this) * rhs;
}

void Mat3x3::operator*=(const float rhs)
{
    (*this) = (*this) * rhs;
}

void Mat3x3::operator/=(const float rhs)
{
    (*this) = (*this) / rhs;
}

Mat3x3 Mat3x3::operator-() const
{
    Mat3x3 result(*this);
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; ++j)
            result.entries[i][j] = -result.entries[i][j];
    }

    return result;
}

Vec3 Mat3x3::operator*(const Vec3 rhs) const
{
    return Vec3(
        entries[0][0] * rhs.x + entries[0][1] * rhs.y + entries[0][2] * rhs.z,
        entries[1][0] * rhs.x + entries[1][1] * rhs.y + entries[1][2] * rhs.z,
        entries[2][0] * rhs.x + entries[2][1] * rhs.y + entries[2][2] * rhs.z);
}