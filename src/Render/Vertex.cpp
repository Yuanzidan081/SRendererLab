#include "Vertex.h"

Vec3 Vertex::CalTangent(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
    // get texCoord difference
    float du1 = v2.texcoord.x - v1.texcoord.x;
    float dv1 = v2.texcoord.y - v1.texcoord.y;
    float du2 = v3.texcoord.x - v1.texcoord.x;
    float dv2 = v3.texcoord.y - v1.texcoord.y;
    float det = (du1 * dv2 - du2 * dv1);

    // get worldPos difference
    Vec3 e1 = v2.position - v1.position;
    Vec3 e2 = v3.position - v1.position;

    // get tangent axis and bitangent axis
    Vec3 t = (e1 * dv2 - e2 * dv1) / det;
    t.Normalize();
    return t;
}
