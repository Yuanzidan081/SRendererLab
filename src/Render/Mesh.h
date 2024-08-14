#ifndef MESH_H
#define MESH_H
#include <vector>
#include "Math/MathGroup.h"
#include "Vertex.h"

class Mesh
{
public:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::string m_name = "Unknown";
    Mesh() = default;
    Mesh(const Mesh &mesh) : m_vertices(mesh.m_vertices), m_indices(mesh.m_indices), m_name(mesh.m_name) {}
    Mesh &operator=(const Mesh &mesh)
    {
        if (&mesh == this)
            return *this;
        m_vertices = mesh.m_vertices;
        m_indices = mesh.m_indices;
        m_name = mesh.m_name;
        return *this;
    }
    ~Mesh() = default;
    // some simple objects' mesh
    void asBox(double width, double height, double depth);
    void asFloor(double length, double height);
    void asTriangle(const Vec3 p1, const Vec3 p2, const Vec3 p3);

    static Mesh *CreateBox(double width, double height, double depth);
    static Mesh *CreateFloor(double length, double height);
    static Mesh *CreateTriangle(const Vec3 p1, const Vec3 p2, const Vec3 p3);
};
#endif // MESH_H
