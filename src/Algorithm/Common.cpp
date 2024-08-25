#include "Common.h"
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