#ifndef MODEL_H
#define MODEL_H
#include "Math/MathGroup.h"
#include <vector>
#include <string>
#include "Texture2D.h"
#include "Mesh.h"

// 单个顶点的属性

class Model : public Mesh
{

public:
    Model(const std::string &path);
    virtual ~Model();
    Mat4x4 SetSize(float sx, float sy, float sz) const;
    // Model &operator=(const Model &model);
    void loadObjModel(const std::string &path);

    /* public:
        vector<Vec3> m_Vertices;
        vector<Vec2> m_UVCoords;
        vector<Vec3> m_Normals;

        vector<vector<Vec3>> m_Faces; */

private:
    Vec3 minPoint, maxPoint;
};

#endif // MODEL_H