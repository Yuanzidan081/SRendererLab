#include "Pipeline.h"
#include "UI/window.h"
#include <cmath>
Pipeline::Pipeline(int width, int height) : m_Width(width), m_Height(height),
                                            m_backBuffer(nullptr), m_frontBuffer(nullptr), m_depthBuffer(nullptr)
{
}

Pipeline::~Pipeline()
{
    if (m_backBuffer)
        delete m_backBuffer;
    if (m_frontBuffer)
        delete m_frontBuffer;
    if (m_depthBuffer)
        delete m_depthBuffer;
    m_backBuffer = nullptr;
    m_frontBuffer = nullptr;
    m_depthBuffer = nullptr;
}

void Pipeline::DrawLine(Vec3i v1, Vec3i v2, Vec4f &color)
{
    bool steep = false;
    if (std::abs(v1.x - v2.x) < std::abs(v1.y - v2.y))
    {
        std::swap(v1.x, v1.y);
        std::swap(v2.x, v2.y);
        steep = true;
    }
    if (v1.x > v2.x)
    { // 当x0>x1时，调换两个点的坐标
        std::swap(v1, v2);
    }
    for (int x = v1.x; x <= v2.x; ++x)
    {
        float t = (float)(x - v1.x) / (float)(v2.x - v1.x);
        int y = v1.y * (1.0f - t) + v2.y * t;
        if (steep)
            m_backBuffer->SetPixelColor(y, x, color);
        else
            m_backBuffer->SetPixelColor(x, y, color);
    }
}

void Pipeline::DrawTriangle(Vec2i v1, Vec2i v2, Vec2i v3, Vec4f &color, const SRendererType &type)
{
    DrawTriangle(Vec3i(v2.x, v2.y, 0.0f), Vec3i(v3.x, v3.y, 0.0f), Vec3i(v1.x, v1.y, 0.0f), color, type);
}
void Pipeline::DrawTriangle(Vec3i v1, Vec3i v2, Vec3i v3, Vec4f &color, const SRendererType &type)
{
    if (type == SRendererType::SLine)
    {
        // std::cout << f[0] << " " << f[1] << " " << f[2] << std::endl;
        DrawLine(v1, v2, color);
        DrawLine(v2, v3, color);
        DrawLine(v3, v1, color);
    }
    else if (type == SRendererType::SFill)
    {
        if (v1.y == v3.y && v1.y == v2.y)
            return;
        // v1.y <= v2.y <= v3.y
        if (v1.y > v2.y)
            std::swap(v1, v2);
        if (v1.y > v3.y)
            std::swap(v1, v3);
        if (v2.y > v3.y)
            std::swap(v2, v3);
        int total_height = v3.y - v1.y;
        for (int i = 0; i <= total_height; ++i)
        {
            // 根据t1将三角形分为上下两部分
            bool second_half = i > v2.y - v1.y || v2.y == v1.y;
            int segment_height = second_half ? v3.y - v2.y : v2.y - v1.y;
            float alpha = (float)i / total_height;
            float beta = (float)(i - (second_half ? v2.y - v1.y : 0)) / segment_height;
            Vec3i A = v1 + (v3 - v1) * alpha;
            Vec3i B = second_half ? v2 + (v3 - v2) * beta : v1 + (v2 - v1) * beta;
            if (A.x > B.x)
                std::swap(A, B);

            // 下面这个是不对的，会有浮点数的误差，导致出现一些白点
            // DrawLine(Vec3i(A.x, v1.y + i, 0), Vec3i(B.x, v1.y + i, 0), color);
            for (int j = A.x; j <= B.x; ++j)
                m_backBuffer->SetPixelColor(j, v1.y + i, color);
        }
    }
}
void Pipeline::DrawModelPureColor(Model &model, Vec4f &color, const SRendererType &type)
{
    for (int i = 0; i < model.GetIndicesSize(); ++i)
    {
        std::vector<int> ind = model.GetIndices(i);
        Vec3i v1 = CoordWorld2Screen(model.GetVetices(ind[0]));
        Vec3i v2 = CoordWorld2Screen(model.GetVetices(ind[1]));
        Vec3i v3 = CoordWorld2Screen(model.GetVetices(ind[2]));
        DrawTriangle(v1, v2, v3, color, type);
    }
}

void Pipeline::DrawModelNormal(Model &model, Vec3f &lightDir, Vec4f &color, const SRendererType &type)
{
    for (int i = 0; i < model.GetIndicesSize(); ++i)
    {
        Vec3i screenCoord[3];
        Vec3f worldCoord[3];
        std::vector<int> ind = model.GetIndices(i);
        for (int j = 0; j < 3; ++j)
        {
            screenCoord[j] = CoordWorld2Screen(model.GetVetices(ind[j]));
            worldCoord[j] = model.GetVetices(ind[j]);
        }
        /* normal vector，这里obj定义的顶点顺序是逆时针 v1->v2->v3 */
        Vec3f normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
        /* intensity */
        float intensity = VecGetDotProduct(normal, lightDir);
        if (intensity > 0)
            DrawTriangle(screenCoord[0], screenCoord[1], screenCoord[2], Vec4f(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), type);
    }
}
Vec3i Pipeline::CoordWorld2Screen(Vec3f &v)
{
    Vec3i res;
    res.x = (v.x + 1.0f) * m_Width / 2.0f;
    res.y = (v.y + 1.0f) * m_Height / 2.0f;
    res.z = v.z;
    return res;
}
void Pipeline::ClearBuffers(const Vec4f &color)
{
    m_backBuffer->ClearBuffers(color);
}

unsigned char *Pipeline::Output()
{
    return m_frontBuffer->GetColorBuffer();
}

void Pipeline::SwapBuffer()
{
    FrameBuffer *temp = m_frontBuffer;
    m_frontBuffer = m_backBuffer;
    m_backBuffer = temp;
}

void Pipeline::Init()
{
    if (m_backBuffer)
        delete m_backBuffer;
    if (m_frontBuffer)
        delete m_frontBuffer;
    m_backBuffer = new FrameBuffer(m_Width, m_Height);
    m_frontBuffer = new FrameBuffer(m_Width, m_Height);
}

void Pipeline::CheckResize()
{
    if (Window::m_window->width() != m_Width || Window::m_window->height() != m_Height)
    {
        m_Width = Window::m_window->width();
        m_Height = Window::m_window->height();
        Init();
    }
}
