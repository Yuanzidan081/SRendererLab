#ifndef MODEL_H
#define MODEL_H
#include "Math/Vec.h"
#include <vector>
#include <string>
using std::vector;

/*
Vertex:
    Vec3f GetVetices(int i);
    const vector<Vec3f> &GetFullVetices() const;
    vector<Vec3f> &GetFullVetices();
VIndices:
    vector<int> GetVIndices(int i);
    const vector<vector<int>> &GetFullVIndcies() const;
    vector<vector<int>> &GetFullVIndcies();
UVCoords:
    Vec2f GetUVCoords(int i);
    const vector<Vec2f> &GetFullUVCoords() const;
    vector<Vec2f> &GetFullUVCoords();
UVIndices
    vector<int> GetUVIndices(int i);
    const vector<vector<int>> &GetFullUVIndices() const;
    vector<vector<int>> &GetFullUVIndices();
Normals
    Vec3f GetNormals(int i);
    const vector<Vec3f> &GetFullNormals() const;
    vector<Vec3f> &GetFullNormals();
NormalIndices
    vector<int> GetNormalIndices(int i);
    const vector<vector>> &GetFullNormalIndices() const;
    vector<vector<int>> &GetFullNormalIndices();

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
NormalsSize:
    const int GetNormalsSize() const;
    int GetNormalsSize();
NormalsIndicesSize
    const int GetNormalsIndicesSize() const;
    int GetNormalsIndicesSize();
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

    const vector<Vec3f> &GetFullVetices() const { return m_Vertices; }
    vector<Vec3f> &GetFullVetices() { return m_Vertices; }

    // VIndices
    vector<int> GetVIndices(int i)
    {
        if (i < 0 && i >= m_VIndices.size())
        {
            std::cout << "VIndices: i is out of range!";
            return vector<int>({0, 0, 0});
        }
        return m_VIndices[i];
    }
    const vector<vector<int>> &GetFullVIndcies() const { return m_VIndices; }
    vector<vector<int>> &GetFullVIndcies() { return m_VIndices; }

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
    const vector<Vec2f> &GetFullUVCoords() const { return m_UVCoords; }
    vector<Vec2f> &GetFullUVCoords() { return m_UVCoords; }

    // UVIndices
    vector<int> GetUVIndices(int i)
    {
        if (i < 0 && i >= m_UVIndices.size())
        {
            std::cout << "UVIndices: i is out of range!";
            return vector<int>({0, 0});
        }
        return m_UVIndices[i];
    }
    const vector<vector<int>> &GetFullUVIndices() const { return m_UVIndices; }
    vector<vector<int>> &GetFullUVIndices() { return m_UVIndices; }

    // Normals
    Vec3f GetNormals(int i)
    {
        if (i < 0 && i >= m_Normals.size())
        {
            std::cout << "Normals: i is out of range!";
            return Vec3f({0.0f, 0.0f, 1.0f});
        }
        return m_Normals[i];
    }
    const vector<Vec3f> &GetFullNormals() const { return m_Normals; }
    vector<Vec3f> &GetFullNormals() { return m_Normals; }

    // NormalIndices
    vector<int> GetNormalIndices(int i)
    {
        if (i < 0 && i >= m_NormalIndices.size())
        {
            std::cout << "NormalIndices: i is out of range!";
            return vector<int>({0, 0, 1});
        }
        return m_NormalIndices[i];
    }
    const vector<vector<int>> &GetFullNormalIndices() const { return m_NormalIndices; }
    vector<vector<int>> &GetFullNormalIndices() { return m_NormalIndices; }
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

    // NormalsSize:
    const int GetNormalsSize() const {return m_NormalsSize; }
    int GetNormalsSize(){return m_NormalsSize; }
    // NormalsIndicesSize
    const int GetNormalsIndicesSize() const{return m_NormalsIndicesSize;}
    int GetNormalsIndicesSize(){return m_NormalsIndicesSize;}

private:
    vector<Vec3f> m_Vertices;
    vector<vector<int>> m_VIndices;
    vector<Vec2f> m_UVCoords;
    vector<vector<int>> m_UVIndices;
    vector<Vec3f> m_Normals;
    vector<vector<int>> m_NormalIndices;
    int m_VerticesSize;
    int m_VIndicesSize;
    int m_UVCoordsSize;
    int m_UVIndicesSize;
    int m_NormalsSize;
    int m_NormalsIndicesSize;
};

#endif // MODEL_H