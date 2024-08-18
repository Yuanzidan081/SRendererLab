#include "Common.h"
VertexOut Lerp(const VertexOut &n1, const VertexOut &n2, double weight)
{
    VertexOut result;
    result.posProj = n1.posProj.GetLerp(n2.posProj, weight);
    result.posWorld = n1.posWorld.GetLerp(n2.posWorld, weight);
    result.color = n1.color.GetLerp(n2.color, weight);
    result.normal = n1.normal.GetLerp(n2.normal, weight);
    result.texcoord = n1.texcoord.GetLerp(n2.texcoord, weight);
    result.oneDivZ = (1.0 - weight) * n1.oneDivZ + weight * n2.oneDivZ;
    return result;
}