#ifndef MODEL_H
#define MODEL_H
#include "Math/Vec.h"
#include <vector>
#include <string>
/*
Vertex:
    Vec3f GetVetices(int i);
    const std::vector<Vec3f> &GetFullVetices() const;
    std::vector<Vec3f> &GetFullVetices();
VIndices:
    std::vector<int> GetVIndices(int i);
    const std::vector<std::vector<int>> &GetFullVIndcies() const;
    std::vector<std::vector<int>> &GetFullVIndcies();
UVCoords:
    Vec2f GetUVCoords(int i);
    const std::vector<Vec2f> &GetFullUVCoords() const;
    std::vector<Vec2f> &GetFullUVCoords();
UVIndices
    std::vector<int> GetUVIndices(int i);
    const std::vector<std::vector<int>> &GetFullUVIndices() const;
    std::vector<std::vector<int>> &GetFullUVIndices();

VerticesSize:
    const int GetVerticesSize() const;
    int GetVerticesSize();
VIndicesSize:
    const int GetVIndicesSize() const;
    int GetVIndicesSize();
UVCoordsSize:
    const int GetUVCoordsSize() const;
    int GetUVCoordsSize();
UVIndicesSize:
    const int GetUVIndicesSize() const;
    int GetUVIndicesSize();
*/

class Model
{

public:
    Model(const char *filename);
    ~Model() = default;
    Model(const Model &model);
    Model &operator=(const Model &model);
    void loadModel(const char *filename);

    void loadObjModel(const char *filename);

    // Vertices
    Vec3f GetVetices(int i)
    {
        if (i < 0 && i >= m_Vertices.size())
        {
            std::cout << "Vertices: i is out of range!";
            return Vec3f(0.0f, 0.0f, 0.0f);
        }
        return m_Vertices[i];
    }

    const std::vector<Vec3f> &GetFullVetices() const { return m_Vertices; }
    std::vector<Vec3f> &GetFullVetices() { return m_Vertices; }

    // VIndices
    std::vector<int> GetVIndices(int i)
    {
        if (i < 0 && i >= m_VIndices.size())
        {
            std::cout << "VIndices: i is out of range!";
            return std::vector<int>({0, 0, 0});
        }
        return m_VIndices[i];
    }
    const std::vector<std::vector<int>> &GetFullVIndcies() const { return m_VIndices; }
    std::vector<std::vector<int>> &GetFullVIndcies() { return m_VIndices; }

    // UVCoords
    Vec2f GetUVCoords(int i)
    {
        if (i < 0 && i >= m_UVCoords.size())
        {
            std::cout << "UVCoords: i is out of range!";
            return Vec2f(0.0f, 0.0f);
        }
        return m_UVCoords[i];
    }
    const std::vector<Vec2f> &GetFullUVCoords() const { return m_UVCoords; }
    std::vector<Vec2f> &GetFullUVCoords() { return m_UVCoords; }

    // UVIndices
    std::vector<int> GetUVIndices(int i)
    {
        if (i < 0 && i >= m_UVIndices.size())
        {
            std::cout << "UVIndices: i is out of range!";
            return std::vector<int>({0, 0});
        }
        return m_UVIndices[i];
    }
    const std::vector<std::vector<int>> &GetFullUVIndices() const { return m_UVIndices; }
    std::vector<std::vector<int>> &GetFullUVIndices() { return m_UVIndices; }

    // VerticesSize
    const int GetVerticesSize() const { return m_VerticesSize; }
    int GetVerticesSize() { return m_VerticesSize; }

    // VIndicesSize
    const int GetVIndicesSize() const { return m_VIndicesSize; }
    int GetVIndicesSize() { return m_VIndicesSize; }

    // UVCoordsSize
    const int GetUVCoordsSize() const { return m_UVCoordsSize; }
    int GetUVCoordsSize() { return m_UVCoordsSize; }

    // UVIndicesSize
    const int GetUVIndicesSize() const { return m_UVIndicesSize; }
    int GetUVIndicesSize() { return m_UVIndicesSize; }

private:
    std::vector<Vec3f> m_Vertices;
    std::vector<std::vector<int>> m_VIndices;
    std::vector<Vec2f> m_UVCoords;
    std::vector<std::vector<int>> m_UVIndices;
    int m_VerticesSize;
    int m_VIndicesSize;
    int m_UVCoordsSize;
    int m_UVIndicesSize;
};

#endif // MODEL_H