#include "Pipeline.h"
#include "UI/window.h"
#include <cmath>
#include <iostream>
Pipeline::Pipeline(int width, int height) : m_Width(width), m_Height(height),
                                            m_backBuffer(nullptr), m_frontBuffer(nullptr)
{
}

Pipeline::~Pipeline()
{
    if (m_backBuffer)
        delete m_backBuffer;
    if (m_frontBuffer)
        delete m_frontBuffer;

    m_backBuffer = nullptr;
    m_frontBuffer = nullptr;
}

void Pipeline::DrawModelPureColor(Model &model, Vec4f &color, const SRendererType &type)
{
    for (int i = 0; i < model.GetIndicesSize(); ++i)
    {
        std::vector<int> ind = model.GetIndices(i);
        Vec3i v1 = CoordWorldFloatToScreenInt(model.GetVetices(ind[0]));
        Vec3i v2 = CoordWorldFloatToScreenInt(model.GetVetices(ind[1]));
        Vec3i v3 = CoordWorldFloatToScreenInt(model.GetVetices(ind[2]));
        DrawTriangleWithoutDepthInfo(v1, v2, v3, color, (void *)m_backBuffer, type);
    }
}

void Pipeline::DrawModelNormalWithoutDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const SRendererType &type)
{
    for (int i = 0; i < model.GetIndicesSize(); ++i)
    {
        Vec3i screenCoord[3];
        Vec3f worldCoord[3];
        std::vector<int> ind = model.GetIndices(i);
        for (int j = 0; j < 3; ++j)
        {
            screenCoord[j] = CoordWorldFloatToScreenInt(model.GetVetices(ind[j]));
            worldCoord[j] = model.GetVetices(ind[j]);
        }

        /* normal vector，这里obj定义的顶点顺序是逆时针 v1->v2->v3 */
        Vec3f normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
        /* intensity */
        float intensity = VecGetDotProduct(normal, lightDir);
        if (intensity > 0)
        {
            DrawTriangleWithoutDepthInfo(screenCoord[0], screenCoord[1], screenCoord[2], Vec4f(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), (void *)m_backBuffer, type);
        }
    }
}
void Pipeline::DrawModelNormalWithDepthInfo(Model &model, Vec3f &lightDir, Vec4f &color, const SRendererType &type)
{
    for (int i = 0; i < model.GetIndicesSize(); ++i)
    {
        Vec3i screenCoord[3];
        Vec3f screenCoordf[3];
        Vec3f worldCoord[3];
        std::vector<int> ind = model.GetIndices(i);
        for (int j = 0; j < 3; ++j)
        {
            screenCoord[j] = CoordWorldFloatToScreenInt(model.GetVetices(ind[j]));
            screenCoordf[j] = CoordWorldFloatToScreenFloat(model.GetVetices(ind[j]));
            worldCoord[j] = model.GetVetices(ind[j]);
        }
        // std::cout << "w0: " << worldCoord[0] << "w1: " << worldCoord[1] << "w2: " << worldCoord[2] << std::endl;
        /* normal vector，这里obj定义的顶点顺序是逆时针 v1->v2->v3 */
        Vec3f normal = VecGetNormalize(VecGetCrossProduct(worldCoord[1] - worldCoord[0], worldCoord[2] - worldCoord[0]));
        /* intensity */
        float intensity = VecGetDotProduct(normal, lightDir);
        if (intensity > 0)
        {
            // DrawTriangleWithDepthInfo(screenCoord[0], screenCoord[1], screenCoord[2], Vec4f(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), (void *)m_backBuffer, type);
            DrawTriangleWithDepthInfo(screenCoordf[0], screenCoordf[1], screenCoordf[2], Vec4f(color.r * intensity, color.g * intensity, color.b * intensity, 1.0f), (void *)m_backBuffer, type);
        }
    }
}
// TODO: representation by ViewPortMatrix
Vec3i Pipeline::CoordWorldFloatToScreenInt(Vec3f &v)
{
    Vec3i res;
    res.x = (v.x + 1.0f) * m_Width / 2.0f;
    res.y = (v.y + 1.0f) * m_Height / 2.0f;
    res.z = (v.z + 1.0f) * 255.0f / 2.0f;

    return res;
}
Vec3f Pipeline::CoordWorldFloatToScreenFloat(Vec3f &v)
{
    Vec3f res;
    res.x = (v.x + 1.0f) * m_Width / 2.0f;
    res.y = (v.y + 1.0f) * m_Height / 2.0f;
    res.z = (v.z + 1.0f) * 255.0f / 2.0f;
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
