#include "CorePipeline.h"

#include <cmath>
#include <iostream>
#include "MathUtils.h"
#include "Algorithm/Clip.h"
#include "Algorithm/Common.h"
#include "material.h"
CorePipeline::CorePipeline(int width, int height)
{
    m_config = Config::GetInstance();
    m_config->Initialize(width, height);
}

CorePipeline::~CorePipeline()
{
    m_config->Destroy();
}

void CorePipeline::ClearFrameBuffer(const Vec4 &color)
{
    m_config->m_backBuffer->clearColorAndDepthBuffer(color);
}

unsigned char *CorePipeline::GetFrameResult()
{
    return m_config->m_frontBuffer->GetColorBuffer();
}

void CorePipeline::SwapFrameBuffer()
{
    FrameBuffer *temp = m_config->m_frontBuffer;
    m_config->m_frontBuffer = m_config->m_backBuffer;
    m_config->m_backBuffer = temp;
}

void CorePipeline::AddDirectionLight(const Vec3 &dir, const Vec4 &color)
{
    std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>();
    light->SetDirectionalLight(dir, color);
    std::shared_ptr<Light> m_light = light;
    m_config->m_lights.push_back(m_light);
}

void CorePipeline::AddPointLight(Vec3 pos, Vec3 atte, const Vec4 &color)
{
    std::shared_ptr<PointLight> light = std::make_shared<PointLight>();
    light->SetPointLight(pos, atte, color);
    std::shared_ptr<Light> m_light = light;
    m_config->m_lights.push_back(m_light);
}

void CorePipeline::AddSpotLight(double cutoff, Vec3 pos, Vec3 dir, Vec3 atte, const Vec4 &color)
{
    std::shared_ptr<SpotLight> light = std::make_shared<SpotLight>();
    light->SetSpotLight(pos, dir, atte, cutoff, color);
    std::shared_ptr<Light> m_light = light;
    m_config->m_lights.push_back(m_light);
}

void CorePipeline::DrawScene()
{
    m_viewMatrix = m_config->m_fpsCamera->GetViewMatrix();
    m_projectMatrix = m_config->m_fpsCamera->GetPerspectiveMatrix();
    for (size_t i = 0; i < m_config->m_models.size(); ++i)
    {
        DrawModel(m_config->m_models[i]);
    }
    if (m_config->m_useSkyBox)
    {
        DrawSkyBox(m_config->m_skyBox);
    }
}

void CorePipeline::DrawMesh()
{
    if (m_config->m_indices->empty())
        return;

    // UpdateViewPlanes(m_viewMatrix, m_projectMatrix);
    for (unsigned int i = 0; i < m_config->m_indices->size(); i += 3)
    {
        // assemble to a triangle primitive
        Vertex p1, p2, p3;
        p1 = (*m_config->m_vertices)[(*m_config->m_indices)[i + 0]];
        p2 = (*m_config->m_vertices)[(*m_config->m_indices)[i + 1]];
        p3 = (*m_config->m_vertices)[(*m_config->m_indices)[i + 2]];
        DrawTriangle(p1, p2, p3);
    }
}

void CorePipeline::DrawTriangle(Vertex &p1, Vertex &p2, Vertex &p3)
{
    // vertex shader stage
    VertexOut v1, v2, v3;
    {
        v1 = m_config->m_shader->VertexShader(p1);
        v2 = m_config->m_shader->VertexShader(p2);
        v3 = m_config->m_shader->VertexShader(p3);
    }
    // view culling
    // if (!ViewCulling(v1.clipPos, v2.clipPos, v3.clipPos))
    // {
    //     continue;
    // }

    if (m_config->m_viewCull && !ClipSpaceCull(v1.clipPos, v2.clipPos, v3.clipPos))
    {
        return;
    }

    // https://chaosinmotion.com/2016/05/22/3d-clipping-in-homogeneous-coordinates/
    //  v.x, v.y, v.z \in [-w, w], not be assigned to 1(only in the step PerspectiveDivision doing so)
    //  lerp are done in the projection space
    //  if the point are not transformed to the viewport space, the clip can be linear, shouldn't use the correction
    std::vector<VertexOut> clippingVertexs = SutherlandHodgeman(v1, v2, v3);

    for (int i = 0; i < clippingVertexs.size(); ++i)
    {
        PerspectiveDivision(clippingVertexs[i]);
    }
    int n = clippingVertexs.size() - 3 + 1; // the number of the clipping triangles
    for (int i = 0; i < n; ++i)
    {
        VertexOut v1 = clippingVertexs[0];
        VertexOut v2 = clippingVertexs[i + 1];
        VertexOut v3 = clippingVertexs[i + 2];
        // back face culling
        {
            if (m_config->m_polygonMode == PolygonMode::Fill && m_config->m_backFaceCulling)
            {
                if (!BackFaceClipping(v1.clipPos, v2.clipPos, v3.clipPos, m_config->m_faceCullMode))
                    continue;
            }
        }
        // view port transformation
        {
            // 如果m_viewPortMat的(2,2)元素反转了，那么Texture和depthBuffer的元素不用反转
            v1.clipPos = m_config->m_viewPortMat * v1.clipPos;
            v2.clipPos = m_config->m_viewPortMat * v2.clipPos;
            v3.clipPos = m_config->m_viewPortMat * v3.clipPos;
        }

        // rasterization and fragment shader stage
        {
            if (m_config->m_polygonMode == PolygonMode::Wire)
            {
                BresenhamLineRasterization(v1, v2);
                BresenhamLineRasterization(v2, v3);
                BresenhamLineRasterization(v3, v1);
            }
            else if (m_config->m_polygonMode == PolygonMode::Fill)
            {
                // if (m_config->m_faceCullMode == FaceCullMode::BackFaceCull)
                //     EdgeWalkingFillRasterization(v1, v2, v3);
                // else
                //     EdgeWalkingFillRasterization(v1, v3, v2);
                if (m_config->m_faceCullMode == FaceCullMode::BackFaceCull)
                    RasterTriangle(v1, v2, v3);
                else
                    RasterTriangle(v1, v3, v2);
            }
        }
    }
}

void CorePipeline::DrawModel(const std::shared_ptr<Model> &model)
{

    for (size_t i = 0; i < model->m_objectNum; ++i)
    {
        Uniform u(model->GetTransform(), m_viewMatrix, m_projectMatrix);
        u.m_ambient = m_config->m_ambient;
        u.m_lights = &(m_config->m_lights);
        // u.m_lights = (m_config->m_lightGroup);
        u.m_eyePos = m_config->m_fpsCamera->GetPosition();
        DrawObject(model->m_objects[i], u);
    }
}

void CorePipeline::DrawSkyBox(Model *model)
{
    m_config->m_faceCullMode = FrontFaceCull;
    m_config->m_shader = m_config->m_skyBox->m_objects[0].GetShader();
    Uniform u;
    u.m_viewMatrix = m_viewMatrix;
    u.m_projectMatrix = m_projectMatrix;
    u.m_cubeMap = m_config->m_cubeMap;
    SetVertexBuffer(&(m_config->m_skyBox->m_objects[0].m_mesh->m_vertices));
    SetIndexBuffer(&(m_config->m_skyBox->m_objects[0].m_mesh->m_indices));
    m_config->m_shader->SetUniform(&u);
    DrawMesh();
    m_config->m_faceCullMode = BackFaceCull;
}

void CorePipeline::DrawObject(const Object &obj, Uniform &u)
{
    m_config->m_shader = obj.GetShader();
    obj.m_material->SetupUniform(u);

    SetVertexBuffer(&obj.m_mesh->m_vertices);
    SetIndexBuffer(&obj.m_mesh->m_indices);
    m_config->m_shader->SetUniform(&u);
    DrawMesh();
}

void CorePipeline::RasterTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3)
{
    int fxPtX[3], fxPtY[3];
    fxPtX[0] = (int)(v1.clipPos.x + 0.5);
    fxPtY[0] = (int)(v1.clipPos.y + 0.5);
    fxPtX[1] = (int)(v2.clipPos.x + 0.5);
    fxPtY[1] = (int)(v2.clipPos.y + 0.5);
    fxPtX[2] = (int)(v3.clipPos.x + 0.5);
    fxPtY[2] = (int)(v3.clipPos.y + 0.5);
    int startX = max(min(min(fxPtX[0], fxPtX[1]), fxPtX[2]), 0);
    int endX = min(max(max(fxPtX[0], fxPtX[1]), fxPtX[2]), m_config->m_width - 1);

    int startY = max(min(min(fxPtY[0], fxPtY[1]), fxPtY[2]), 0);
    int endY = min(max(max(fxPtY[0], fxPtY[1]), fxPtY[2]), m_config->m_height - 1);

    // rasterization
    for (int x = startX; x <= endX; x++)
    {
        for (int y = startY; y <= endY; y++)
        {
            Vec3 weight = Barycentric2D((float)(x + 0.5), (float)(y + 0.5), v1.clipPos, v2.clipPos, v3.clipPos);

            if (IsInsideTriangle(weight.x, weight.y, weight.z))
            {
                VertexOut current = Lerp(v1, v2, v3, weight);
                if (m_config->m_depthTesting)
                {
                    float pixelDepth = m_config->m_backBuffer->GetPixelDepth(x, y);
                    if (current.clipPos.z > pixelDepth)
                        continue;
                    m_config->m_backBuffer->SetPixelDepth(x, y, current.clipPos.z);
                }
                PerspectiveRestore(current);
                m_config->m_backBuffer->SetPixelColor(x, y, m_config->m_shader->FragmentShader(current));
            }
        }
    }
    // int fxPtX[3], fxPtY[3];
    // fxPtX[0] = (int)(v1.clipPos.x + 0.5);
    // fxPtY[0] = (int)(v1.clipPos.y + 0.5);
    // fxPtX[1] = (int)(v2.clipPos.x + 0.5);
    // fxPtY[1] = (int)(v2.clipPos.y + 0.5);
    // fxPtX[2] = (int)(v3.clipPos.x + 0.5);
    // fxPtY[2] = (int)(v3.clipPos.y + 0.5);

    // // float Z[3] = {v1.clipPos.z, v2.clipPos.z, v3.clipPos.z};

    // int startX = max(min(min(fxPtX[0], fxPtX[1]), fxPtX[2]), 0);
    // int endX = min(max(max(fxPtX[0], fxPtX[1]), fxPtX[2]), m_config->m_width - 1);

    // int startY = max(min(min(fxPtY[0], fxPtY[1]), fxPtY[2]), 0);
    // int endY = min(max(max(fxPtY[0], fxPtY[1]), fxPtY[2]), m_config->m_height - 1);

    // // I Ay - By
    // int I01 = fxPtY[0] - fxPtY[1];
    // int I02 = fxPtY[1] - fxPtY[2];
    // int I03 = fxPtY[2] - fxPtY[0];

    // // J Bx - Ax
    // int J01 = fxPtX[1] - fxPtX[0];
    // int J02 = fxPtX[2] - fxPtX[1];
    // int J03 = fxPtX[0] - fxPtX[2];

    // // K AxBy - AyBx
    // int K01 = fxPtX[0] * fxPtY[1] - fxPtX[1] * fxPtY[0];
    // int K02 = fxPtX[1] * fxPtY[2] - fxPtX[2] * fxPtY[1];
    // int K03 = fxPtX[2] * fxPtY[0] - fxPtX[0] * fxPtY[2];

    // // F01 = I01 * Px + J01 * Py + K01
    // // Cy
    // int F01 = (I01 * startX) + (J01 * startY) + K01;
    // int F02 = (I02 * startX) + (J02 * startY) + K02;
    // int F03 = (I03 * startX) + (J03 * startY) + K03;

    // // int delta = F01 + F02 + F03;
    // // float OneDivideDelta = 1.0f / (float)delta;
    // // // 面积
    // // // float Delta = (v2.windowPos.x - v1.windowPos.x) * (v3.windowPos.y - v1.windowPos.y) - (v1.windowPos.x - v3.windowPos.x) * (v1.windowPos.y - v2.windowPos.y);
    // int Delta = (fxPtX[1] - fxPtX[0]) * (fxPtY[2] - fxPtY[0]) - (fxPtX[0] - fxPtX[2]) * (fxPtY[0] - fxPtY[1]);
    // float OneDivideDelta = 1 / (float)Delta;

    // // Z[1] = (Z[1] - Z[0]) * OneDivideDelta;
    // // Z[2] = (Z[2] - Z[0]) * OneDivideDelta;

    // VertexOut V1 = v1;
    // VertexOut V2 = v2;
    // VertexOut V3 = v3;

    // V2 = (V2 - V1) * OneDivideDelta;
    // V3 = (V3 - V1) * OneDivideDelta;

    // // // float zx = I03 * Z[1] + I01 * Z[2];
    // // // float zy = J03 * Z[1] + J01 * Z[2];

    // VertexOut vx = V2 * I03 + V3 * I01;
    // VertexOut vy = V2 * J03 + V3 * J01;

    // int Cy1 = F01, Cy2 = F02, Cy3 = F03;
    // VertexOut v0 = V1 + V2 * Cy3 + V3 * Cy1; // +0.5f * vx + 0.5f * vy;

    // for (int y = startY; y <= endY; y++)
    // {
    //     // Cx
    //     int Cx1 = Cy1;
    //     int Cx2 = Cy2;
    //     int Cx3 = Cy3;
    //     VertexOut v1X = v0;
    //     //     // float depth = Z[0] + Cx3 * Z[1] + Cx1 * Z[2];
    //     //     // VertexOut vf = V1 + V2 * Cx3 + V3 * Cx1 + 0.5f * vx;
    //     for (int x = startX; x <= endX; x++)
    //     {
    //         if (((Cx1 <= 0) && (Cx2 <= 0) && (Cx3 <= 0)) || ((Cx1 >= 0) && (Cx2 >= 0) && (Cx3 >= 0)))
    //         {
    //             if (m_config->m_depthTesting)
    //             {
    //                 float pixelDepth = m_config->m_backBuffer->GetPixelDepth(x, y);
    //                 if (v1X.clipPos.z > pixelDepth)
    //                     continue;
    //                 m_config->m_backBuffer->SetPixelDepth(x, y, v1X.clipPos.z);
    //             }
    //             VertexOut current = v1X;
    //             // Vec3 weights = Vec3(Cx2 * OneDivideDelta, Cx3 * OneDivideDelta, Cx1 * OneDivideDelta);
    //             // VertexOut current = Lerp(v1, v2, v3, weights);

    //             PerspectiveRestore(current);
    //             m_config->m_backBuffer->SetPixelColor(x, y, m_config->m_shader->FragmentShader(current));
    //         }
    //         // }
    //         // Cx += I
    //         Cx1 += I01;
    //         Cx2 += I02;
    //         Cx3 += I03;
    //         // depth += zx;
    //         v1X += vx;
    //         // z0 += zx;
    //     }
    //     // Cy += J
    //     Cy1 += J01;
    //     Cy2 += J02;
    //     Cy3 += J03;
    //     // z0 += zy;
    //     v0 += vy;
    // }
}

void CorePipeline::PerspectiveDivision(VertexOut &target)
{
    // oneDivzZ to correct lerp
    target.oneDivZ = 1.0f / target.clipPos.w;

    target.clipPos *= target.oneDivZ;
    target.clipPos.w = 1.0f;
    // map from [-1, 1] to [0, 1]
    target.clipPos.z = (target.clipPos.z + 1.0f) * 0.5f;

    target.worldPos *= target.oneDivZ;
    target.texcoord *= target.oneDivZ;
    target.color *= target.oneDivZ;
    target.normal *= target.oneDivZ;
    target.TBN *= target.oneDivZ;
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// https://liolok.com/zhs/bresenham-line-algorithm-and-decision-parameter/
void CorePipeline::BresenhamLineRasterization(const VertexOut &from, const VertexOut &to)
{
    int dx = to.clipPos.x - from.clipPos.x;
    int dy = to.clipPos.y - from.clipPos.y;
    int stepX = 1, stepY = 1;
    // 保证dx和dy都是正的，用来判断斜率，不用除法
    if (dx < 0)
    {
        stepX = -1;
        dx = -dx;
    }
    if (dy < 0)
    {
        stepY = -1;
        dy = -dy;
    }
    int d2x = 2 * dx, d2y = 2 * dy;
    int d2y_minus_d2x = d2y - d2x;
    int sx = from.clipPos.x;
    int sy = from.clipPos.y;

    VertexOut tmp;
    // slop < 1

    if (dy < dx)
    {
        int flag = d2y - dx;
        for (int i = 0; i < dx; ++i)
        {
            // linear interpolation
            tmp = Lerp(from, to, static_cast<float>(i) / dx);
            float depth = m_config->m_backBuffer->GetPixelDepth(sx, sy);
            if (tmp.clipPos.z > depth)
                continue; // fail to pass the depth testing
            m_config->m_backBuffer->SetPixelDepth(sx, sy, tmp.clipPos.z);
            // fragment shader
            m_config->m_backBuffer->SetPixelColor(sx, sy, m_config->m_shader->FragmentShader(tmp));
            sx += stepX;
            if (flag <= 0)
                flag += d2y;
            else
            {
                sy += stepY;
                flag += d2y_minus_d2x;
            }
        }
    }
    else
    {
        int flag = d2x - dy;
        for (int i = 0; i < dy; ++i)
        {
            tmp = Lerp(from, to, static_cast<float>(i) / dy);
            float depth = m_config->m_backBuffer->GetPixelDepth(sx, sy);
            if (tmp.clipPos.z > depth)
                continue; // fail to pass the depth testing
            m_config->m_backBuffer->SetPixelDepth(sx, sy, tmp.clipPos.z);

            // fragment shader
            m_config->m_backBuffer->SetPixelColor(sx, sy, m_config->m_shader->FragmentShader(tmp));
            sy += stepY;
            if (flag <= 0)
                flag += d2x;
            else
            {
                sx += stepX;
                flag -= d2y_minus_d2x;
            }
        }
    }
}
void CorePipeline::ScanLinePerRow(const VertexOut &left, const VertexOut &right)
{
    // scan the line from left to right
    VertexOut current;
    int length = right.clipPos.x - left.clipPos.x + 1;
    for (int i = 0; i <= length; ++i)
    {
        float weight = static_cast<float>(i) / length;
        current = Lerp(left, right, weight);
        current.clipPos.x = left.clipPos.x + i;
        current.clipPos.y = left.clipPos.y;

        // depth testing
        if (m_config->m_depthTesting)
        {
            float depth = m_config->m_backBuffer->GetPixelDepth(current.clipPos.x, current.clipPos.y);

            if (current.clipPos.z > depth)
                continue; // fail to pass the depth testing

            m_config->m_backBuffer->SetPixelDepth(current.clipPos.x, current.clipPos.y, current.clipPos.z);
        }
        if (current.clipPos.x < 0 || current.clipPos.y < 0)
            continue;
        if (current.clipPos.x >= m_config->m_width || current.clipPos.y >= m_config->m_height)
            break;
        PerspectiveRestore(current);
        // fragment shader
        m_config->m_backBuffer->SetPixelColor(current.clipPos.x, current.clipPos.y, m_config->m_shader->FragmentShader(current));
    }
}
void CorePipeline::PerspectiveRestore(VertexOut &current)
{
    float w = 1.0f / current.oneDivZ;
    current.worldPos *= w;
    current.color *= w;
    current.texcoord *= w;
    current.normal *= w;
    current.TBN *= w;
}
void CorePipeline::RasterTopTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3)
{
    VertexOut left = v2;
    VertexOut right = v3;
    VertexOut dest = v1;
    VertexOut tmp, newleft, newright;
    if (left.clipPos.x > right.clipPos.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = left.clipPos.y - dest.clipPos.y + 1;

    for (int i = 0; i < dy; ++i)
    {
        float weight = 0;
        if (dy != 0)
            weight = static_cast<float>(i) / dy;
        newleft = Lerp(left, dest, weight);
        newright = Lerp(right, dest, weight);
        newleft.clipPos.y = newright.clipPos.y = left.clipPos.y - i;
        ScanLinePerRow(newleft, newright);
    }
}
void CorePipeline::RasterBottomTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3)
{
    VertexOut left = v1;
    VertexOut right = v2;
    VertexOut dest = v3;
    VertexOut tmp, newleft, newright;
    if (left.clipPos.x > right.clipPos.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = dest.clipPos.y - left.clipPos.y + 1;

    for (int i = 0; i < dy; ++i)
    {
        float weight = 0;
        if (dy != 0)
            weight = static_cast<float>(i) / dy;
        newleft = Lerp(left, dest, weight);
        newright = Lerp(right, dest, weight);
        newleft.clipPos.y = newright.clipPos.y = left.clipPos.y + i;
        ScanLinePerRow(newleft, newright);
    }
}
void CorePipeline::EdgeWalkingFillRasterization(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3)
{
    // split the triangle into two parts
    VertexOut tmp;
    VertexOut target[3] = {v1, v2, v3};
    // vertexOut[0].y < vertexOut[1].y < vertexOut[2].y
    //*
    // ** vertexOut[0]
    //  * *
    //   *  *
    //    *  *  vertexOut[1]
    //     *  vertexOut[2]

    if (target[0].clipPos.y > target[1].clipPos.y)
    {
        tmp = target[0];
        target[0] = target[1];
        target[1] = tmp;
    }
    if (target[0].clipPos.y > target[2].clipPos.y)
    {
        tmp = target[0];
        target[0] = target[2];
        target[2] = tmp;
    }
    if (target[1].clipPos.y > target[2].clipPos.y)
    {
        tmp = target[1];
        target[1] = target[2];
        target[2] = tmp;
    }
    // bottom triangle
    if (Equal(target[0].clipPos.y, target[1].clipPos.y))
    {
        RasterBottomTriangle(target[0], target[1], target[2]);
    }
    else if (Equal(target[1].clipPos.y, target[2].clipPos.y))
    {
        RasterTopTriangle(target[0], target[1], target[2]);
    }
    else
    {
        float weight = static_cast<float>(target[1].clipPos.y - target[0].clipPos.y) / (target[2].clipPos.y - target[0].clipPos.y);
        VertexOut newPoint = Lerp(target[0], target[2], weight);

        RasterTopTriangle(target[0], newPoint, target[1]);
        RasterBottomTriangle(newPoint, target[1], target[2]);
    }
}
