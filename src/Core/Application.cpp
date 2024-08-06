#include "Application.h"
#include <QDebug>

#include "Render/Model.h"
#include "Render/Texture2D.h"
#include "Base.h"
#include "Shader/ShaderGroup.h"
#include "time.h"
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

    m_naiveCamera = new NaiveCamera(Vec3(1.5f, 1.0f, 10.0f));
    // m_naiveCamera = new NaiveCamera(Vec3(2.0f, 1.0f, 3.0f));
    // m_naiveCamera = new NaiveCamera(Vec3(0.0f, 0.0f, 20.0f));
    // Model model("obj/head/african_head.obj");

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

    // Model
    Model head("obj/head/african_head.obj");
    // Mesh
    Mesh cube, floor;
    cube.asBox(1.0, 1.0, 1.0);
    floor.asFloor(10.0, -1.5);

    // transformation
    double angle = 0.0;
    Mat4x4 cubeTransformMat[3], floorTransformMat, headTransformMat;
    cubeTransformMat[0].SetTranslation(Vec3(3.0f, 0.0f, 1.0f));
    cubeTransformMat[1].SetTranslation(Vec3(4.0f, 0.0f, 1.0f));
    cubeTransformMat[2].SetTranslation(Vec3(3.5f, 1.0f, 1.0f));
    headTransformMat = head.SetSize(2.0, 2.0, 2.0);
    Mat4x4 rotateMat;

    // pipeline settings
    m_pipeline->SetShadingMode(ShadingMode::Simple);
    m_pipeline->SetPolygonMode(PolygonMode::Fill);
    m_pipeline->SetProjectMatrix(45.0f, static_cast<float>(m_width) / m_height, 0.1f, 100.0f);
    m_pipeline->SetViewMatrix(m_naiveCamera->GetPosition(), m_naiveCamera->GetViewMatrix());
    // load texture
    unsigned int cubeTex = m_pipeline->LoadTexture("obj/cube/container.jpg");
    unsigned int floorTex = m_pipeline->LoadTexture("obj/floor/floor.jpg");
    unsigned int headTex = m_pipeline->LoadTexture("obj/head/african_head_diffuse.tga");

    // calculate time stamp.
    clock_t start, finish;
    m_fps = 0;
    while (!m_stopped)
    {
        start = clock();
        m_pipeline->ClearFrameBuffer(Vec4(0.2f, 0.2f, 0.2f, 1.0f));
        m_pipeline->SetViewMatrix(m_naiveCamera->GetPosition(), m_naiveCamera->GetViewMatrix());
        // m_pipeline->DrawModelPureColor(model, Vec4(0.0f, 0.8f, 0.1f, 1.0f), PolygonMode::Fill);
        //     m_pipeline->DrawModelPureColor(model, Vec4(0.1f, 0.1f, 0.1f, 1.0f), PolygonMode::SLine);
        //      m_pipeline->DrawModelNormalWithoutDepthInfo(model, Vec3(0.0f, 0.0f, 1.0f), Vec4(0.0f, 0.8f, 0.1f, 1.0f), PolygonMode::Fill);
        // m_pipeline->DrawModelNormalWithDepthInfo(model, Vec3(0.0f, 0.0f, 1.0f), Vec4(0.0f, 0.8f, 0.1f, 1.0f));
        //    m_pipeline->DrawModelWithTextureWithoutViewMat(model, Vec3(0.0f, 0.0f, 1.0f), texture1);
        // m_pipeline->DrawModelWithTextureWithViewMat(model, Vec3(1.0f, 1.0f, 1.0f), texture1);

        // render cube
        {
            m_pipeline->BindTexture(cubeTex);
            m_pipeline->SetVertexBuffer(&cube.m_vertices);
            m_pipeline->SetIndexBuffer(&cube.m_indices);

            m_pipeline->SetModelMatrix(cubeTransformMat[0]);
            m_pipeline->DrawMesh();

            m_pipeline->SetModelMatrix(cubeTransformMat[1]);
            m_pipeline->DrawMesh();

            m_pipeline->SetModelMatrix(cubeTransformMat[2]);
            m_pipeline->DrawMesh();

            m_pipeline->UnBindTexture(floorTex);
        }
        // render head
        {
            m_pipeline->BindTexture(headTex);
            m_pipeline->SetVertexBuffer(&head.m_vertices);
            m_pipeline->SetIndexBuffer(&head.m_indices);

            m_pipeline->SetModelMatrix(rotateMat * headTransformMat);
            m_pipeline->DrawMesh();
            m_pipeline->UnBindTexture(headTex);
        }
        {
            m_pipeline->BindTexture(floorTex);
            m_pipeline->SetModelMatrix(floorTransformMat);
            m_pipeline->SetVertexBuffer(&floor.m_vertices);
            m_pipeline->SetIndexBuffer(&floor.m_indices);
            m_pipeline->DrawMesh();
            m_pipeline->UnBindTexture(floorTex);
        }
        finish = clock();
        double deltaFrameTime = (double)(finish - start) / CLOCKS_PER_SEC;

        // rotate
        angle += 45 * deltaFrameTime;
        angle = fmod(angle, 360);
        rotateMat.SetRotationY(angle);
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
