#ifndef MODEL_H
#define MODEL_H
#include "Math/Vec.h"
#include <vector>
#include <string>
class Model
{

public:
    Model(const char *filename);
    ~Model() = default;
    Model(const Model &model);
    Model &operator=(const Model &model);
    void loadModel(const char *filename);

    void loadObjModel(const char *filename);
    Vec3f GetVetices(int i) { return m_Vetices[i]; }

    const std::vector<Vec3f> &GetFullVetices() const { return m_Vetices; }
    std::vector<Vec3f> &GetFullVetices() { return m_Vetices; }
    std::vector<int> GetIndices(int i) { return m_Indices[i]; }
    const std::vector<std::vector<int>> &GetFullIndcies() const { return m_Indices; }
    std::vector<std::vector<int>> &GetFullIndcies() { return m_Indices; }
    const int GetVerticesSize() const { return m_VeticesSize; }
    int GetVerticesSize() { return m_VeticesSize; }
    const int GetIndicesSize() const { return m_IndicesSize; }
    int GetIndicesSize() { return m_IndicesSize; }

private:
    std::vector<Vec3f> m_Vetices;
    std::vector<std::vector<int>> m_Indices;
    int m_VeticesSize;
    int m_IndicesSize;
};

#endif // MODEL_H