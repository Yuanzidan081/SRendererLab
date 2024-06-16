#ifndef MODEL_H
#define MODEL_H
#include "Math/Vec.h"
#include <vector>
#include <string>
class Model
{

public:
    Model(char const *filename);
    ~Model() = default;
    void loadModel(const char *filename);

    void loadObjModel(const char *filename);
    Vec3f GetVetices(int i) { return m_Vetices[i]; }
    std::vector<int> GetIndices(int i) { return m_Indices[i]; }
    int GetVerticesSize() { return m_VeticesSize; }
    int GetIndicesSize() { return m_IndicesSize; }

private:
    std::vector<Vec3f> m_Vetices;
    std::vector<std::vector<int>> m_Indices;
    int m_VeticesSize;
    int m_IndicesSize;
};

#endif // MODEL_H