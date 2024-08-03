#ifndef MAT_H
#define MAT_H
#include <initializer_list>
#include "Vec.h"
#include <iostream>
#include "MathUtils.h"
template <size_t ROW, size_t COL, typename T>
struct Mat
{
    T mat[ROW][COL];

    inline Mat()
    {
        for (size_t r = 0; r < ROW; ++r)
        {
            for (size_t c = 0; c < COL; ++c)
                mat[r][c] = (r == c) ? 1 : 0;
        }
    }

    inline Mat(const Mat<ROW, COL, T> &rhs)
    {
        for (size_t r = 0; r < ROW; ++r)
        {
            for (size_t c = 0; c < COL; ++c)
                mat[r][c] = rhs.mat[r][c];
        }
    }
    // 给定列的initializer_list赋值
    inline Mat(const std::initializer_list<Vec<COL, T>> &rhs)
    {
        auto it = rhs.begin();
        for (size_t i = 0; i < ROW; ++i)
            SetRow(i, *it++);
    }

    inline const T *operator[](size_t row) const
    {
        assert(row < ROW);
        return mat[row];
    }
    inline T *operator[](size_t row)
    {
        assert(row < ROW);
        return mat[row];
    }

    // 取一行
    inline Vec<COL, T> GetRow(size_t row) const
    {
        assert(row < ROW);
        Vec<COL, T> a;
        for (size_t i = 0; i < COL; ++i)
            a[i] = mat[row][i];
        return a;
    }

    // 取一列
    inline Vec<ROW, T> GetCol(size_t col) const
    {
        assert(col < COL);
        Vec<ROW, T> a;
        for (size_t i = 0; i < ROW; ++i)
            a[i] = mat[i][col];
        return a;
    }

    // 设置一行
    inline void SetRow(size_t row, const Vec<COL, T> &a)
    {
        assert(row < ROW);
        for (size_t i = 0; i < COL; ++i)
            mat[row][i] = a[i];
    }

    // 设置一列
    inline void SetCol(size_t col, const Vec<ROW, T> &a)
    {
        assert(col < COL);
        for (size_t i = 0; i < ROW; ++i)
            mat[i][col] = a[i];
    }
    // 删去一行和一列
    inline Mat<ROW - 1, COL - 1, T> GetMinor(size_t row, size_t col) const
    {
        Mat<ROW - 1, COL - 1, T> res;
        for (size_t r = 0; r < ROW - 1; ++r)
        {
            for (size_t c = 0; c < COL - 1; ++c)
            {
                res.mat[r][c] = mat[r < row ? r : r + 1][c < col ? c : c + 1];
            }
        }
        return res;
    }
    // 取得转置矩阵
    inline Mat<COL, ROW, T> GetTranspose() const
    {
        Mat<COL, ROW, T> ret;
        for (size_t r = 0; r < ROW; ++r)
        {
            for (size_t c = 0; c < COL; ++c)
                ret.mat[c][r] = mat[r][c];
        }
        return ret;
    }

    // 取得 0 矩阵
    inline static Mat<ROW, COL, T> GetZero()
    {
        Mat<ROW, COL, T> ret;
        for (size_t r = 0; r < ROW; ++r)
        {
            for (size_t c = 0; c < COL; ++c)
                ret.mat[r][c] = 0;
        }
        return ret;
    }

    // 取得单位矩阵
    inline static Mat<ROW, COL, T> GetIdentity()
    {
        Mat<ROW, COL, T> ret;
        for (size_t r = 0; r < ROW; ++r)
        {
            for (size_t c = 0; c < COL; ++c)
                ret.mat[r][c] = (r == c) ? 1 : 0;
        }
        return ret;
    }
};

// 特化3x3的矩阵
template <typename T>
struct Mat<3, 3, T>
{
    union
    {
        struct
        {
            T e00, e01, e02;
            T e10, e11, e12;
            T e20, e21, e22;
        };
        T mat[3][3];
    };

    inline Mat()
    {
    }
    inline Mat(T e00, T e01, T e02,
               T e10, T e11, T e12,
               T e20, T e21, T e22)
    {
        mat[0][0] = e00, mat[0][1] = e01, mat[0][2] = e02,
        mat[1][0] = e10, mat[1][1] = e11, mat[1][2] = e12,
        mat[2][0] = e20, mat[2][1] = e21, mat[2][2] = e22;
    }
    inline Mat(const Mat<3, 3, T> &rhs)
    {
        for (size_t r = 0; r < 3; ++r)
        {
            for (size_t c = 0; c < 3; ++c)
                mat[r][c] = rhs.mat[r][c];
        }
    }
    // 给定列的initializer_list赋值
    inline Mat(const std::initializer_list<Vec<3, T>> &rhs)
    {
        auto it = rhs.begin();
        for (size_t i = 0; i < 3; ++i)
            SetRow(i, *it++);
    }

    inline const T *operator[](size_t row) const
    {
        assert(row < 3);
        return mat[row];
    }
    inline T *operator[](size_t row)
    {
        assert(row < 3);
        return mat[row];
    }

    // 取一行
    inline Vec<3, T> GetRow(size_t row) const
    {
        assert(row < 3);
        Vec<3, T> a;
        for (size_t i = 0; i < 3; ++i)
            a[i] = mat[row][i];
        return a;
    }

    // 取一列
    inline Vec<3, T> GetCol(size_t col) const
    {
        assert(col < 3);
        Vec<3, T> a;
        for (size_t i = 0; i < 3; ++i)
            a[i] = mat[i][col];
        return a;
    }

    // 设置一行
    inline void SetRow(size_t row, const Vec<3, T> &a)
    {
        assert(row < 3);
        for (size_t i = 0; i < 3; ++i)
            mat[row][i] = a[i];
    }

    // 设置一列
    inline void SetCol(size_t col, const Vec<3, T> &a)
    {
        assert(col < 3);
        for (size_t i = 0; i < 3; ++i)
            mat[i][col] = a[i];
    }
    // 删去一行和一列
    inline Mat<2, 2, T> GetMinor(size_t row, size_t col) const
    {
        Mat<2, 2, T> res;
        for (size_t r = 0; r < 2; ++r)
        {
            for (size_t c = 0; c < 2; ++c)
            {
                res.mat[r][c] = mat[r < row ? r : r + 1][c < col ? c : c + 1];
            }
        }
        return res;
    }
    // 取得转置矩阵
    inline Mat<3, 3, T> GetTranspose() const
    {
        Mat<3, 3, T> ret;
        for (size_t r = 0; r < 3; ++r)
        {
            for (size_t c = 0; c < 3; ++c)
                ret.mat[c][r] = mat[r][c];
        }
        return ret;
    }

    // 取得 0 矩阵
    inline static Mat<3, 3, T> GetZero()
    {
        Mat<3, 3, T> ret;
        for (size_t r = 0; r < 3; ++r)
        {
            for (size_t c = 0; c < 3; ++c)
                ret.mat[r][c] = 0;
        }
        return ret;
    }

    // 取得单位矩阵
    inline static Mat<3, 3, T> GetIdentity()
    {
        Mat<3, 3, T> ret;
        for (size_t r = 0; r < 3; ++r)
        {
            for (size_t c = 0; c < 3; ++c)
                ret.mat[r][c] = (r == c) ? 1 : 0;
        }
        return ret;
    }
};

template <typename T>
struct Mat<4, 4, T>
{
    union
    {
        struct
        {
            T e00, e01, e02, e03;
            T e10, e11, e12, e13;
            T e20, e21, e22, e23;
            T e30, e31, e32, e33;
        };
        T mat[4][4];
    };

    inline Mat()
    {
    }
    inline Mat(T e00, T e01, T e02, T e03,
               T e10, T e11, T e12, T e13,
               T e20, T e21, T e22, T e23,
               T e30, T e31, T e32, T e33)
    {
        mat[0][0] = e00, mat[0][1] = e01, mat[0][2] = e02, mat[0][3] = e03;
        mat[1][0] = e10, mat[1][1] = e11, mat[1][2] = e12, mat[1][3] = e13;
        mat[2][0] = e20, mat[2][1] = e21, mat[2][2] = e22, mat[2][3] = e23;
        mat[3][0] = e30, mat[3][1] = e31, mat[3][2] = e32, mat[3][3] = e33;
    }
    inline Mat(const Mat<4, 4, T> &rhs)
    {
        for (size_t r = 0; r < 4; ++r)
        {
            for (size_t c = 0; c < 4; ++c)
                mat[r][c] = rhs.mat[r][c];
        }
    }
    // 给定列的initializer_list赋值
    inline Mat(const std::initializer_list<Vec<4, T>> &rhs)
    {
        auto it = rhs.begin();
        for (size_t i = 0; i < 4; ++i)
            SetRow(i, *it++);
    }

    inline const T *operator[](size_t row) const
    {
        assert(row < 4);
        return mat[row];
    }
    inline T *operator[](size_t row)
    {
        assert(row < 4);
        return mat[row];
    }

    // 取一行
    inline Vec<4, T> GetRow(size_t row) const
    {
        assert(row < 4);
        Vec<4, T> a;
        for (size_t i = 0; i < 4; ++i)
            a[i] = mat[row][i];
        return a;
    }

    // 取一列
    inline Vec<4, T> GetCol(size_t col) const
    {
        assert(col < 4);
        Vec<4, T> a;
        for (size_t i = 0; i < 4; ++i)
            a[i] = mat[i][col];
        return a;
    }

    // 设置一行
    inline void SetRow(size_t row, const Vec<4, T> &a)
    {
        assert(row < 4);
        for (size_t i = 0; i < 4; ++i)
            mat[row][i] = a[i];
    }

    // 设置一列
    inline void SetCol(size_t col, const Vec<4, T> &a)
    {
        assert(col < 4);
        for (size_t i = 0; i < 4; ++i)
            mat[i][col] = a[i];
    }
    // 删去一行和一列
    inline Mat<3, 3, T> GetMinor(size_t row, size_t col) const
    {
        Mat<3, 3, T> res;
        for (size_t r = 0; r < 3; ++r)
        {
            for (size_t c = 0; c < 3; ++c)
            {
                res.mat[r][c] = mat[r < row ? r : r + 1][c < col ? c : c + 1];
            }
        }
        return res;
    }
    // 取得转置矩阵
    inline Mat<4, 4, T> GetTranspose() const
    {
        Mat<4, 4, T> ret;
        for (size_t r = 0; r < 4; ++r)
        {
            for (size_t c = 0; c < 4; ++c)
                ret.mat[c][r] = mat[r][c];
        }
        return ret;
    }

    // 取得 0 矩阵
    inline static Mat<4, 4, T> GetZero()
    {
        Mat<4, 4, T> ret;
        for (size_t r = 0; r < 4; ++r)
        {
            for (size_t c = 0; c < 4; ++c)
                ret.mat[r][c] = 0;
        }
        return ret;
    }

    // 取得单位矩阵
    inline static Mat<4, 4, T> GetIdentity()
    {
        Mat<4, 4, T> ret;
        for (size_t r = 0; r < 4; ++r)
        {
            for (size_t c = 0; c < 4; ++c)
                ret.mat[r][c] = (r == c) ? 1 : 0;
        }
        return ret;
    }
};
template <size_t ROW, size_t COL, typename T>
inline bool operator==(const Mat<ROW, COL, T> &a, const Mat<ROW, COL, T> &b)
{
    for (size_t r = 0; r < ROW; ++r)
    {
        for (size_t c = 0; c < COL; ++c)
        {
            if (a.mat[r][c] != b.mat[r][c])
                return false;
        }
    }
    return true;
}

template <size_t ROW, size_t COL, typename T>
inline bool operator!=(const Mat<ROW, COL, T> &a, const Mat<ROW, COL, T> &b)
{
    return !(a == b);
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> operator+(const Mat<ROW, COL, T> &a)
{
    return a;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> operator-(const Mat<ROW, COL, T> &a)
{
    Mat<ROW, COL, T> out;
    for (size_t r = 0; r < ROW; ++r)
    {
        for (size_t c = 0; c < COL; ++c)
            out.mat[r][c] = -a.mat[r][c];
    }
    return out;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> operator+(const Mat<ROW, COL, T> &a, const Mat<ROW, COL, T> &b)
{
    Mat<ROW, COL, T> out;
    for (size_t r = 0; r < ROW; ++r)
    {
        for (size_t c = 0; c < COL; ++c)
            out.mat[r][c] = a.mat[r][c] + b.mat[r][c];
    }
    return out;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> operator-(const Mat<ROW, COL, T> &a, const Mat<ROW, COL, T> &b)
{
    Mat<ROW, COL, T> out;
    for (size_t r = 0; r < ROW; ++r)
    {
        for (size_t c = 0; c < COL; ++c)
            out.mat[r][c] = a.mat[r][c] - b.mat[r][c];
    }
    return out;
}

template <size_t ROW, size_t COL, size_t NEWCOL, typename T>
inline Mat<ROW, NEWCOL, T> operator*(const Mat<ROW, COL, T> &a, const Mat<COL, NEWCOL, T> &b)
{
    Mat<ROW, NEWCOL, T> out;
    for (size_t r = 0; r < ROW; ++r)
    {
        for (size_t c = 0; c < NEWCOL; ++c)
        {
            out.mat[r][c] = VecGetDotProduct(a.GetRow(r), b.GetCol(c));
        }
    }
    return out;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> operator*(const Mat<ROW, COL, T> &a, T x)
{
    Mat<ROW, COL, T> out;
    for (size_t r = 0; r < ROW; r++)
    {
        for (size_t c = 0; c < COL; c++)
        {
            out.mat[r][c] = a.mat[r][c] * x;
        }
    }
    return out;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> operator/(const Mat<ROW, COL, T> &a, T x)
{
    assert(x != 0);
    Mat<ROW, COL, T> out;
    for (size_t r = 0; r < ROW; r++)
    {
        for (size_t c = 0; c < COL; c++)
        {
            out.mat[r][c] = a.mat[r][c] / x;
        }
    }
    return out;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> operator*(T x, const Mat<ROW, COL, T> &a)
{
    return (a * x);
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> operator/(T x, const Mat<ROW, COL, T> &a)
{
    Mat<ROW, COL, T> out;
    for (size_t r = 0; r < ROW; r++)
    {
        for (size_t c = 0; c < COL; c++)
        {
            out.mat[r][c] = x / a.mat[r][c];
        }
    }
    return out;
}

template <size_t ROW, size_t COL, typename T>
inline Vec<ROW, T> operator*(const Vec<ROW, T> &a, const Mat<ROW, COL, T> &b)
{
    Vec<ROW, T> out;
    for (size_t i = 0; i < COL; ++i)
    {
        out[i] = VecGetDotProduct(a, b.GetCol(i));
    }
    return out;
}

template <size_t ROW, size_t COL, typename T>
inline Vec<ROW, T> operator*(const Mat<ROW, COL, T> &a, const Vec<COL, T> &b)
{
    Vec<ROW, T> out;
    for (size_t i = 0; i < ROW; ++i)
    {
        out[i] = VecGetDotProduct(a.GetRow(i), b);
    }
    return out;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> &operator+=(Mat<ROW, COL, T> &a, Mat<ROW, COL, T> &b)
{
    // Mat<ROW, COL, T> out;
    for (size_t r = 0; r < ROW; ++r)
    {
        for (size_t c = 0; c < COL; ++c)
            a.mat[r][c] += b.mat[r][c];
    }
    // a = out;
    return a;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> &operator-=(Mat<ROW, COL, T> &a, Mat<ROW, COL, T> &b)
{
    // Mat<ROW, COL, T> out;
    for (size_t r = 0; r < ROW; ++r)
    {
        for (size_t c = 0; c < COL; ++c)
            a.mat[r][c] -= b.mat[r][c];
    }
    // a = out;
    return a;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> &operator*=(Mat<ROW, COL, T> &a, Mat<COL, COL, T> &b)
{
    Mat<ROW, COL, T> out;
    for (size_t r = 0; r < ROW; ++r)
    {
        for (size_t c = 0; c < COL; ++c)
        {
            out.mat[r][c] = VecGetDotProduct(a.GetRow(r), b.GetCol(c));
        }
    }
    for (size_t r = 0; r < ROW; ++r)
    {
        for (size_t c = 0; c < COL; ++c)
        {
            a.mat[r][c] = out.mat[r][c];
        }
    }
    return a;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> &operator*=(Mat<ROW, COL, T> &a, T x)
{
    for (size_t r = 0; r < ROW; r++)
    {
        for (size_t c = 0; c < COL; c++)
        {
            a.mat[r][c] *= x;
        }
    }
    return a;
}

template <size_t ROW, size_t COL, typename T>
inline Mat<ROW, COL, T> &operator/=(Mat<ROW, COL, T> &a, T x)
{
    assert(x != 0);
    for (size_t r = 0; r < ROW; r++)
    {
        for (size_t c = 0; c < COL; c++)
        {
            a.mat[r][c] /= x;
        }
    }
    return a;
}

// 定义一个辅助函数来比较两个矩阵的每个元素
template <int Rows, int Cols, typename T>
bool MatNear(const Mat<Rows, Cols, T> &mat1, const Mat<Rows, Cols, T> &mat2, T epsilon = 0.000001f)
{
    for (int i = 0; i < Rows; ++i)
    {
        for (int j = 0; j < Cols; ++j)
        {
            if (std::fabs(mat1.mat[i][j] - mat2.mat[i][j]) > epsilon)
            {
                return false;
            }
        }
    }
    return true;
}

template <size_t ROW, size_t COL, typename T>
inline std::ostream &operator<<(std::ostream &os, const Mat<ROW, COL, T> &mat)
{

    for (size_t r = 0; r < ROW; ++r)
    {
        os << "[";
        for (size_t c = 0; c < COL; ++c)
        {
            os << mat.mat[r][c] << " ";
        }
        os << "]" << std::endl;
    }
    return os;
}

// 行列式求值：一阶
template <typename T>
inline T MatGetDet(const Mat<1, 1, T> &m)
{
    return m[0][0];
}

// 行列式求值：二阶
template <typename T>
inline T MatGetDet(const Mat<2, 2, T> &m)
{
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

// 行列式求值：多阶行列式，即第一行同他们的余子式相乘求和
template <size_t N, typename T>
inline T MatGetDet(const Mat<N, N, T> &m)
{
    T sum = 0;
    for (size_t i = 0; i < N; i++)
        sum += m[0][i] * MatGetCofactor(m, 0, i);
    return sum;
}

// 余子式：一阶
template <typename T>
inline T MatGetCofactor(const Mat<1, 1, T> &m, size_t row, size_t col)
{
    return 0;
}

// 多阶余子式：即删除特定行列的子式的行列式值
template <size_t N, typename T>
inline T MatGetCofactor(const Mat<N, N, T> &m, size_t row, size_t col)
{
    return MatGetDet(m.GetMinor(row, col)) * (((row + col) % 2) ? -1 : 1);
}

// 伴随矩阵：即余子式矩阵的转置
template <size_t N, typename T>
inline Mat<N, N, T> MatGetAdjoint(const Mat<N, N, T> &m)
{
    Mat<N, N, T> ret;
    for (size_t j = 0; j < N; j++)
    {
        for (size_t i = 0; i < N; i++)
            ret[j][i] = MatGetCofactor(m, i, j);
    }
    return ret;
}

// 求逆矩阵：使用伴随矩阵除以行列式的值得到
template <size_t N, typename T>
inline Mat<N, N, T> MatGetInverse(const Mat<N, N, T> &m)
{
    Mat<N, N, T> ret = MatGetAdjoint(m);
    T det = VecGetDotProduct(m.GetRow(0), ret.GetCol(0));
    return ret / det;
}

typedef Mat<3, 3, float> Mat3x3f;
typedef Mat<4, 4, float> Mat4x4f;

inline static Mat4x4f Mat4x4GetTranslate(const Vec3f &a)
{
    Mat4x4f res = Mat4x4f::GetIdentity();
    res.mat[0][3] = a[0];
    res.mat[1][3] = a[1];
    res.mat[2][3] = a[2];
    return res;
}

inline static Mat4x4f Mat4x4GetScale(const Vec3f &a)
{
    Mat4x4f res = Mat4x4f::GetIdentity();
    res.mat[0][0] = a[0];
    res.mat[1][1] = a[1];
    res.mat[2][2] = a[2];
    return res;
}

inline static Mat4x4f Mat4x4GetXRotation(const float angle)
{
    Mat4x4f res = Mat4x4f::GetIdentity();
    res.mat[1][1] = cos(angle);
    res.mat[1][2] = sin(angle);
    res.mat[2][1] = -sin(angle);
    res.mat[2][2] = cos(angle);
    return res;
}

inline static Mat4x4f Mat4x4GetYRotation(const float angle)
{
    Mat4x4f res = Mat4x4f::GetIdentity();
    res.mat[0][0] = cos(angle);
    res.mat[0][2] = -sin(angle);
    res.mat[2][0] = sin(angle);
    res.mat[2][2] = cos(angle);
    return res;
}

inline static Mat4x4f Mat4x4GetZRotation(const float angle)
{
    Mat4x4f res = Mat4x4f::GetIdentity();
    res.mat[0][0] = cos(angle);
    res.mat[0][1] = sin(angle);
    res.mat[1][0] = -sin(angle);
    res.mat[1][1] = cos(angle);
    return res;
}

inline static Mat4x4f Mat4x4GetRotation(const Vec3f &a, const float angle)
{
    // 使用了四元数的乘法，这里使用的是行主序
    Mat4x4f res = Mat4x4f::GetIdentity();
    float qsin = (float)sin(angle * 0.5f);
    float qcos = (float)cos(angle * 0.5f);
    float w = qcos;
    Vec3f vec = VecGetNormalize(a);
    float x = vec.x * qsin;
    float y = vec.y * qsin;
    float z = vec.z * qsin;

    res.mat[0][0] = 1 - 2 * y * y - 2 * z * z;
    res.mat[1][0] = 2 * x * y - 2 * w * z;
    res.mat[2][0] = 2 * x * z + 2 * w * y;
    res.mat[0][1] = 2 * x * y + 2 * w * z;
    res.mat[1][1] = 1 - 2 * x * x - 2 * z * z;
    res.mat[2][1] = 2 * y * z - 2 * w * x;
    res.mat[0][2] = 2 * x * z - 2 * w * y;
    res.mat[1][2] = 2 * y * z + 2 * w * x;
    res.mat[2][2] = 1 - 2 * x * x - 2 * y * y;
    return res;
}

// fovy传入的应该是一个弧度
inline static Mat4x4f Mat4x4GetPerspective(const float fovy, const float aspect, const float zNear, const float zFar)
{
    float rFovy = fovy * M_PI / 180;
    const float tanHalfFovy = tanf(static_cast<float>(rFovy * 0.5f));
    Mat4x4f res(
        1.0f / (aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f / tanHalfFovy, 0.0f, 0.0f,
        0.0f, 0.0f, -(zFar + zNear) / (zFar - zNear), -(2.0f * zFar * zNear) / (zFar - zNear),
        0.0f, 0.0f, -1.0f, 0.0f);

    /* Mat4x4f res = Mat4x4f::GetIdentity();
    res.mat[0][0] = 1 / (aspect * tan(fovy * 0.5f));
    res.mat[1][1] = 1 / tan(fovy * 0.5f);
    res.mat[2][2] = -(zFar + zNear) / (zFar - zNear);
    res.mat[3][2] = -1;
    res.mat[2][3] = -(2 * zFar * zNear) / (zFar - zNear); */
    return res;
}

inline static Mat4x4f Mat4x4GetOrtho(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar)
{

    Mat4x4f res(
        2.0f / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / (zFar - zNear), -(zFar + zNear) / (zFar - zNear),
        0.0f, 0.0f, 0.0f, 1.0f);

    /* Mat4x4f res = Mat4x4f::GetIdentity();
    res.mat[0][0] = 2 / (right - left);
    res.mat[1][1] = 2 / (top - bottom);
    res.mat[2][2] = -2 / (zFar - zNear);
    res.mat[0][3] = -(right + left) / (right - left);//其实是0.0f
    res.mat[1][3] = -(top + bottom) / (top - bottom);//其实是0.0f
    res.mat[2][3] = -(zFar + zNear) / (zFar - zNear); */
    return res;
}
inline static Mat4x4f Mat4x4GetLookAt(const Vec3f &eye, const Vec3f &target, const Vec3f &up)
{

    Vec3f Z = VecGetNormalize(eye - target);
    Vec3f X = VecGetNormalize(VecGetCrossProduct(up, Z));
    Vec3f Y = VecGetNormalize(VecGetCrossProduct(Z, X));
    Mat4x4f res(
        X.x, X.y, X.z, -VecGetDotProduct(X, eye),
        Y.x, Y.y, Y.z, -VecGetDotProduct(Y, eye),
        Z.x, Z.y, Z.z, -VecGetDotProduct(Z, eye),
        0.0f, 0.0f, 0.0f, 1.0f);
    /* Mat4x4f res(
        X.x, X.y, X.z, -target.x,
        Y.x, Y.y, Y.z, -target.y,
        Z.x, Z.y, Z.z, -target.z,
        0.0f, 0.0f, 0.0f, 1.0f); */
    /* Mat4x4f res(
        X.x, X.y, X.z, -VecGetDotProduct(X, target),
        Y.x, Y.y, Y.z, -VecGetDotProduct(Y, target),
        Z.x, Z.y, Z.z, -VecGetDotProduct(Z, target),
        0.0f, 0.0f, 0.0f, 1.0f); */
    /* Mat4x4f res = Mat4x4f::GetIdentity();
    res.mat[0][0] = X.x;
    res.mat[0][1] = X.y;
    res.mat[0][2] = X.z;
    res.mat[1][0] = Y.x;
    res.mat[1][1] = Y.y;
    res.mat[1][2] = Y.z;
    res.mat[2][0] = Z.x;
    res.mat[2][1] = Z.y;
    res.mat[2][2] = Z.z;
    res.mat[0][3] = -VecGetDotProduct(X, eye);
    res.mat[1][3] = -VecGetDotProduct(Y, eye);
    res.mat[2][3] = -VecGetDotProduct(Z, eye); */
    return res;
}

inline static Mat4x4f Mat4x4GetViewport(float left, float bottom, float width, float height)
{
    Mat4x4f res(
        width * 0.5f, 0.0f, 0.0f, left + width * 0.5f,
        0.0f, -height * 0.5f, 0.0f, bottom + height * 0.5f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    /* Mat4x4f res = Mat4x4f::GetIdentity();
    res.mat[0][0] = width * 0.5f;
    res.mat[1][1] = height * 0.5f;
    res.mat[0][3] = left + width * 0.5f;
    res.mat[1][3] = bottom + height * 0.5f; */
    return res; // z坐标不需要管，投影到屏幕上，这里认为视口的坐标原点位于左下角
}

inline static Mat4x4f Mat4x4GetViewportNaive(float left, float bottom, float width, float height, float depthScale)
{
    Mat4x4f res(
        width * 0.5f, 0.0f, 0.0f, left + width * 0.5f,
        0.0f, height * 0.5f, 0.0f, bottom + height * 0.5f,
        0.0f, 0.0f, depthScale * 0.5f, depthScale * 0.5f,
        0.0f, 0.0f, 0.0f, 1.0f);
    return res;
}

inline static Mat4x4f Mat4x4GetProjectionNaive(float cameraZ)
{
    Mat4x4f res(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -1.0f / cameraZ, 1.0f);
    return res;
}

inline static Mat4x4f Mat4x4GetProjectionNaive(const Vec3f &eye, const Vec3f &center)
{
    Mat4x4f res(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -1.0f / VecGetLength(eye - center), 1.0f);
    return res;
}

#endif