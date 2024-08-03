#include "Application.h"
#include <QDebug>

#include "Render/Model.h"
#include "Render/Texture2D.h"
#include "Base.h"
#include "Shader/GouraudShader.h"
#include "Shader/CartoonShader.h"
#include "Shader/TextureShader.h"
#include "Shader/NormalShader.h"
#include "Shader/PhongShader.h"
#include "Render/ShaderData.h"
#include "Render/Mesh.h"
Application::Application(int width, int height) : m_stopped(false), m_fps(0), m_width(width), m_height(height)
{
    m_pipeline = new Pipeline(width, height);
    m_naiveCamera = nullptr;
}

Application::~Application()
{
    if (m_pipeline)
        delete m_pipeline;
    if (m_naiveCamera)
        delete m_naiveCamera;

    m_pipeline = nullptr;
    m_naiveCamera = nullptr;
}

void Application::Run()
{
    m_pipeline->initialize();

    m_naiveCamera = new NaiveCamera(Vec3f(1.5f, 1.0f, 10.0f));
    // m_naiveCamera = new NaiveCamera(Vec3f(2.0f, 1.0f, 3.0f));
    // m_naiveCamera = new NaiveCamera(Vec3f(0.0f, 0.0f, 20.0f));
    Model model("obj/head/african_head.obj");

    // Model model("obj/cube/cube.obj");
    // Texture2D texture1("obj/head/african_head_diffuse.tga");

    /* TEST Shader CASE1: GouraudShader*/
    // DrawData drawData;
    // drawData.model = new Model(model);
    // drawData.shader = new GouraudShader();
    // drawData.shader->SetModel(drawData.model);

    /* TEST Shader CASE2: CartoonShader*/
    // DrawData drawData;
    // drawData.model = new Model(model);
    // drawData.shader = new CartoonShader();
    // drawData.shader->SetModel(drawData.model);

    /* TEST Shader CASE3: TextureShader*/
    // model.SetDiffuse("obj/head/african_head_diffuse.tga");
    // model.SetDiffuse("obj/head/grid.tga");
    // DrawData drawData;
    // drawData.model = new Model(model);
    // drawData.shader = new TextureShader();
    // drawData.shader->SetModel(drawData.model);

    /* TEST Shader CASE4: NormalShader*/
    /* model.SetDiffuse("obj/head/african_head_diffuse.tga");
    // model.SetNormal("obj/head/african_head_nm_tangent.png"); // normal in tangent space
    model.SetNormal("obj/head/african_head_nm.png"); // normal in world space
    DrawData drawData;
    drawData.model = &model;
    drawData.shader = new NormalShader();
    drawData.shader->SetModel(drawData.model); */

    /* TEST Shader CASE5: PhongShader*/
    /*  model.SetDiffuse("obj/head/african_head_diffuse.tga");
     model.SetNormal("obj/head/african_head_nm_tangent.png");
     model.SetSpecular("obj/head/african_head_spec.tga");
     DrawData drawData;
     drawData.model = new Model(model);
     drawData.shader = new PhongShader();
     drawData.shader->SetModel(drawData.model); */

    unsigned int floorTex = m_pipeline->LoadTexture("obj/floor/floor.jpg");
    unsigned int headTex = m_pipeline->LoadTexture("obj/head/african_head_diffuse.tga");
    Mesh floor, triangle;
    floor.asFloor(6.0f, -1.5f);
    triangle.asTriangle(Vec3f(0.0f, 1.0f, 0.0f), Vec3f(-1.0f, 0.5f, 0.0f), Vec3f(1.0f, -0.5f, 0.0f));
    Vec3f center(0.0f, 0.0f, 0.0f);
    m_pipeline->SetShadingMode(ShadingMode::Simple);
    m_pipeline->SetPolygonMode(PolygonMode::Fill);
    m_pipeline->SetProjectMatrix(45.0f, static_cast<float>(m_width) / m_height, 0.1f, 100.0f);

    m_pipeline->SetViewMatrix(m_naiveCamera->GetPosition(), m_naiveCamera->GetViewMatrix());
    while (!m_stopped)
    {
        m_pipeline->ClearFrameBuffer(Vec4f(0.2f, 0.2f, 0.2f, 1.0f));
        m_pipeline->SetViewMatrix(m_naiveCamera->GetPosition(), m_naiveCamera->GetViewMatrix());
        // m_pipeline->DrawModelPureColor(model, Vec4f(0.0f, 0.8f, 0.1f, 1.0f), PolygonMode::Fill);
        //     m_pipeline->DrawModelPureColor(model, Vec4f(0.1f, 0.1f, 0.1f, 1.0f), PolygonMode::SLine);
        //      m_pipeline->DrawModelNormalWithoutDepthInfo(model, Vec3f(0.0f, 0.0f, 1.0f), Vec4f(0.0f, 0.8f, 0.1f, 1.0f), PolygonMode::Fill);
        // m_pipeline->DrawModelNormalWithDepthInfo(model, Vec3f(0.0f, 0.0f, 1.0f), Vec4f(0.0f, 0.8f, 0.1f, 1.0f));
        //    m_pipeline->DrawModelWithTextureWithoutViewMat(model, Vec3f(0.0f, 0.0f, 1.0f), texture1);
        // m_pipeline->DrawModelWithTextureWithViewMat(model, Vec3f(1.0f, 1.0f, 1.0f), texture1);
        {
            m_pipeline->BindTexture(floorTex);
            m_pipeline->SetModelMatrix(Mat4x4f::GetIdentity());
            m_pipeline->SetVertexBuffer(&floor.m_vertices);
            m_pipeline->SetIndexBuffer(&floor.m_indices);
            m_pipeline->DrawMesh();
            m_pipeline->UnBindTexture(floorTex);
        }

        // head
        {
            m_pipeline->BindTexture(headTex);
            m_pipeline->SetModelMatrix(Mat4x4GetScale(Vec3f(0.2f, 0.2f, 0.2f)));
            m_pipeline->SetVertexBuffer(&triangle.m_vertices);
            m_pipeline->SetIndexBuffer(&triangle.m_indices);
            m_pipeline->DrawMesh();
            m_pipeline->UnBindTexture(headTex);
        }

        // m_pipeline->DrawModelWithShader(drawData);
        m_pipeline->SwapFrameBuffer();
        emit frameReady(m_pipeline->GetFrameResult());
        ++m_fps;
    }
}
void Application::Stop()
{
    m_stopped = true;
}
