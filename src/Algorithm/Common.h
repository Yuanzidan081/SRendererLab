#ifndef COMMON_H
#define COMMON_H
#include "Math/MathGroup.h"
#include "Render/Vertex.h"

VertexOut Lerp(const VertexOut &n1, const VertexOut &n2, double weight);

#endif // COMMON_H