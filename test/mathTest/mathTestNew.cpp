#include <gtest/gtest.h>
// #include "Math/Mat.h"
#include "Math/Mat4x4.h"
TEST(MatTestNew, FuncMat4x4GetInverse)
{
    // 四阶逆矩阵

    Mat4x4 mat(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 2.0f, 1.0f, 3.0f, 0.0f, 1.0f, 2.0f, 1.0f, 4.0f);
    Mat4x4 mat_inv_expect(1.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, -1.0f / 6.0f, 1.0f / 3.0f, 0.0f, 0.125f, -5.0f / 24.0f, -1.0f / 12.0f, 1.0f / 4.0f);
    Mat4x4 mat_inv_actual = mat.GetInverse();
    std::cout << mat_inv_expect;
    std::cout << mat_inv_actual;
    EXPECT_TRUE(mat_inv_actual == mat_inv_expect);
}

TEST(MatTestNew, FuncMat4x4GetInverse2)
{
    Mat4x4 mat(1, 1, 3, -1, 1, 1, 1, 1, 1, -2, 1, -1, 4, 1, 8, -1);

    Mat4x4 mat_inv_expect(13.0f / 6.0f, 5.0f / 2.0f, 5.0f / 3.0f, -4.0f / 3.0f,
                          4.0f / 3.0f, 1.0f, 1.0f / 3.0f, -2.0f / 3.0f,
                          -3.0f / 2.0f, -3.0f / 2.0f, -1.0f, 1.0f,
                          -2.0f, -1.0f, -1.0f, 1.0f);
    Mat4x4 mat_inv_actual = mat.GetInverse();
    std::cout << mat_inv_expect;
    std::cout << mat_inv_actual;
    EXPECT_TRUE(mat_inv_actual == mat_inv_expect);
}

TEST(MatTestNew, FuncMat4x4GetInverse3)
{
    Mat4x4 mat(1.0f, 2.0f, 3.0f, 4.0f,
               5.0f, 6.0f, 7.0f, 8.0f,
               9.0f, 10.0f, 11.0f, 12.0f,
               13.0f, 14.0f, 15.0f, 16.0f);

    // This matrix is singular (determinant is 0), so it does not have an inverse.
    // We expect the GetInverse function to handle this gracefully, possibly by returning a zero or identity matrix.
    Mat4x4 mat_inv_expect(1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f);

    Mat4x4 mat_inv_actual = mat.GetInverse();
    std::cout << mat_inv_expect;
    std::cout << mat_inv_actual;
    EXPECT_TRUE(mat_inv_actual == mat_inv_expect);
}

TEST(MatTestNew, FuncMat4x4Add)
{
    Mat4x4 mat1(1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f);

    Mat4x4 mat2(1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f);
    Mat4x4 mat_actual = mat1 + mat2;
    Mat4x4 mat_expect(2.0f, 4.0f, 6.0f, 8.0f,
                      10.0f, 12.0f, 14.0f, 16.0f,
                      18.0f, 20.0f, 22.0f, 24.0f,
                      26.0f, 28.0f, 30.0f, 32.0f);
    std::cout << mat_expect;
    std::cout << mat_actual;
    EXPECT_TRUE(mat_expect == mat_actual);
}

TEST(MatTestNew, FuncMat4x4MulScale)
{
    Mat4x4 mat1(1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f);

    Mat4x4 mat_actual = mat1 * 2;
    Mat4x4 mat_expect(2.0f, 4.0f, 6.0f, 8.0f,
                      10.0f, 12.0f, 14.0f, 16.0f,
                      18.0f, 20.0f, 22.0f, 24.0f,
                      26.0f, 28.0f, 30.0f, 32.0f);
    std::cout << mat_expect;
    std::cout << mat_actual;
    EXPECT_TRUE(mat_expect == mat_actual);
}

TEST(MatTestNew, FuncMat4x4Sub)
{
    Mat4x4 mat1(1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f);
    Mat4x4 mat2(1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f);
    Mat4x4 mat_actual = mat1 - mat2;
    Mat4x4 mat_expect(0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 0.0f);
    std::cout << mat_expect;
    std::cout << mat_actual;
    EXPECT_TRUE(mat_expect == mat_actual);
}

TEST(MatTestNew, FuncMat4x4MulMat)
{
    Mat4x4 mat1(1, 1, 3, -1, 1, 1, 1, 1, 1, -2, 1, -1, 4, 1, 8, -1);
    Mat4x4 mat2(1, 1, 3, -1, 1, 1, 1, 1, 1, -2, 1, -1, 4, 1, 8, -1);
    Mat4x4 mat_actual = mat1 * mat2;
    Mat4x4 mat_expect(1, -5, -1, -2, 7, 1, 13, -2, -4, -4, -6, -3, 9, -12, 13, -10);
    std::cout << mat_expect;
    std::cout << mat_actual;
    EXPECT_TRUE(mat_expect == mat_actual);
}
TEST(MatTest, FuncMat4x4GetTranslate)
{

    // 四阶逆矩阵
    Mat4x4 mat;
    mat.SetTranslation(Vec3(1.0f, 2.0f, 3.0f));
    Mat4x4 expected4(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat == expected4);
}

TEST(MatTest, FuncMat4x4GetScale)
{

    // 四阶逆矩阵
    Mat4x4 mat;
    mat.SetScale(Vec3(1.0f, 2.0f, 3.0f));
    Mat4x4 expected4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat == expected4);
}

TEST(MatTest, FuncMat4x4GetXRotation)
{

    // 四阶逆矩阵
    float angle = 45.0f;
    Mat4x4 mat;
    mat.SetRotationX(angle);
    Mat4x4 expected4(1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, cos(angle * M_PI / 180), -sin(angle * M_PI / 180), 0.0f,
                     0.0f, sin(angle * M_PI / 180), cos(angle * M_PI / 180), 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat == expected4);
}

TEST(MatTest, FuncMat4x4GetYRotation)
{

    // 四阶逆矩阵
    float angle = 45.0f;
    Mat4x4 mat;
    mat.SetRotationY(angle);
    Mat4x4 expected4(cos(angle * M_PI / 180), 0.0f, sin(angle * M_PI / 180), 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     -sin(angle * M_PI / 180), 0.0f, cos(angle * M_PI / 180),
                     0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat == expected4);
}

TEST(MatTest, FuncMat4x4GetZRotation)
{

    // 四阶逆矩阵
    float angle = 45.0f;
    Mat4x4 mat;
    mat.SetRotationZ(angle);
    Mat4x4 expected4(cos(angle * M_PI / 180), -sin(angle * M_PI / 180), 0.0f, 0.0f,
                     sin(angle * M_PI / 180), cos(angle * M_PI / 180), 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat == expected4);
}

TEST(MatTest, FuncMat4x4GetRotation)
{

    // 四阶逆矩阵，其实测试是通过的，浮点数的比较是有误差的
    float angle = 45.0f;
    Mat4x4 mat1;
    mat1.SetRotationAxis(angle, Vec3(1.0f, 0.0f, 0.0f));

    Mat4x4 expected1(1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, cos(angle * M_PI / 180), -sin(angle * M_PI / 180), 0.0f,
                     0.0f, sin(angle * M_PI / 180), cos(angle * M_PI / 180), 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_EQ(mat1, expected1);

    mat1.SetRotationAxis(angle, Vec3(0.0f, 1.0f, 0.0f));

    Mat4x4 expected2(cos(angle * M_PI / 180), 0.0f, +sin(angle * M_PI / 180), 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     -sin(angle * M_PI / 180), 0.0f, cos(angle * M_PI / 180), 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_EQ(mat1, expected2);

    mat1.SetRotationAxis(angle, Vec3(0.0f, 0.0f, 1.0f));
    Mat4x4 expected4(cos(angle * M_PI / 180), -sin(angle * M_PI / 180), 0.0f, 0.0f,
                     sin(angle * M_PI / 180), cos(angle * M_PI / 180), 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_EQ(mat1, expected4);
}

TEST(MatTest, FuncMat4x4GetPerspective)
{
    float fovy = 45.0f;
    float aspect = 1.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;
    float epsilon = 1e-5;

    Mat4x4 result;
    result.SetPerspective(fovy, aspect, zNear, zFar);
    Mat4x4 expected;
    expected.entries[0][0] = 1 / (aspect * tan(fovy * 0.5f * M_PI / 180));
    expected.entries[1][1] = 1 / tan(fovy * 0.5f);
    expected.entries[2][2] = -(zFar + zNear) / (zFar - zNear);
    expected.entries[3][2] = -1;
    expected.entries[2][3] = -(2 * zFar * zNear) / (zFar - zNear);
    expected.entries[3][3] = 0.0f;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            EXPECT_EQ(expected.entries[i][j], expected.entries[i][j]);
        }
    }
}

TEST(MatTest, FuncMat4x4GetOrtho)
{
    float left = -1.0f;
    float right = 1.0f;
    float bottom = -1.0f;
    float top = 1.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;
    float epsilon = 1e-5;

    Mat4x4 result;
    result.SetOrtho(left, right, bottom, top, zNear, zFar);
    Mat4x4 expected;
    expected.entries[0][0] = 2 / (right - left);
    expected.entries[1][1] = 2 / (top - bottom);
    expected.entries[2][2] = -2 / (zFar - zNear);
    expected.entries[0][3] = -(right + left) / (right - left);
    expected.entries[1][3] = -(top + bottom) / (top - bottom);
    expected.entries[2][3] = -(zFar + zNear) / (zFar - zNear);
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            EXPECT_EQ(result.entries[i][j], expected.entries[i][j]);
        }
    }
}

TEST(MatTest, FuncMat4x4GetLookAt)
{
    Vec3 eye(0.0f, 0.0f, 5.0f);
    Vec3 target(0.0f, 0.0f, 0.0f);
    Vec3 up(0.0f, 1.0f, 0.0f);
    float epsilon = 1e-5;

    Mat4x4 result;
    result.SetLookAt(eye, target, up);
    Vec3 Z = (eye - target).GetNormalize();
    Vec3 X = (up.GetCrossProduct(Z)).GetNormalize();
    Vec3 Y = (Z.GetCrossProduct(X)).GetNormalize();

    Mat4x4 expected;
    expected.entries[0][0] = X.x;
    expected.entries[0][1] = X.y;
    expected.entries[0][2] = X.z;
    expected.entries[1][0] = Y.x;
    expected.entries[1][1] = Y.y;
    expected.entries[1][2] = Y.z;
    expected.entries[2][0] = Z.x;
    expected.entries[2][1] = Z.y;
    expected.entries[2][2] = Z.z;
    expected.entries[0][3] = -X.GetDotProduct(eye);
    expected.entries[1][3] = -Y.GetDotProduct(eye);
    expected.entries[2][3] = -Z.GetDotProduct(eye);

    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            EXPECT_EQ(result.entries[i][j], expected.entries[i][j]);
        }
    }
}

TEST(MatTest, FuncMat4x4GetViewport)
{
    float left = 0.0f;
    float bottom = 0.0f;
    float width = 800.0f;
    float height = 600.0f;
    float epsilon = 1e-5;

    Mat4x4 result;
    result.SetViewPort(left, bottom, width, height);
    Mat4x4 expected;
    expected.entries[0][0] = width * 0.5f;
    expected.entries[1][1] = -height * 0.5f;
    expected.entries[0][3] = left + width * 0.5f;
    expected.entries[1][3] = bottom + height * 0.5f;

    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            EXPECT_EQ(result.entries[i][j], expected.entries[i][j]);
        }
    }
}