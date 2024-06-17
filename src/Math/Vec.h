#ifndef VEC_H
#define VEC_H
#include <initializer_list>
#include <cmath>
#include <cassert>
#include <iostream>
/**************************************************/
/******************1. 矢量定义**********************/
/**************************************************/

// 通用矢量，N为矢量维度，T为数据类型
template <size_t N, typename T>
struct Vec
{
    T vec[N]; // 固定大小的向量，使用C语言的数组来保存
    inline Vec()
    {
        for (size_t i = 0; i < N; ++i)
            vec[i] = T();
    }
    inline Vec(const T *ptr) // 使用数组赋值
    {
        for (size_t i = 0; i < N; ++i)
            vec[i] = ptr[i];
    }
    inline Vec(const Vec<N, T> &rhs)
    {
        for (size_t i = 0; i < N; ++i)
            vec[i] = rhs.vec[i];
    }
    inline Vec(const std::initializer_list<T> &u)
    {
        auto it = u.begin();
        for (size_t i = 0; i < N; ++i)
            vec[i] = *it++;
    }
    inline const T &operator[](size_t i) const
    {
        assert(i < N);
        return vec[i];
    }
    inline T &operator[](size_t i)
    {
        assert(i < N);
        return vec[i];
    }
};

// 特化二维矢量
template <typename T>
struct Vec<2, T>
{
    union
    {
        struct
        {
            T x, y;
        };
        struct
        {
            T u, v;
        };
        T vec[2];
    };
    inline Vec() : x(T()), y(T()) {}
    inline Vec(T X, T Y) : x(X), y(Y) {}
    inline Vec(const Vec<2, T> &rhs) : x(rhs.x), y(rhs.y) {}
    inline Vec(const T *ptr) : x(ptr[0]), y(ptr[1]) {}
    inline const T &operator[](size_t i) const
    {
        assert(i < 2);
        return vec[i];
    }
    inline T &operator[](size_t i)
    {
        assert(i < 2);
        return vec[i];
    }
    // void load
    // void save
};

// 特化三维矢量
template <typename T>
struct Vec<3, T>
{
    union
    {
        struct
        {
            T x, y, z;
        };
        struct
        {
            T r, g, b;
        };
        struct
        {
            T u, v, w;
        };
        T vec[3];
    };
    inline Vec() : x(T()), y(T()), z(T()) {}
    inline Vec(T X, T Y, T Z) : x(X), y(Y), z(Z) {}
    inline Vec(const Vec<3, T> &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
    inline Vec(const T *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}
    inline const T &operator[](size_t i) const
    {
        assert(i < 3);
        return vec[i];
    }
    inline T &operator[](size_t i)
    {
        assert(i < 3);
        return vec[i];
    }
};

// 特化四维矢量
template <typename T>
struct Vec<4, T>
{
    union
    {
        struct
        {
            T x, y, z, w;
        };
        struct
        {
            T r, g, b, a;
        };
        T vec[4];
    };
    inline Vec() : x(T()), y(T()), z(T()), w(T()) {}
    inline Vec(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}
    inline Vec(const Vec<4, T> &rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
    inline Vec(const T *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]), w(ptr[3]) {}
    inline const T &operator[](size_t i) const
    {
        assert(i < 4);
        return vec[i];
    }
    inline T &operator[](size_t i)
    {
        assert(i < 4);
        return vec[i];
    }
};
typedef Vec<2, float> Vec2f;
typedef Vec<3, float> Vec3f;
typedef Vec<4, float> Vec4f;
typedef Vec<2, int> Vec2i;
typedef Vec<3, int> Vec3i;

/**************************************************/
/******************2. 矢量运算**********************/
/**************************************************/
// (+a)
template <size_t N, typename T>
inline Vec<N, T> operator+(const Vec<N, T> &a)
{
    return a;
}

// (-a)
template <size_t N, typename T>
inline Vec<N, T> operator-(const Vec<N, T> &a)
{
    Vec<N, T> b;
    for (size_t i = 0; i < N; ++i)
        b[i] = -a[i];
    return b;
}

// (a == b) ? true : false
template <size_t N, typename T>
inline bool operator==(const Vec<N, T> &a, const Vec<N, T> &b)
{
    for (size_t i = 0; i < N; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}

// (a != b) ? true : false
template <size_t N, typename T>
inline bool operator!=(const Vec<N, T> &a, const Vec<N, T> &b)
{
    return !(a == b);
}

// (a + b)
template <size_t N, typename T>
inline Vec<N, T> operator+(const Vec<N, T> &a, const Vec<N, T> &b)
{
    Vec<N, T> c;
    for (size_t i = 0; i < N; ++i)
        c[i] = a[i] + b[i];
    return c;
}

// (a - b)
template <size_t N, typename T>
inline Vec<N, T> operator-(const Vec<N, T> &a, const Vec<N, T> &b)
{
    Vec<N, T> c;
    for (size_t i = 0; i < N; ++i)
        c[i] = a[i] - b[i];
    return c;
}

// (a * b) 各个元素相乘，H积
template <size_t N, typename T>
inline Vec<N, T> operator*(const Vec<N, T> &a, const Vec<N, T> &b)
{
    Vec<N, T> c;
    for (size_t i = 0; i < N; ++i)
        c[i] = a[i] * b[i];
    return c;
}

// (a / b) 各个元素相除
template <size_t N, typename T>
inline Vec<N, T> operator/(const Vec<N, T> &a, const Vec<N, T> &b)
{
    Vec<N, T> c;
    for (size_t i = 0; i < N; ++i)
    {
        assert(b[i] != 0);
        c[i] = a[i] / b[i];
    }
    return c;
}

// (a * x)
template <size_t N, typename T>
inline Vec<N, T> operator*(const Vec<N, T> &a, T x)
{
    Vec<N, T> b;
    for (size_t i = 0; i < N; ++i)
        b[i] = a[i] * x;
    return b;
}

// (a * x)
template <size_t N, typename T1, typename T2>
inline Vec<N, T1> operator*(const Vec<N, T1> &a, T2 x)
{
    Vec<N, T1> b;
    for (size_t i = 0; i < N; ++i)
        b[i] = a[i] * x;
    return b;
}

// (x * a)
template <size_t N, typename T>
inline Vec<N, T> operator*(T x, const Vec<N, T> &a)
{
    Vec<N, T> b;
    for (size_t i = 0; i < N; ++i)
        b[i] = a[i] * x;
    return b;
}

// (x * a)
template <size_t N, typename T1, typename T2>
inline Vec<N, T1> operator*(T2 x, const Vec<N, T1> &a)
{
    Vec<N, T1> b;
    for (size_t i = 0; i < N; ++i)
        b[i] = a[i] * x;
    return b;
}

// (a / x)
template <size_t N, typename T>
inline Vec<N, T> operator/(const Vec<N, T> &a, T x)
{
    assert(x != 0);
    Vec<N, T> b;
    for (size_t i = 0; i < N; ++i)
        b[i] = a[i] / x;
    return b;
}

// (x / a)
template <size_t N, typename T>
inline Vec<N, T> operator/(T x, const Vec<N, T> &a)
{
    Vec<N, T> b;
    for (size_t i = 0; i < N; ++i)
    {
        assert(a[i] != 0);
        b[i] = x / a[i];
    }

    return b;
}

// a += b
template <size_t N, typename T>
inline Vec<N, T> &operator+=(Vec<N, T> &a, const Vec<N, T> &b)
{
    for (size_t i = 0; i < N; ++i)
        a[i] += b[i];
    return a;
}

// a -= b
template <size_t N, typename T>
inline Vec<N, T> &operator-=(Vec<N, T> &a, const Vec<N, T> &b)
{
    for (size_t i = 0; i < N; ++i)
        a[i] -= b[i];
    return a;
}

// a *= b
template <size_t N, typename T>
inline Vec<N, T> &operator*=(Vec<N, T> &a, const Vec<N, T> &b)
{
    for (size_t i = 0; i < N; ++i)
        a[i] *= b[i];
    return a;
}

// a /= b
template <size_t N, typename T>
inline Vec<N, T> &operator/=(Vec<N, T> &a, const Vec<N, T> &b)
{
    for (size_t i = 0; i < N; ++i)
        a[i] /= b[i];
    return a;
}

// a *= x
template <size_t N, typename T>
inline Vec<N, T> operator*=(Vec<N, T> &a, T x)
{
    for (size_t i = 0; i < N; ++i)
        a[i] *= x;
    return a;
}

// a /= x
template <size_t N, typename T>
inline Vec<N, T> operator/=(Vec<N, T> &a, T x)
{
    assert(x != 0);
    for (size_t i = 0; i < N; ++i)
        a[i] /= x;
    return a;
}

// |a| ^ 2
template <size_t N, typename T>
inline T VecGetLengthSquare(const Vec<N, T> &a)
{
    T sum = 0;
    for (size_t i = 0; i < N; ++i)
        sum += a[i] * a[i];
    return sum;
}

// |a|
template <size_t N, typename T>
inline T VecGetLength(const Vec<N, T> &a)
{
    return sqrt(VecGetLengthSquare(a));
}

// 矢量点乘
template <size_t N, typename T>
inline T VecGetDotProduct(const Vec<N, T> &a, const Vec<N, T> &b)
{
    T sum = 0;
    for (size_t i = 0; i < N; ++i)
    {
        sum += a[i] * b[i];
    }
    return sum;
}

// 二维矢量叉乘，得到标量
template <typename T>
inline T VecGetCrossProduct(const Vec<2, T> &a, const Vec<2, T> &b)
{
    return a.x * b.y - a.y * b.x;
}

// 三维矢量叉乘，得到新矢量
template <typename T>
inline Vec<3, T> VecGetCrossProduct(const Vec<3, T> &a, const Vec<3, T> &b)
{
    return Vec<3, T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// 四维矢量叉乘：前三维叉乘，后一位保留
template <typename T>
inline Vec<4, T> VecGetCrossProduct(const Vec<4, T> &a, const Vec<4, T> &b)
{
    return Vec<4, T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, a.w);
}

// 插值 a + (b - a) * t
template <size_t N, typename T>
inline Vec<N, T> VecGetLinearLerp(const Vec<N, T> &a, const Vec<N, T> &b, float t)
{
    return a * t + b * (1 - t);
}

// a / |a|
template <size_t N, typename T>
inline Vec<N, T> VecGetNormalize(const Vec<N, T> &a)
{
    return a / VecGetLength(a);
}

// 判断矢量是否接近
template <size_t N, typename T>
inline bool VecIsNear(const Vec<N, T> &a, const Vec<N, T> &b, T dist)
{
    return (VecGetLengthSquare(a - b) <= dist);
}

// 特化：判断两个单精度矢量是否近似
template <size_t N>
inline bool VecIsNearEqual(const Vec<N, float> &a, const Vec<N, float> &b, float e = 0.0001)
{
    return VecIsNear(a, b, e);
}

// 特化：判断两个双精度矢量是否近似
template <size_t N>
inline bool VecIsNearEqual(const Vec<N, double> &a, const Vec<N, double> &b, double e = 0.0000001)
{
    return VecIsNear(a, b, e);
}

// 打印调试
template <size_t N, typename T>
inline std::ostream &operator<<(std::ostream &out, const Vec<N, T> &v)
{
    out << "(";
    for (size_t i = 0; i < N; ++i)
    {
        out << v[i];
        if (i != N - 1)
            out << ", ";
    }
    out << ")";
    return out;
}

inline Vec3f VecGetBaryCentric(Vec3f &A, Vec3f &B, Vec3f &C, Vec3f &P)
{
    /* P = (1-u-v)*A + u*B + v*C */
    /* calculate [AB_x, AC_x, PA_x] and [AB_y, AC_y, PA_y] */
    Vec3f vx(B.x - A.x, C.x - A.x, A.x - P.x);
    Vec3f vy(B.y - A.y, C.y - A.y, A.y - P.y);
    /*the cross of vx & vy should be k[u, v, 1]*/
    Vec3f vCross(VecGetCrossProduct(vx, vy));
    /* if AB_x / AC_x == AB_y / AC_y  then the cross(vx, vy).z = 0*/
    if (std::abs(vCross.z) > 1e-2)
        return Vec3f(1.0f - (vCross.x + vCross.y) / vCross.z, vCross.x / vCross.z, vCross.y / vCross.z);
    /* 点在线上怎么办 */
    return Vec3f(-1.0f, 1.0f, 1.0f);
}

template <size_t N, typename T>
inline Vec<N, T> VecGetMax2(const Vec<N, T> &v1, const Vec<N, T> &v2)
{
    Vec<N, T> res;
    for (size_t i = 0; i < N; ++i)
    {
        res[i] = (v1[i] > v2[i]) ? v1[i] : v2[i];
    }
    return res;
}

template <size_t N, typename T>
inline Vec<N, T> VecGetMin2(const Vec<N, T> &v1, const Vec<N, T> &v2)
{
    Vec<N, T> res;
    for (size_t i = 0; i < N; ++i)
    {
        res[i] = (v1[i] < v2[i]) ? v1[i] : v2[i];
    }
    return res;
}

template <size_t N, typename T>
inline Vec<N, T> VecGetBetween(const Vec<N, T> &v, const Vec<N, T> &vmin, const Vec<N, T> &vmax)
{
    return VecGetMin2(VecGetMax2(v, vmin), vmax);
}

template <size_t N, typename T>
inline Vec<N, T> VecGetClamp(const Vec<N, T> &v, T minx = 0, T maxx = 1)
{
    Vec<N, T> res;
    for (size_t i = 0; i < N; ++i)
    {
        res[i] = (v[i] < minx) ? minx : (v[i] > maxx) ? maxx
                                                      : v[i];
    }
    return res;
}
#endif // VEC_H