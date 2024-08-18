#ifndef CLIP_H
#define CLIP_H
#include <vector>
#include "Math/MathGroup.h"
#include "Render/Vertex.h"
#include "Core/Base.h"
class Clip
{
public:
    static float s_near;
    static float s_far;
};

bool BackFaceClipping(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, FaceCullMode faceCullMode = BackFaceCull);
bool ViewCulling(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3);
void UpdateViewPlanes(Mat4x4 &viewMatrix, Mat4x4 &projectionMatrix);
void ViewingFrustumPlanes(std::vector<Vec4> &planeParameter, const Mat4x4 &vp);
bool IsInsideFrustum(const Vec3 &v, const Vec4 &planeParameter);
bool IsInsideViewPort(const Vec4 &lineParameter, const Vec4 &p);
bool IsAllVertexsInsideViewPort(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3);
VertexOut GetViewPortIntersect(const VertexOut &v1, const VertexOut &v2, const Vec4 &lineParameter);
std::vector<VertexOut> SutherlandHodgeman(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3);

// clipping space cull
bool ClipSpaceCull(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3);

#endif // CLIP_H
