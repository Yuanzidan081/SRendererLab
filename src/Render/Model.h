#ifndef MODEL_H
#define MODEL_H
#include "Math/MathGroup.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include "Texture2D.h"
#include "Mesh.h"
using std::map;
using std::string;
using std::unordered_map;
using std::vector;
// 单个顶点的属性

class Model
{

public:
    Model(const char *filename);
    ~Model();
    Model(const Model &model);
    Model &operator=(const Model &model);
    void loadObjModel(const char *filename);
    void SetDiffuse(const char *diffuseFileName);
    void SetNormal(const char *normalFileName);
    void SetSpecular(const char *specularFileName);
    Vec4 GetDiffuseColor(Vec2 &uv);
    Vec4 GetNormalColor(Vec2 &uv);

    float GetSpecularColor(Vec2 &uv);

public:
    vector<Vec3> m_Vertices;
    vector<Vec2> m_UVCoords;
    vector<Vec3> m_Normals;

    vector<vector<Vec3>> m_Faces;
    Texture2D *m_diffuseTexture;
    Texture2D *m_normalTexture;
    Texture2D *m_specularTexture;
};

#endif // MODEL_H