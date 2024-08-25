#ifndef VERTEX_H
#define VERTEX_H
#include "Math/Vec4.h"
#include "Math/Vec3.h"
#include "Math/Vec2.h"
#include "Math/Mat3x3.h"
class Vertex
{
public:
    Vec4 position; // position
    Vec4 color;    // vertex color
    Vec2 texcoord; // texture coordinate
    Vec3 normal;   // vertex normal
    Vec4 tangent;  // vertex tangent
    Vertex() = default;
    Vertex(Vec4 pos_, Vec4 color_, Vec2 texcoord_, Vec3 normal_, Vec4 tangent_)
        : position(pos_), color(color_), texcoord(texcoord_), normal(normal_), tangent(tangent_) {}
    Vertex(const Vertex &rhs)
        : position(rhs.position), color(rhs.color), texcoord(rhs.texcoord), normal(rhs.normal), tangent(rhs.tangent) {}
    static Vec3 CalTangent(const Vertex &v1, const Vertex &v2, const Vertex &v3);
};
class VertexOut
{
public:
    Vec4 worldPos; // position in world space
    Vec4 clipPos;  // projected position
    Vec2 texcoord; // texture coordinates
    Vec3 normal;   // vertex normal
    Vec4 color;    // vertex color
    Mat3x3 TBN;    // normal mapping

    float oneDivZ;
    VertexOut() = default;
    VertexOut(Vec4 worldPos_, Vec4 clipPos_, Vec2 tex_,
              Vec3 normal_, Vec4 color_, float oneDivZ_, Mat3x3 TBN_) : worldPos(worldPos_), clipPos(clipPos_), texcoord(tex_),
                                                                        normal(normal_), color(color_), oneDivZ(oneDivZ_), TBN(TBN_) {}
    VertexOut(const VertexOut &rhs) : worldPos(rhs.worldPos),
                                      clipPos(rhs.clipPos), texcoord(rhs.texcoord),
                                      normal(rhs.normal), color(rhs.color), oneDivZ(rhs.oneDivZ), TBN(rhs.TBN)
    {
    }
};
#endif // VERTEX_H