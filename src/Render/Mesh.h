#ifndef MESH_H
#define MESH_H
#include <vector>
#include "Math/Vec.h"
#include "Math/Mat.h"

class Vertex
{
public:
    Vec4f position; // position
    Vec4f color;    // vertex color
    Vec2f texcoord; // texture coordinate
    Vec3f normal;   // vertex normal
    Vertex() = default;
    Vertex(Vec4f pos_, Vec4f color_, Vec2f texcoord_, Vec3f normal_)
        : position(pos_), color(color_), texcoord(texcoord_), normal(normal_) {}
    Vertex(const Vertex &rhs)
        : position(rhs.position), color(rhs.color), texcoord(rhs.texcoord), normal(rhs.normal) {}
};
class VertexOut
{
public:
    Vec4f posWorld; // position in world space
    Vec4f posProj;  // projected position
    Vec2f texcoord; // texture coordinates
    Vec3f normal;   // vertex normal
    Vec4f color;    // vertex color
    float oneDivZ;
    VertexOut() = default;
    VertexOut(Vec4f posWorld_, Vec4f posProj_, Vec2f tex_,
              Vec3f normal_, Vec4f color_, float oneDivZ_) : posWorld(posWorld_), posProj(posProj_), texcoord(tex_),
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
    void asTriangle(const Vec3f p1, const Vec3f p2, const Vec3f p3);
};
#endif // MESH_H