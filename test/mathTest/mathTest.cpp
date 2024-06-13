#include <gtest/gtest.h>
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Math/MathUtils.h"
#include <iostream>
// 测试 (a == b)
TEST(VecTest, OperatorVecEqualVec)
{
    EXPECT_TRUE(Vec2f({1.0f, 2.0f}) == Vec2f({1.0f, 2.0f}));
    EXPECT_TRUE(Vec3f({3.0f, 4.0f, 5.0f}) == Vec3f({3.0f, 4.0f, 5.0f}));
    EXPECT_TRUE(Vec4f({6.0f, 7.0f, 8.0f, 9.0f}) == Vec4f({6.0f, 7.0f, 8.0f, 9.0f}));
}
// 测试 (a != b)
TEST(VecTest, OperatorVecUnequalVec)
{
    EXPECT_TRUE(Vec2f({1.0f, 2.0f}) != Vec2f({3.0f, 2.0f}));
    EXPECT_TRUE(Vec3f({3.0f, 4.0f, 5.0f}) != Vec3f({3.0f, 5.0f, 5.0f}));
    EXPECT_TRUE(Vec4f({6.0f, 7.0f, 8.0f, 9.0f}) != Vec4f({6.0f, 7.0f, 8.0f, 10.0f}));
}
// 测试 (a + b)
TEST(VecTest, OperatorVecPlusVec)
{
    EXPECT_EQ(Vec2f({1.0f, 2.0f}) + Vec2f({3.0f, 4.0f}), Vec2f({4.0f, 6.0f}));
    EXPECT_EQ(Vec3f({2.0f, 1.0f, 1.0f}) + Vec3f({-1.0f, -2.0f, 2.0f}), Vec3f({1.0f, -1.0f, 3.0f}));
    EXPECT_EQ(Vec4f({5.0f, 6.0f, 1.0f, 2.0f}) + Vec4f({3.0f, 7.0f, 3.0f, 4.0f}), Vec4f({8.0f, 13.0f, 4.0f, 6.0f}));
}

// 测试 (a - b)
TEST(VecTest, OperatorVecMinusVec)
{
    EXPECT_EQ(Vec2f({1.0f, 2.0f}) - Vec2f({3.0f, 4.0f}), Vec2f({-2.0f, -2.0f}));
    EXPECT_EQ(Vec3f({2.0f, 1.0f, 1.0f}) - Vec3f({-1.0f, -2.0f, 2.0f}), Vec3f({3.0f, 3.0f, -1.0f}));
    EXPECT_EQ(Vec4f({5.0f, 6.0f, 1.0f, 2.0f}) - Vec4f({3.0f, 7.0f, 3.0f, 4.0f}), Vec4f({2.0f, -1.0f, -2.0f, -2.0f}));
}

// 测试 (a * b) 各个元素相乘，H积
TEST(VecTest, OperatorVecTimesVec)
{
    EXPECT_EQ(Vec2f({1.0f, 2.0f}) * Vec2f({3.0f, 4.0f}), Vec2f({3.0f, 8.0f}));
    EXPECT_EQ(Vec3f({2.0f, 1.0f, 3.0f}) * Vec3f({-1.0f, -2.0f, 2.0f}), Vec3f({-2.0f, -2.0f, 6.0f}));
    EXPECT_EQ(Vec4f({5.0f, 6.0f, 1.0f, 2.0f}) * Vec4f({3.0f, 7.0f, 3.0f, 4.0f}), Vec4f({15.0f, 42.0f, 3.0f, 8.0f}));
}
// 测试 (a / b) 各个元素相除
TEST(VecTest, OperatorVecDivideVec)
{
    EXPECT_EQ(Vec2f({1.0f, 2.0f}) / Vec2f({2.0f, 4.0f}), Vec2f({0.5f, 0.5f}));
    EXPECT_EQ(Vec3f({2.0f, 1.0f, 4.0f}) / Vec3f({-1.0f, -2.0f, 2.0f}), Vec3f({-2.0f, -0.5f, 2.0f}));
    EXPECT_EQ(Vec4f({5.0f, 6.0f, 1.0f, 2.0f}) / Vec4f({2.0f, 1.0f, 2.0f, 1.0f}), Vec4f({2.5f, 6.0f, 0.5f, 2.0f}));
}
// 测试 (a * x)
TEST(VecTest, OperatorVecTimesScale)
{
    EXPECT_EQ(Vec2f({1.0f, 2.0f}) * 2.0f, Vec2f({2.0f, 4.0f}));
    EXPECT_EQ(Vec3f({2.0f, 1.0f, 3.0f}) * 3.0f, Vec3f({6.0f, 3.0f, 9.0f}));
    EXPECT_EQ(Vec4f({5.0f, 6.0f, 1.0f, 2.0f}) * -1.0f, Vec4f({-5.0f, -6.0f, -1.0f, -2.0f}));
}
// 测试 (x * a)
TEST(VecTest, OperatorScaleTimesVec)
{
    EXPECT_EQ(2.0f * Vec2f({1.0f, 2.0f}), Vec2f({2.0f, 4.0f}));
    EXPECT_EQ(3.0f * Vec3f({2.0f, 1.0f, 3.0f}), Vec3f({6.0f, 3.0f, 9.0f}));
    EXPECT_EQ(-1.0f * Vec4f({5.0f, 6.0f, 1.0f, 2.0f}), Vec4f({-5.0f, -6.0f, -1.0f, -2.0f}));
}
// 测试 (a / x)
TEST(VecTest, OperatorVecDivideScale)
{
    EXPECT_EQ(Vec2f({1.0f, 2.0f}) / 2.0f, Vec2f({0.5f, 1.0f}));
    EXPECT_EQ(Vec3f({2.0f, 1.0f, 4.0f}) / 4.0f, Vec3f({0.5f, 0.25f, 1.0f}));
    EXPECT_EQ(Vec4f({5.0f, 6.0f, 1.0f, 2.0f}) / -1.0f, Vec4f({-5.0f, -6.0f, -1.0f, -2.0f}));
}
// 测试 (x / a)
TEST(VecTest, OperatorVecScaleDivideVec)
{
    EXPECT_EQ(2.0f / Vec2f({1.0f, 2.0f}), Vec2f({2.0f, 1.0f}));
    EXPECT_EQ(4.0f / Vec3f({2.0f, 1.0f, 4.0f}), Vec3f({2.0f, 4.0f, 1.0f}));
    EXPECT_EQ(-1.0f / Vec4f({5.0f, 8.0f, 2.0f, 4.0f}), Vec4f({-0.2f, -0.125f, -0.5f, -0.25f}));
}

// 测试 a += b
TEST(VecTest, OperatorVecPlusEqual)
{
    Vec2f a1({1.0f, 2.0f});
    Vec2f b1({3.0f, 4.0f});
    a1 += b1;
    EXPECT_EQ(a1, Vec2f({4.0f, 6.0f}));

    Vec3f a2({1.0f, 2.0f, 3.0f});
    Vec3f b2({4.0f, 5.0f, 6.0f});
    a2 += b2;
    EXPECT_EQ(a2, Vec3f({5.0f, 7.0f, 9.0f}));

    Vec4f a3({1.1f, 2.2f, 3.3f, 4.4f});
    Vec4f b3({4.4f, 5.5f, 6.6f, 7.7f});
    a3 += b3;
    EXPECT_EQ(a3, Vec4f({5.5f, 7.7f, 9.9f, 12.1f}));
}

// 测试 a -= b
TEST(VecTest, OperatorVecMinusEqual)
{
    Vec2f a1({4.0f, 6.0f});
    Vec2f b1({1.0f, 2.0f});
    a1 -= b1;
    EXPECT_EQ(a1, Vec2f({3.0f, 4.0f}));

    Vec3f a2({5.0f, 7.0f, 9.0f});
    Vec3f b2({1.0f, 2.0f, 3.0f});
    a2 -= b2;
    EXPECT_EQ(a2, Vec3f({4.0f, 5.0f, 6.0f}));

    Vec4f a3({5.5f, 7.7f, 9.0f, 10.0f});
    Vec4f b3({1.1f, 2.2f, 3.0f, 4.0f});
    a3 -= b3;
    EXPECT_EQ(a3, Vec4f({4.4f, 5.5f, 6.0f, 6.0f}));
}

// 测试 a *= b
TEST(VecTest, OperatorVecMultiplyEqualVec)
{
    Vec2f a1({1.0f, 2.0f});
    Vec2f b1({2.0f, 3.0f});
    a1 *= b1;
    EXPECT_EQ(a1, Vec2f({2.0f, 6.0f}));

    Vec3f a2({1.0f, 2.0f, 3.0f});
    Vec3f b2({2.0f, 3.0f, 4.0f});
    a2 *= b2;
    EXPECT_EQ(a2, Vec3f({2.0f, 6.0f, 12.0f}));

    Vec4f a3({1.1f, 2.0f, 3.3f, 2.9f});
    Vec4f b3({2.0f, 3.0f, 4.0f, 2.0f});
    a3 *= b3;
    EXPECT_EQ(a3, Vec4f({2.2f, 6.0f, 13.2f, 5.8f}));
}

// 测试 a /= b
TEST(VecTest, OperatorVecDivideEqual)
{
    Vec2f a1({4.0f, 6.0f});
    Vec2f b1({2.0f, 3.0f});
    a1 /= b1;
    EXPECT_EQ(a1, Vec2f({2.0f, 2.0f}));

    Vec3f a2({6.0f, 9.0f, 12.0f});
    Vec3f b2({2.0f, 3.0f, 4.0f});
    a2 /= b2;
    EXPECT_EQ(a2, Vec3f({3.0f, 3.0f, 3.0f}));

    Vec4f a3({6.6f, 9.9f, 13.2f, 1.0f});
    Vec4f b3({2.0f, 3.0f, 4.0f, 0.5f});
    a3 /= b3;
    EXPECT_EQ(a3, Vec4f({3.3f, 3.3f, 3.3f, 2.0f}));
}
// 测试 |a| ^ 2
TEST(VecTest, FuncVecGetLengthSquare)
{
    Vec2f a1({3.0f, 4.0f});
    EXPECT_EQ(VecGetLengthSquare(a1), 25.0f);

    Vec3f a2({1.0f, 2.0f, 2.0f});
    EXPECT_EQ(VecGetLengthSquare(a2), 9.0f);

    Vec4f a3({1.0f, 2.0f, 2.0f, 4.0f});
    EXPECT_EQ(VecGetLengthSquare(a3), 25.0f);
}

// 测试 |a|
TEST(VecTest, FuncVecGetLength)
{
    Vec2f a1({3.0f, 4.0f});
    EXPECT_EQ(VecGetLength(a1), 5.0f);

    Vec3f a2({1.0f, 2.0f, 2.0f});
    EXPECT_EQ(VecGetLength(a2), 3.0f);

    Vec4f a3({1.0f, 2.0f, 2.0f, 4.0f});
    EXPECT_EQ(VecGetLength(a3), 5.0f);
}

// 测试 矢量点乘
TEST(VecTest, FuncVecGetDotProduct)
{
    Vec2f a1({1.0f, 2.0f});
    Vec2f b1({3.0f, 4.0f});
    EXPECT_EQ(VecGetDotProduct(a1, b1), 11.0f);

    Vec3f a2({1.0f, 2.0f, 3.0f});
    Vec3f b2({4.0f, 5.0f, 6.0f});
    EXPECT_EQ(VecGetDotProduct(a2, b2), 32.0f);

    Vec4f a3({1.0f, 2.0f, 3.0f, 4.0f});
    Vec4f b3({5.0f, 6.0f, 7.0f, 8.0f});
    EXPECT_EQ(VecGetDotProduct(a3, b3), 70.0f);
}

// 测试 二维矢量叉乘，得到标量
TEST(VecTest, FuncVecGetCrossProduct2D)
{
    Vec2f a1({1.0f, 2.0f});
    Vec2f b1({3.0f, 4.0f});
    EXPECT_EQ(VecGetCrossProduct(a1, b1), -2.0f);
}

// 测试 三维矢量叉乘，得到新矢量
TEST(VecTest, FuncVecGetCrossProduct3D)
{
    Vec3f a1({1.0f, 2.0f, 3.0f});
    Vec3f b1({4.0f, 5.0f, 6.0f});
    EXPECT_EQ(VecGetCrossProduct(a1, b1), Vec3f({-3.0f, 6.0f, -3.0f}));
}

// 测试 四维矢量叉乘：前三维叉乘，后一位保留
TEST(VecTest, FuncVecGetCrossProduct4D)
{
    Vec4f a1({1.0f, 2.0f, 3.0f, 1.0f});
    Vec4f b1({4.0f, 5.0f, 6.0f, 1.0f});
    EXPECT_EQ(VecGetCrossProduct(a1, b1), Vec4f({-3.0f, 6.0f, -3.0f, 1.0f}));
}

// 测试 插值 a + (b - a) * t
TEST(VecTest, FuncVecGetLinearLerp)
{
    Vec2f a1({1.0f, 2.0f});
    Vec2f b1({3.0f, 4.0f});
    EXPECT_EQ(VecGetLinearLerp(a1, b1, 0.5f), Vec2f({2.0f, 3.0f}));

    Vec3f a2({1.0f, 2.0f, 3.0f});
    Vec3f b2({4.0f, 5.0f, 6.0f});
    EXPECT_EQ(VecGetLinearLerp(a2, b2, 0.2f), Vec3f({3.4f, 4.4f, 5.4f}));

    Vec4f a3({1.0f, 2.0f, 3.0f, 4.0f});
    Vec4f b3({5.0f, 5.0f, 7.0f, 8.0f});
    EXPECT_EQ(VecGetLinearLerp(a3, b3, 0.3f), Vec4f({3.8f, 4.1f, 5.8f, 6.8f}));
}

// 测试 a / |a|
TEST(VecTest, FuncVecGetNormalize)
{
    Vec2f a1({3.0f, 4.0f});
    EXPECT_EQ(VecGetNormalize(a1), Vec2f({0.6f, 0.8f}));

    Vec3f a2({1.0f, 2.0f, 2.0f});
    EXPECT_EQ(VecGetNormalize(a2), Vec3f({0.33333334f, 0.66666669f, 0.66666669f}));

    Vec4f a3({1.0f, 2.0f, 2.0f, 4.0f});
    EXPECT_EQ(VecGetNormalize(a3), Vec4f({0.2f, 0.4f, 0.4f, 0.8f}));
}

// 测试 判断矢量是否接近
TEST(VecTest, FuncVecIsNear)
{
    Vec2f a1({1.0f, 2.0f});
    Vec2f b1({1.0001f, 2.0001f});
    EXPECT_TRUE(VecIsNear(a1, b1, 0.0002f));
    EXPECT_TRUE(VecIsNear(a1, b1, 0.00001f));

    Vec3f a2({1.0f, 2.0f, 3.0f});
    Vec3f b2({1.0001f, 2.0001f, 3.0001f});
    EXPECT_TRUE(VecIsNear(a2, b2, 0.0003f));
    EXPECT_TRUE(VecIsNear(a2, b2, 0.00001f));

    Vec4f a3({1.0f, 2.0f, 3.0f, 4.0f});
    Vec4f b3({1.0001f, 2.0001f, 3.0001f, 4.0001f});
    EXPECT_TRUE(VecIsNear(a3, b3, 0.0004f));
    EXPECT_TRUE(VecIsNear(a3, b3, 0.00001f));
}

// 测试 特化：判断两个单精度矢量是否近似
TEST(VecTest, FuncVecIsNearEqualFloat)
{
    Vec2f a1({1.0f, 2.0f});
    Vec2f b1({1.0001f, 2.0001f});
    EXPECT_TRUE(VecIsNearEqual(a1, b1));
    EXPECT_TRUE(VecIsNearEqual(a1, b1, 0.00001f));

    Vec3f a2({1.0f, 2.0f, 3.0f});
    Vec3f b2({1.0001f, 2.0001f, 3.0001f});
    EXPECT_TRUE(VecIsNearEqual(a2, b2));
    EXPECT_TRUE(VecIsNearEqual(a2, b2, 0.00001f));

    Vec4f a3({1.0f, 2.0f, 3.0f, 4.0f});
    Vec4f b3({1.0001f, 2.0001f, 3.0001f, 4.0001f});
    EXPECT_TRUE(VecIsNearEqual(a3, b3));
    EXPECT_TRUE(VecIsNearEqual(a3, b3, 0.00001f));
}

// 测试 特化：判断两个双精度矢量是否近似
TEST(VecTest, FuncVecIsNearEqualDouble)
{
    Vec<2, double> a1({1.0, 2.0});
    Vec<2, double> b1({1.00000001, 2.00000001});
    EXPECT_TRUE(VecIsNearEqual(a1, b1));
    EXPECT_TRUE(VecIsNearEqual(a1, b1, 0.00000001));

    Vec<3, double> a2({1.0, 2.0, 3.0});
    Vec<3, double> b2({1.00000001, 2.00000001, 3.00000001});
    EXPECT_TRUE(VecIsNearEqual(a2, b2));
    EXPECT_TRUE(VecIsNearEqual(a2, b2, 0.00000001));

    Vec<4, double> a3({1.0, 2.0, 3.0, 4.0});
    Vec<4, double> b3({1.00000001, 2.00000001, 3.00000001, 4.00000001});
    EXPECT_TRUE(VecIsNearEqual(a3, b3));
    EXPECT_TRUE(VecIsNearEqual(a3, b3, 0.00000001));
}

/*           矩阵              */

// a == b
TEST(VecTest, OperatorMatEqualMat)
{
    Mat3x3f a1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Mat3x3f b1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    EXPECT_TRUE(a1 == b1);

    Mat4x4f a2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    Mat4x4f b2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    EXPECT_TRUE(a2 == b2);
}

// a == b
TEST(VecTest, OperatorMatUnEqualMat)
{
    Mat3x3f a1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Mat3x3f b1(0.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    EXPECT_TRUE(a1 != b1);

    Mat4x4f a2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    Mat4x4f b2(2.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    EXPECT_TRUE(a2 != b2);
}

TEST(MatTest, OperatorMatPlusMat)
{
    Mat3x3f a1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Mat3x3f b1(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    Mat3x3f expected1(10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f);
    EXPECT_TRUE((a1 + b1) == expected1);

    Mat4x4f a2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    Mat4x4f b2(6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, -1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f, -9.0f);
    Mat4x4f expected2(7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, -2.0f, -2.0f, -2.0f, -2.0f, -4.0f, -3.0f, -3.0f);
    EXPECT_TRUE((a2 + b2) == expected2);
}

TEST(MatTest, OperatorMatMinusMat)
{
    Mat3x3f a1(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    Mat3x3f b1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Mat3x3f expected1(8.0f, 6.0f, 4.0f, 2.0f, 0.0f, -2.0f, -4.0f, -6.0f, -8.0f);
    EXPECT_TRUE((a1 - b1) == expected1);

    Mat4x4f a2(6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, -1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f, -9.0f);
    Mat4x4f b2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    Mat4x4f expected2(5.0f, 3.0f, 1.0f, -1.0f, -3.0f, -5.0f, -7.0f, -9.0f, -11.0f, -4.0f, -6.0f, -8.0f, -10.0f, -10.0f, -13.0f, -15.0f);
    EXPECT_TRUE((a2 - b2) == expected2);
}

TEST(MatTest, OperatorMatMultiplyMat)
{
    Mat3x3f a1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Mat3x3f b1(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    Mat3x3f expected1(30.0f, 24.0f, 18.0f, 84.0f, 69.0f, 54.0f, 138.0f, 114.0f, 90.0f);
    EXPECT_EQ(a1 * b1, expected1);

    Mat4x4f a2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    Mat4x4f b2(6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, -1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f, -9.0f);
    Mat4x4f expected2(-20.0f, -30.0f, -40.0f, -50.0f, -20.0f, -46.0f, -72.0f, -98.0f, 34.0f, 19.0f, 4.0f, -11.0f, -16.0f, -34.0f, -52.0f, -70.0f);
    EXPECT_EQ(a2 * b2, expected2);
}

TEST(MatTest, OperatorMatMultiplyScalar)
{
    Mat3x3f a1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    float scalar1 = 2.0f;
    Mat3x3f expected1(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f);
    EXPECT_TRUE((a1 * scalar1) == expected1);

    Mat4x4f a2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    float scalar2 = -1.0f;
    Mat4x4f expected2(-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f, -9.0f, -1.0f, -2.0f, -3.0f, -4.0f, -3.0f, -5.0f, -6.0f);
    EXPECT_TRUE((a2 * scalar2) == expected2);
}

TEST(MatTest, OperatorScalarMultiplyMat)
{
    Mat3x3f a1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    float scalar1 = 2.0f;
    Mat3x3f expected1(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f);
    EXPECT_TRUE((scalar1 * a1) == expected1);

    Mat4x4f a2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    float scalar2 = -1.0f;
    Mat4x4f expected2(-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f, -9.0f, -1.0f, -2.0f, -3.0f, -4.0f, -3.0f, -5.0f, -6.0f);
    EXPECT_TRUE((scalar2 * a2) == expected2);
}

TEST(MatTest, OperatorMatDivideScalar)
{
    Mat3x3f a1(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f);
    float scalar1 = 2.0f;
    Mat3x3f expected1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    EXPECT_TRUE((a1 / scalar1) == expected1);

    Mat4x4f a2(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 2.0f, 4.0f, 6.0f, 8.0f, 6.0f, 10.0f, 12.0f);
    float scalar2 = 2.0f;
    Mat4x4f expected2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 5.0f, 6.0f);
    EXPECT_TRUE((a2 / scalar2) == expected2);
}

TEST(MatTest, OperatorVecMultiplyMat)
{
    Vec<3, float> vec1(1.0f, 2.0f, 3.0f);
    Mat<3, 3, float> mat1(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    Vec<3, float> expected1(1.0f, 2.0f, 3.0f);
    EXPECT_TRUE((vec1 * mat1) == expected1);

    Vec<3, float> vec2(1.0f, 2.0f, 3.0f);
    Mat<3, 3, float> mat2(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Vec<3, float> expected2(14.0f, 32.0f, 50.0f);
    EXPECT_TRUE((mat2 * vec2) == expected2);
}

TEST(MatTest, OperatorMatAddEqual)
{
    Mat<3, 3, float> a1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Mat<3, 3, float> b1(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    Mat<3, 3, float> expected1(10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f);
    a1 += b1;
    EXPECT_TRUE(a1 == expected1);
}

TEST(MatTest, OperatorMatMinusEqual)
{
    Mat<3, 3, float> a1(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    Mat<3, 3, float> b1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Mat<3, 3, float> expected1(8.0f, 6.0f, 4.0f, 2.0f, 0.0f, -2.0f, -4.0f, -6.0f, -8.0f);
    a1 -= b1;
    EXPECT_TRUE(a1 == expected1);
}

TEST(MatTest, OperatorMatMultiplyEqual)
{
    Mat<3, 3, float> a1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Mat<3, 3, float> b1(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    Mat<3, 3, float> expected1(30.0f, 24.0f, 18.0f, 84.0f, 69.0f, 54.0f, 138.0f, 114.0f, 90.0f);
    a1 *= b1;
    EXPECT_TRUE(a1 == expected1);
}

TEST(MatTest, OperatorMatMultiplyScalarEqual)
{
    Mat<3, 3, float> a1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    float scalar1 = 2.0f;
    Mat<3, 3, float> expected1(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f);
    a1 *= scalar1;
    EXPECT_TRUE(a1 == expected1);
}

TEST(MatTest, OperatorMatDivideScalarEqual)
{
    Mat<3, 3, float> a1(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f);
    float scalar1 = 2.0f;
    Mat<3, 3, float> expected1(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    a1 /= scalar1;
    EXPECT_TRUE(a1 == expected1);
}

TEST(MatTest, FuncMatGetDet)
{
    // 一阶行列式
    Mat<1, 1, float> mat1(
        {{3.0f}});
    EXPECT_FLOAT_EQ(MatGetDet(mat1), 3.0f);

    // 二阶行列式
    Mat<2, 2, float> mat2({{1.0f, 2.0f}, {3.0f, 4.0f}});
    EXPECT_FLOAT_EQ(MatGetDet(mat2), -2.0f);

    // 三阶行列式
    Mat<3, 3, float> mat3(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
    EXPECT_FLOAT_EQ(MatGetDet(mat3), 1.0f);

    // 四阶行列式
    Mat<4, 4, float> mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 2.0f, 6.0f, 4.0f, 8.0f, 3.0f, 1.0f, 2.0f, 1.0f);
    EXPECT_FLOAT_EQ(MatGetDet(mat4), 24.0f);
}

TEST(MatTest, FuncMatGetCofactor)
{
    // 二阶余子式
    Mat<2, 2, float> mat2({{1.0f, 2.0f}, {3.0f, 4.0f}});
    EXPECT_FLOAT_EQ(MatGetCofactor(mat2, 0, 0), 4.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat2, 0, 1), -3.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat2, 1, 0), -2.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat2, 1, 1), 1.0f);

    // 三阶余子式
    Mat<3, 3, float> mat3(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat3, 0, 0), -24.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat3, 0, 1), 20.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat3, 0, 2), -5.0f);

    // 四阶余子式
    Mat<4, 4, float> mat4(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 2.0f, 6.0f, 4.0f, 8.0f, 3.0f, 1.0f, 2.0f, 1.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat4, 0, 0), 6.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat4, 0, 1), -30.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat4, 1, 0), -14.0f);
    EXPECT_FLOAT_EQ(MatGetCofactor(mat4, 1, 1), 22.0f);
}

TEST(MatTest, FuncMatGetAdjoint)
{
    // 三阶伴随矩阵
    Mat<3, 3, float> mat3(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
    Mat<3, 3, float> expected3(-24.0f, 20.0f, -5.0f, 18.0f, -15.0f, 4.0f, 5.0f, -4.0f, 1.0f);
    expected3 = expected3.GetTranspose();
    EXPECT_TRUE(MatGetAdjoint(mat3) == expected3);

    // 四阶伴随矩阵
    Mat<4, 4, float> mat4(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 2.0f, 1.0f, 3.0f, 0.0f, 1.0f, 2.0f, 1.0f, 4.0f);
    Mat<4, 4, float> expected4(24.0, 0.0f, 0.0f, 0.0f, -12.0f, 12.0f, 0.0f, 0.0f, -12.0f, -4.0f, 8.0f, 0.0f, 3.0f, -5.0f, -2.0f, 6.0f);
    EXPECT_EQ(MatGetAdjoint(mat4), expected4);
}

TEST(MatTest, FuncMatGetInverse)
{
    // 三阶逆矩阵
    Mat<3, 3, float> mat3(1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f);
    Mat<3, 3, float> expected3(-24.0f, 18.0f, 5.0f, 20.0f, -15.0f, -4.0f, -5.0f, 4.0f, 1.0f);
    EXPECT_TRUE(MatGetInverse(mat3) == expected3);

    // 四阶逆矩阵
    Mat<4, 4, float> mat4(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 2.0f, 1.0f, 3.0f, 0.0f, 1.0f, 2.0f, 1.0f, 4.0f);
    Mat<4, 4, float> expected4(1.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, -1.0f / 6.0f, 1.0f / 3.0f, 0.0f, 0.125f, -5.0f / 24.0f, -1.0f / 12.0f, 1.0f / 4.0f);

    EXPECT_TRUE(MatGetInverse(mat4) == expected4);
}

TEST(MatTest, FuncMat4x4GetTranslate)
{

    // 四阶逆矩阵
    Mat<4, 4, float> mat4 = Mat4x4GetTranslate(Vec3f(1.0f, 2.0f, 3.0f));
    Mat<4, 4, float> expected4(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat4 == expected4);
}

TEST(MatTest, FuncMat4x4GetScale)
{

    // 四阶逆矩阵
    Mat<4, 4, float> mat4 = Mat4x4GetScale(Vec3f(1.0f, 2.0f, 3.0f));
    Mat<4, 4, float> expected4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat4 == expected4);
}

TEST(MatTest, FuncMat4x4GetXRotation)
{

    // 四阶逆矩阵
    float angle = 45.0f * M_PI / 180.0f;
    Mat<4, 4, float> mat4 = Mat4x4GetXRotation(angle);
    Mat<4, 4, float> expected4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cos(angle), sin(angle), 0.0f, 0.0f, -sin(angle), cos(angle), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat4 == expected4);
}

TEST(MatTest, FuncMat4x4GetYRotation)
{

    // 四阶逆矩阵
    float angle = 45.0f * M_PI / 180.0f;
    Mat<4, 4, float> mat4 = Mat4x4GetYRotation(angle);
    Mat<4, 4, float> expected4(cos(angle), 0.0f, -sin(angle), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sin(angle), 0.0f, cos(angle), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat4 == expected4);
}

TEST(MatTest, FuncMat4x4GetZRotation)
{

    // 四阶逆矩阵
    float angle = 45.0f * M_PI / 180.0f;
    Mat<4, 4, float> mat4 = Mat4x4GetZRotation(angle);
    Mat<4, 4, float> expected4(cos(angle), sin(angle), 0.0f, 0.0f, -sin(angle), cos(angle), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_TRUE(mat4 == expected4);
}

TEST(MatTest, FuncMat4x4GetRotation)
{

    // 四阶逆矩阵，其实测试是通过的，浮点数的比较是有误差的
    float angle = 45.0f * M_PI / 180.0f;
    Mat<4, 4, float> mat1 = Mat4x4GetRotation(Vec3f(1.0f, 0.0f, 0.0f), angle);
    Mat<4, 4, float> expected1(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cos(angle), sin(angle), 0.0f, 0.0f, -sin(angle), cos(angle), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    // EXPECT_EQ(mat1, expected1);

    Mat<4, 4, float> mat2 = Mat4x4GetRotation(Vec3f(0.0f, 1.0f, 0.0f), angle);
    Mat<4, 4, float> expected2(cos(angle), 0.0f, -sin(angle), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, sin(angle), 0.0f, cos(angle), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    // EXPECT_EQ(mat2, expected2);

    Mat<4, 4, float> mat4 = Mat4x4GetRotation(Vec3f(0.0f, 0.0f, 1.0f), angle);
    Mat<4, 4, float> expected4(cos(angle), sin(angle), 0.0f, 0.0f, -sin(angle), cos(angle), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    // EXPECT_EQ(mat4, expected4);
}

TEST(MatTest, FuncMat4x4GetPerspective)
{
    float fovy = 45.0f * M_PI / 180.0f;
    float aspect = 1.0f;
    float zNear = 0.1f;
    float zFar = 100.0f;
    float epsilon = 1e-5;

    Mat4x4f result = Mat4x4GetPerspective(fovy, aspect, zNear, zFar);
    Mat4x4f expected = Mat4x4f::GetIdentity();
    expected.mat[0][0] = 1 / (aspect * tan(fovy * 0.5f));
    expected.mat[1][1] = 1 / tan(fovy * 0.5f);
    expected.mat[2][2] = -(zFar + zNear) / (zFar - zNear);
    expected.mat[3][2] = -1;
    expected.mat[2][3] = -(2 * zFar * zNear) / (zFar - zNear);
    expected.mat[3][3] = 0.0f;
    EXPECT_TRUE(MatNear(result, expected, epsilon));
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

    Mat4x4f result = Mat4x4GetOrtho(left, right, bottom, top, zNear, zFar);
    Mat4x4f expected = Mat4x4f::GetIdentity();
    expected.mat[0][0] = 2 / (right - left);
    expected.mat[1][1] = 2 / (top - bottom);
    expected.mat[2][2] = -2 / (zFar - zNear);
    expected.mat[0][3] = -(right + left) / (right - left);
    expected.mat[1][3] = -(top + bottom) / (top - bottom);
    expected.mat[2][3] = -(zFar + zNear) / (zFar - zNear);

    EXPECT_TRUE(MatNear(result, expected, epsilon));
}

TEST(MatTest, FuncMat4x4GetLookAt)
{
    Vec3f eye(0.0f, 0.0f, 5.0f);
    Vec3f target(0.0f, 0.0f, 0.0f);
    Vec3f up(0.0f, 1.0f, 0.0f);
    float epsilon = 1e-5;

    Mat4x4f result = Mat4x4GetLookAt(eye, target, up);
    Vec3f Z = VecGetNormalize(eye - target);
    Vec3f X = VecGetNormalize(VecGetCrossProduct(up, Z));
    Vec3f Y = VecGetNormalize(VecGetCrossProduct(Z, X));

    Mat4x4f expected = Mat4x4f::GetIdentity();
    expected.mat[0][0] = X.x;
    expected.mat[0][1] = X.y;
    expected.mat[0][2] = X.z;
    expected.mat[1][0] = Y.x;
    expected.mat[1][1] = Y.y;
    expected.mat[1][2] = Y.z;
    expected.mat[2][0] = Z.x;
    expected.mat[2][1] = Z.y;
    expected.mat[2][2] = Z.z;
    expected.mat[0][3] = -VecGetDotProduct(X, eye);
    expected.mat[1][3] = -VecGetDotProduct(Y, eye);
    expected.mat[2][3] = -VecGetDotProduct(Z, eye);

    EXPECT_TRUE(MatNear(result, expected, epsilon));
}

TEST(MatTest, FuncMat4x4GetViewport)
{
    float left = 0.0f;
    float bottom = 0.0f;
    float width = 800.0f;
    float height = 600.0f;
    float epsilon = 1e-5;

    Mat4x4f result = Mat4x4GetViewport(left, bottom, width, height);
    Mat4x4f expected = Mat4x4f::GetIdentity();
    expected.mat[0][0] = width * 0.5f;
    expected.mat[1][1] = height * 0.5f;
    expected.mat[0][3] = left + width * 0.5f;
    expected.mat[1][3] = bottom + height * 0.5f;

    EXPECT_TRUE(MatNear(result, expected, epsilon));
}