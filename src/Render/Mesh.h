#ifndef MESH_H
#define MESH_H
#include <vector>
#include "Math/MathGroup.h"

class Vertex
{
public:
    Vec4 position; // position
    Vec4 color;    // vertex color
    Vec2 texcoord; // texture coordinate
    Vec3 normal;   // vertex normal
    Vertex() = default;
    Vertex(Vec4 pos_, Vec4 color_, Vec2 texcoord_, Vec3 normal_)
        : position(pos_), color(color_), texcoord(texcoord_), normal(normal_) {}
    Vertex(const Vertex &rhs)
        : position(rhs.position), color(rhs.color), texcoord(rhs.texcoord), normal(rhs.normal) {}
};
class VertexOut
{
public:
    Vec4 posWorld; // position in world space
    Vec4 posProj;  // projected position
    Vec2 texcoord; // texture coordinates
    Vec3 normal;   // vertex normal
    Vec4 color;    // vertex color
    float oneDivZ;
    VertexOut() = default;
    VertexOut(Vec4 posWorld_, Vec4 posProj_, Vec2 tex_,
              Vec3 normal_, Vec4 color_, float oneDivZ_) : posWorld(posWorld_), posProj(posProj_), texcoord(tex_),
                                                           normal(normal_), color(color_), oneDivZ(oneDivZ_) {}
    VertexOut(const VertexOut &rhs) : posWorld(rhs.posWorld),
                                      posProj(rhs.posProj), texcoord(rhs.texcoord),
                                      normal(rhs.normal), color(rhs.color), oneDivZ(rhs.oneDivZ) {}
};
class Mesh
{
public:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    Mesh() = default;
    Mesh(const Mesh &mesh) : m_vertices(mesh.m_vertices), m_indices(mesh.m_indices) {}
    Mesh &operator=(const Mesh &mesh)
    {
        if (&mesh == this)
            return *this;
        m_vertices = mesh.m_vertices;
        m_indices = mesh.m_indices;
        return *this;
    }
    virtual ~Mesh() = default;
    // some simple objects' mesh

    void asBox(double width, double height, double depth);
    void asFloor(double length, double height);
    void asTriangle(const Vec3 p1, const Vec3 p2, const Vec3 p3);
};
#endif // MESH_H