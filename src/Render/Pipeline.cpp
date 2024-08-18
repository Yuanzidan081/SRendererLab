#include "Pipeline.h"
// #include "UI/window.h"
#include <cmath>
#include <iostream>
#include "MathUtils.h"
#include "Algorithm/Clip.h"
#include "Algorithm/Common.h"
Pipeline::Pipeline(int width, int height)
{
    m_config = Config::GetInstance();
    m_config->Initialize(width, height);
}

Pipeline::~Pipeline()
{
    m_config->Destroy();
}

void Pipeline::ClearFrameBuffer(const Vec4 &color)
{
    m_config->m_backBuffer->clearColorAndDepthBuffer(color);
}

unsigned char *Pipeline::GetFrameResult()
{
    return m_config->m_frontBuffer->GetColorBuffer();
}

void Pipeline::SwapFrameBuffer()
{
    FrameBuffer *temp = m_config->m_frontBuffer;
    m_config->m_frontBuffer = m_config->m_backBuffer;
    m_config->m_backBuffer = temp;
}

void Pipeline::AddDirectionLight(Vec3 amb, Vec3 diff, Vec3 spec, Vec3 dir)
{
    DirectionalLight *light = new DirectionalLight();
    light->SetDirectionalLight(amb, diff, spec, dir);
    Light *m_light = light;
    m_config->m_lights.push_back(m_light);
}

void Pipeline::AddPointLight(Vec3 amb, Vec3 diff, Vec3 spec, Vec3 pos, Vec3 atte)
{
    PointLight *light = new PointLight();
    light->SetPointLight(amb, diff, spec, pos, atte);
    Light *m_light = reinterpret_cast<Light *>(light);
    m_config->m_lights.push_back(m_light);
}

void Pipeline::AddSpotLight(Vec3 amb, Vec3 diff, Vec3 spec, double cutoff, Vec3 pos, Vec3 dir, Vec3 atte)
{
    SpotLight *light = new SpotLight();
    light->SetSpotLight(amb, diff, spec, pos, dir, atte, cutoff);
    Light *m_light = reinterpret_cast<Light *>(light);
    m_config->m_lights.push_back(m_light);
}

void Pipeline::DrawScene()
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

void Pipeline::DrawMesh()
{
    if (m_config->m_indices->empty())
        return;

    // UpdateViewPlanes(m_viewMatrix, m_projectMatrix);
    for (unsigned int i = 0; i < m_config->m_indices->size(); i += 3)
    {
        // assemble to a triangle primitive
        Vertex p1, p2, p3;
        {
            p1 = (*m_config->m_vertices)[(*m_config->m_indices)[i + 0]];
            p2 = (*m_config->m_vertices)[(*m_config->m_indices)[i + 1]];
            p3 = (*m_config->m_vertices)[(*m_config->m_indices)[i + 2]];
        }

        // vertex shader stage
        VertexOut v1, v2, v3;
        {
            v1 = m_config->m_shader->vertexShader(p1);
            v2 = m_config->m_shader->vertexShader(p2);
            v3 = m_config->m_shader->vertexShader(p3);
        }
        // view culling
        // if (!ViewCulling(v1.posProj, v2.posProj, v3.posProj))
        // {
        //     continue;
        // }

        if (m_config->m_viewCull && !ClipSpaceCull(v1.posProj, v2.posProj, v3.posProj))
        {
            continue;
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
                    if (!BackFaceClipping(v1.posProj, v2.posProj, v3.posProj, m_config->m_faceCullMode))
                        continue;
                }
            }
            // view port transformation
            {
                // 如果m_viewPortMat的(2,2)元素反转了，那么Texture和depthBuffer的元素不用反转
                v1.posProj = m_config->m_viewPortMat * v1.posProj;
                v2.posProj = m_config->m_viewPortMat * v2.posProj;
                v3.posProj = m_config->m_viewPortMat * v3.posProj;
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
                    EdgeWalkingFillRasterization(v1, v2, v3);
                }
            }
        }
    }
}

void Pipeline::DrawModel(Model *model)
{

    for (size_t i = 0; i < model->m_objectNum; ++i)
    {
        Uniform u(model->GetTransform(), m_viewMatrix, m_projectMatrix);
        u.m_lights = &(m_config->m_lights);
        u.m_eyePos = m_config->m_fpsCamera->GetPosition();
        DrawObject(model->m_objects[i], u);
    }
}

void Pipeline::DrawSkyBox(Model *model)
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

void Pipeline::DrawObject(const Object &obj, Uniform &u)
{
    m_config->m_shader = obj.GetShader();
    u.m_material = obj.GetMaterial();
    u.m_mainTex = obj.GetMainTex();
    SetVertexBuffer(&obj.m_mesh->m_vertices);
    SetIndexBuffer(&obj.m_mesh->m_indices);
    m_config->m_shader->SetUniform(&u);
    DrawMesh();
}

void Pipeline::PerspectiveDivision(VertexOut &target)
{
    // oneDivzZ to correct lerp
    target.oneDivZ = 1.0f / target.posProj.w;

    target.posProj /= target.posProj.w;
    target.posProj.w = 1.0f;
    // map from [-1, 1] to [0, 1]
    target.posProj.z = (target.posProj.z + 1.0f) * 0.5f;

    target.posWorld *= target.oneDivZ;
    target.texcoord *= target.oneDivZ;
    target.color *= target.oneDivZ;
    target.normal *= target.oneDivZ;
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// https://liolok.com/zhs/bresenham-line-algorithm-and-decision-parameter/
void Pipeline::BresenhamLineRasterization(const VertexOut &from, const VertexOut &to)
{
    int dx = to.posProj.x - from.posProj.x;
    int dy = to.posProj.y - from.posProj.y;
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
    int sx = from.posProj.x;
    int sy = from.posProj.y;

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
            if (tmp.posProj.z > depth)
                continue; // fail to pass the depth testing
            m_config->m_backBuffer->SetPixelDepth(sx, sy, tmp.posProj.z);
            // fragment shader
            m_config->m_backBuffer->SetPixelColor(sx, sy, m_config->m_shader->fragmentShader(tmp));
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
            if (tmp.posProj.z > depth)
                continue; // fail to pass the depth testing
            m_config->m_backBuffer->SetPixelDepth(sx, sy, tmp.posProj.z);

            // fragment shader
            m_config->m_backBuffer->SetPixelColor(sx, sy, m_config->m_shader->fragmentShader(tmp));
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
void Pipeline::ScanLinePerRow(const VertexOut &left, const VertexOut &right)
{
    // scan the line from left to right
    VertexOut current;
    int length = right.posProj.x - left.posProj.x + 1;
    for (int i = 0; i <= length; ++i)
    {
        float weight = static_cast<float>(i) / length;
        current = Lerp(left, right, weight);
        current.posProj.x = left.posProj.x + i;
        current.posProj.y = left.posProj.y;

        // depth testing
        if (m_config->m_depthTesting)
        {
            float depth = m_config->m_backBuffer->GetPixelDepth(current.posProj.x, current.posProj.y);

            if (current.posProj.z > depth)
                continue; // fail to pass the depth testing

            m_config->m_backBuffer->SetPixelDepth(current.posProj.x, current.posProj.y, current.posProj.z);
        }
        if (current.posProj.x < 0 || current.posProj.y < 0)
            continue;
        if (current.posProj.x >= m_config->m_width || current.posProj.y >= m_config->m_height)
            break;
        float w = 1.0f / current.oneDivZ;
        current.posWorld *= w;
        current.color *= w;
        current.texcoord *= w;
        current.normal *= w;
        // fragment shader
        m_config->m_backBuffer->SetPixelColor(current.posProj.x, current.posProj.y, m_config->m_shader->fragmentShader(current));
    }
}
void Pipeline::RasterTopTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3)
{
    VertexOut left = v2;
    VertexOut right = v3;
    VertexOut dest = v1;
    VertexOut tmp, newleft, newright;
    if (left.posProj.x > right.posProj.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = left.posProj.y - dest.posProj.y + 1;

    for (int i = 0; i < dy; ++i)
    {
        float weight = 0;
        if (dy != 0)
            weight = static_cast<float>(i) / dy;
        newleft = Lerp(left, dest, weight);
        newright = Lerp(right, dest, weight);
        newleft.posProj.y = newright.posProj.y = left.posProj.y - i;
        ScanLinePerRow(newleft, newright);
    }
}
void Pipeline::RasterBottomTriangle(VertexOut &v1, VertexOut &v2, VertexOut &v3)
{
    VertexOut left = v1;
    VertexOut right = v2;
    VertexOut dest = v3;
    VertexOut tmp, newleft, newright;
    if (left.posProj.x > right.posProj.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = dest.posProj.y - left.posProj.y + 1;

    for (int i = 0; i < dy; ++i)
    {
        float weight = 0;
        if (dy != 0)
            weight = static_cast<float>(i) / dy;
        newleft = Lerp(left, dest, weight);
        newright = Lerp(right, dest, weight);
        newleft.posProj.y = newright.posProj.y = left.posProj.y + i;
        ScanLinePerRow(newleft, newright);
    }
}
void Pipeline::EdgeWalkingFillRasterization(const VertexOut &v1, const VertexOut &v2, const VertexOut &v3)
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

    if (target[0].posProj.y > target[1].posProj.y)
    {
        tmp = target[0];
        target[0] = target[1];
        target[1] = tmp;
    }
    if (target[0].posProj.y > target[2].posProj.y)
    {
        tmp = target[0];
        target[0] = target[2];
        target[2] = tmp;
    }
    if (target[1].posProj.y > target[2].posProj.y)
    {
        tmp = target[1];
        target[1] = target[2];
        target[2] = tmp;
    }
    // bottom triangle
    if (Equal(target[0].posProj.y, target[1].posProj.y))
    {
        RasterBottomTriangle(target[0], target[1], target[2]);
    }
    else if (Equal(target[1].posProj.y, target[2].posProj.y))
    {
        RasterTopTriangle(target[0], target[1], target[2]);
    }
    else
    {
        float weight = static_cast<float>(target[1].posProj.y - target[0].posProj.y) / (target[2].posProj.y - target[0].posProj.y);
        VertexOut newPoint = Lerp(target[0], target[2], weight);

        RasterTopTriangle(target[0], newPoint, target[1]);
        RasterBottomTriangle(newPoint, target[1], target[2]);
    }
}
