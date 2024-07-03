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