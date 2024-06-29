#ifndef MODEL_H
#define MODEL_H
#include "Math/Vec.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
using std::map;
using std::string;
using std::unordered_map;
using std::vector;
// 单个顶点的属性

struct Vertex
{
    /* map<string, Vec4f> varingV4f;
    map<string, Vec3f> varingV3f;
    map<string, Vec2f> varingV2f;
    map<string, float> varingV1f; */
    vector<Vec4f> varingV4f;
    vector<Vec3f> varingV3f;
    vector<Vec2f> varingV2f;
    vector<float> varingV1f;
    map<string, int> varingIndMap;
    template <typename T>
    inline T &get(const string &name)
    {
        /* Accessor<T> accessor(*this);
        return accessor[name]; */
        if constexpr (std::is_same_v<T, float>)
        {
            if (varingIndMap.count(name) == 0)
            {
                printf("source file name:%s, the line is:%d\n", __FILE__, __LINE__);
                assert(0 == 1);
            }
            /* return varingV1f[name]; */
            return varingV1f[varingIndMap[name]];
        }
        else if constexpr (std::is_same_v<T, Vec2f>)
        {
            if (varingIndMap.count(name) == 0)
            {
                printf("source file name:%s, the line is:%d\n", __FILE__, __LINE__);
                assert(0 == 1);
            }
            /* return varingV2f[name]; */
            return varingV2f[varingIndMap[name]];
        }
        else if constexpr (std::is_same_v<T, Vec3f>)
        {
            if (varingIndMap.count(name) == 0)
            {
                printf("source file name:%s, the line is:%d\n", __FILE__, __LINE__);
                assert(0 == 1);
            }
            /* return varingV3f[name]; */
            return varingV3f[varingIndMap[name]];
        }
        else if constexpr (std::is_same_v<T, Vec4f>)
        {
            if (varingIndMap.count(name) == 0)
            {
                printf("source file name:%s, the line is:%d\n", __FILE__, __LINE__);
                assert(0 == 1);
            }
            /* return varingV4f[name]; */
            return varingV4f[varingIndMap[name]];
        }
        else
        {
            cout << "invalid vertex attribute " << name << endl;
            assert(false);
        }
    }
    template <typename T>
    inline void set(const string &name, T value)
    {
        /* Accessor<T> accessor(*this);
        accessor[name] = value; */
        if constexpr (std::is_same_v<T, float>)
        {

            /* varingV1f[name] = value; */

            varingV1f.emplace_back(value);
            varingIndMap[name] = varingV1f.size() - 1;
        }
        else if constexpr (std::is_same_v<T, Vec2f>)
        {

            /* varingV2f[name] = value; */
            varingV2f.emplace_back(value);
            varingIndMap[name] = varingV2f.size() - 1;
        }
        else if constexpr (std::is_same_v<T, Vec3f>)
        {

            /* varingV3f[name] = value; */
            varingV3f.emplace_back(value);
            varingIndMap[name] = varingV3f.size() - 1;
        }
        else if constexpr (std::is_same_v<T, Vec4f>)
        {
            /* varingV4f[name] = value; */
            varingV4f.emplace_back(value);
            varingIndMap[name] = varingV4f.size() - 1;
        }
        else
        {
            cout << "invalid vertex attribute " << name << endl;
            assert(false);
        }
    }
};

class Model
{

public:
    Model(const char *filename);
    ~Model() = default;
    Model(const Model &model);
    Model &operator=(const Model &model);
    void loadObjModel(const char *filename);

public:
    vector<Vec3f> m_Vertices;
    vector<Vec2f> m_UVCoords;
    vector<Vec3f> m_Normals;

    vector<vector<Vec3i>> m_Faces;
};

#endif // MODEL_H