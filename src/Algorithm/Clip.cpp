#include "Clip.h"
#include "Common.h"
#include "Core/Base.h"
static std::vector<Vec4> m_viewPlaneParameters(6, Vec4());
static std::vector<Vec4> m_viewLineParameters = {
    // near
    Vec4(0, 0, 1, 1),
    // far
    Vec4(0, 0, -1, 1),
    // left
    Vec4(1, 0, 0, 1),
    // right
    Vec4(-1, 0, 0, 1),
    // top
    Vec4(0, -1, 0, 1),
    // bottom
    Vec4(0, 1, 0, 1)};

float Clip::s_near = 0.01f;
float Clip::s_far = 100.0f;
bool BackFaceClipping(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3, FaceCullMode faceCullMode)
{

    Vec3 edge1(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
    Vec3 edge2(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
    Vec3 viewRay(0, 0, 1);
    Vec3 normal = edge1.GetCrossProduct(edge2);
    return (faceCullMode == BackFaceCull) ? (viewRay.GetDotProduct(normal) > 0) : (viewRay.GetDotProduct(normal) < 0);
}
bool ViewCulling(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3)
{
    Vec3 minPoint, maxPoint;
    minPoint.x = min(v1.x, min(v2.x, v3.x));
    minPoint.y = min(v1.y, min(v2.y, v3.y));
    minPoint.z = min(v1.z, min(v2.z, v3.z));
    maxPoint.x = max(v1.x, max(v2.x, v3.x));
    maxPoint.y = max(v1.y, max(v2.y, v3.y));
    maxPoint.z = max(v1.z, max(v2.z, v3.z));
    // Near 和 Far culling: save the point inside
    if (!IsInsideFrustum(minPoint, m_viewPlaneParameters[4]) && !IsInsideFrustum(maxPoint, m_viewPlaneParameters[4]))
        return false;
    if (!IsInsideFrustum(minPoint, m_viewPlaneParameters[5]) && !IsInsideFrustum(maxPoint, m_viewPlaneParameters[5]))
        return false;
    if (!IsInsideFrustum(minPoint, m_viewPlaneParameters[0]) && !IsInsideFrustum(maxPoint, m_viewPlaneParameters[0]))
        return false;
    if (!IsInsideFrustum(minPoint, m_viewPlaneParameters[1]) && !IsInsideFrustum(maxPoint, m_viewPlaneParameters[1]))
        return false;
    if (!IsInsideFrustum(minPoint, m_viewPlaneParameters[2]) && !IsInsideFrustum(maxPoint, m_viewPlaneParameters[2]))
        return false;
    if (!IsInsideFrustum(minPoint, m_viewPlaneParameters[3]) && !IsInsideFrustum(maxPoint, m_viewPlaneParameters[3]))
        return false;
    return true;
}

void UpdateViewPlanes(Mat4x4 &viewMatrix, Mat4x4 &projectionMatrix)
{
    ViewingFrustumPlanes(m_viewPlaneParameters, projectionMatrix * viewMatrix);
    // ViewingFrustumPlanes(m_config->m_viewPlaneParameters, m_config->m_fpsCamera->GetPerspectiveMatrix() * m_config->m_fpsCamera->GetViewMatrix());
}

// get six frusum's  planes to use for frustum culling
// all the normal vectors of the frustum planes are toward the inside of the frustum
void ViewingFrustumPlanes(std::vector<Vec4> &planeParameter, const Mat4x4 &vp)
{

    // left plane
    planeParameter[0].x = vp[0][3] + vp[0][0];
    planeParameter[0].y = vp[1][3] + vp[1][0];
    planeParameter[0].z = vp[2][3] + vp[2][0];
    planeParameter[0].w = vp[3][3] + vp[3][0];
    // right plane
    planeParameter[1].x = vp[0][3] - vp[0][0];
    planeParameter[1].y = vp[1][3] - vp[1][0];
    planeParameter[1].z = vp[2][3] - vp[2][0];
    planeParameter[1].w = vp[3][3] - vp[3][0];
    // top plane
    planeParameter[2].x = vp[0][3] - vp[0][1];
    planeParameter[2].y = vp[1][3] - vp[1][1];
    planeParameter[2].z = vp[2][3] - vp[2][1];
    planeParameter[2].w = vp[3][3] - vp[3][1];
    // bottom plane
    planeParameter[3].x = vp[0][3] + vp[0][1];
    planeParameter[3].y = vp[1][3] + vp[1][1];
    planeParameter[3].z = vp[2][3] + vp[2][1];
    planeParameter[3].w = vp[3][3] + vp[3][1];
    // near plane
    planeParameter[4].x = vp[0][3] + vp[0][2];
    planeParameter[4].y = vp[1][3] + vp[1][2];
    planeParameter[4].z = vp[2][3] + vp[2][2];
    planeParameter[4].w = vp[3][3] + vp[3][2];
    // far plane
    planeParameter[5].x = vp[0][3] - vp[0][2];
    planeParameter[5].y = vp[1][3] - vp[1][2];
    planeParameter[5].z = vp[2][3] - vp[2][2];
    planeParameter[5].w = vp[3][3] - vp[3][2];
}

// the distance of the point to the plane d = Ax + By + Cz + D
// d < 0 point is outside the frustum
// d > 0 point is inside the frustum
// d = 0 point is on the planes of the frustum
// https://www8.cs.umu.se/kurser/5DV180/VT18/lab/plane_extraction.pdf
bool IsInsideFrustum(const Vec3 &v, const Vec4 &planePrameter)
{
    return planePrameter.x * v.x + planePrameter.y * v.y + planePrameter.z * v.z + planePrameter.w >= 0;
}

bool IsInsideViewPort(const Vec4 &lineParameter, const Vec4 &p)
{
    return lineParameter.x * p.x + lineParameter.y * p.y + lineParameter.z * p.z + lineParameter.w * p.w >= 0;
}

bool IsAllVertexsInsideViewPort(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3)
{
    // outside the ndc
    if (v1.x > 1 || v1.x < -1)
        return false;
    if (v1.y > 1 || v1.y < -1)
        return false;
    if (v2.x > 1 || v2.x < -1)
        return false;
    if (v2.y > 1 || v2.y < -1)
        return false;
    if (v3.x > 1 || v3.x < -1)
        return false;
    if (v3.y > 1 || v3.y < -1)
        return false;
    return true;
}

VertexOut GetViewPortIntersect(const VertexOut &v1, const VertexOut &v2, const Vec4 &lineParameter)
{
    float da = v1.posProj.x * lineParameter.x + v1.posProj.y * lineParameter.y + v1.posProj.z * lineParameter.z + v1.posProj.w * lineParameter.w;
    float db = v2.posProj.x * lineParameter.x + v2.posProj.y * lineParameter.y + v2.posProj.z * lineParameter.z + v2.posProj.w * lineParameter.w;

    float weight = da / (da - db);
    return Lerp(v1, v2, weight);
}
std::vector<VertexOut> SutherlandHodgeman(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3)
{
    std::vector<VertexOut> output = {v1, v2, v3};
    if (IsAllVertexsInsideViewPort(v1.posProj, v2.posProj, v3.posProj))
        return output;
    for (int i = 0; i < m_viewLineParameters.size(); ++i)
    {
        std::vector<VertexOut> input(output);
        output.clear();
        for (int j = 0; j < input.size(); ++j)
        {
            VertexOut cur = input[j];
            VertexOut pre = input[(j + input.size() - 1) % input.size()];
            if (IsInsideViewPort(m_viewLineParameters[i], cur.posProj))
            {
                if (!IsInsideViewPort(m_viewLineParameters[i], pre.posProj))
                {
                    VertexOut intersecting = GetViewPortIntersect(pre, cur, m_viewLineParameters[i]);
                    output.push_back(intersecting);
                }
                output.push_back(cur);
            }
            else if (IsInsideViewPort(m_viewLineParameters[i], pre.posProj))
            {
                VertexOut intersecting = GetViewPortIntersect(pre, cur, m_viewLineParameters[i]);
                output.push_back(intersecting);
            }
        }
    }
    return output;
}

bool ClipSpaceCull(const Vec4 &v1, const Vec4 &v2, const Vec4 &v3)
{
    if (v1.w < Clip::s_near && v2.w < Clip::s_near && v3.w < Clip::s_near)
        return false;
    if (v1.w > Clip::s_far && v1.w > Clip::s_far && v3.w > Clip::s_far)
        return false;
    if (fabs(v1.x) <= fabs(v1.w) || fabs(v1.y) <= fabs(v1.w) || fabs(v1.z) <= fabs(v1.w))
        return true;
    if (fabs(v2.x) <= fabs(v2.w) || fabs(v2.y) <= fabs(v2.w) || fabs(v2.z) <= fabs(v2.w))
        return true;
    if (fabs(v3.x) <= fabs(v3.w) || fabs(v3.y) <= fabs(v3.w) || fabs(v3.z) <= fabs(v3.w))
        return true;
    return false;
}
