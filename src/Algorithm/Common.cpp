#include "Common.h"
#include "Core/Base.h"
VertexOut Lerp(const VertexOut &n1, const VertexOut &n2, double weight)
{
    VertexOut result;
    result.clipPos = n1.clipPos.GetLerp(n2.clipPos, weight);
    result.worldPos = n1.worldPos.GetLerp(n2.worldPos, weight);
    result.color = n1.color.GetLerp(n2.color, weight);
    result.normal = n1.normal.GetLerp(n2.normal, weight);
    result.texcoord = n1.texcoord.GetLerp(n2.texcoord, weight);
    result.TBN = n1.TBN.GetLerp(n2.TBN, weight);
    result.oneDivZ = (1.0 - weight) * n1.oneDivZ + weight * n2.oneDivZ;
    return result;
}

VertexOut Lerp(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3, const Vec3 &weight)
{
    VertexOut result;
    result.clipPos = Lerp3(v1.clipPos, v2.clipPos, v3.clipPos, weight);
    result.worldPos = Lerp3(v1.worldPos, v2.worldPos, v3.worldPos, weight);
    result.color = Lerp3(v1.color, v2.color, v3.color, weight);
    result.normal = Lerp3(v1.normal, v2.normal, v3.normal, weight);
    result.texcoord = Lerp3(v1.texcoord, v2.texcoord, v3.texcoord, weight);
    result.TBN = Lerp3(v1.TBN, v2.TBN, v3.TBN, weight);
    result.oneDivZ = weight.x * v1.oneDivZ + weight.y * v2.oneDivZ + weight.z * v3.oneDivZ;
    return result;
}

Vec3 Barycentric2D(float x, float y, const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
{
    float c1 = (x * (v2.y - v3.y) + (v3.x - v2.x) * y + v2.x * v3.y - v3.x * v2.y) / (v1.x * (v2.y - v3.y) + (v3.x - v2.x) * v1.y + v2.x * v3.y - v3.x * v2.y);
    float c2 = (x * (v3.y - v1.y) + (v1.x - v3.x) * y + v3.x * v1.y - v1.x * v3.y) / (v2.x * (v3.y - v1.y) + (v1.x - v3.x) * v2.y + v3.x * v1.y - v1.x * v3.y);
    return Vec3(c1, c2, 1 - c1 - c2);
}

bool IsInsideTriangle(float alpha, float beta, float gamma)
{

    // here epsilon is to alleviate precision bug
    if (alpha > -EPSILON && beta > -EPSILON && gamma > -EPSILON)
        return true;

    return false;
}
