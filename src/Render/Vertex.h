#ifndef VERTEX_H
#define VERTEX_H
#include "Math/Vec4.h"
#include "Math/Vec3.h"
#include "Math/Vec2.h"
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
#endif // VERTEX_H