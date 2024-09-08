#ifndef COMMON_H
#define COMMON_H
#include "Math/MathGroup.h"
#include "Render/Vertex.h"

VertexOut Lerp(const VertexOut &n1, const VertexOut &n2, double weight);
VertexOut Lerp(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3, const Vec3 &weights);

Vec3 Barycentric2D(float x, float y, const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);

bool IsInsideTriangle(float alpha, float beta, float gamma);

#endif // COMMON_H