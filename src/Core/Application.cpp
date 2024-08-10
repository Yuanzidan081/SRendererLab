#include "Application.h"
#include <QDebug>

#include "Render/Model.h"
#include "Render/Texture2D.h"
#include "Base.h"
#include "Shader/ShaderGroup.h"
#include "time.h"
#include "Render/Mesh.h"

#include <stdio.h>
#include <direct.h>
Application::Application(int width, int height) : m_stopped(false), m_fps(0), m_width(width), m_height(height)
{
    m_pipeline = new Pipeline(width, height);
    m_fpsCamera = nullptr;
}

Application::~Application()
{
    if (m_pipeline)
        delete m_pipeline;
    if (m_fpsCamera)
        delete m_fpsCamera;

    m_pipeline = nullptr;
    m_fpsCamera = nullptr;
}

void Application::Run()
{
    m_pipeline->initialize();

    //    m_fpsCamera = new QuaternionFPSCamera(Vec3(1.5f, 1.0f, 10.0f));
    m_fpsCamera = new EulerFPSCamera(Vec3(1.5f, 1.0f, 10.0f));

    std::string curPath = "E:/Computer Graphics/MyProject/SRendererLab/";
    Shader *shader = new SimpleShader();
    // head
    Material headMat;
    headMat.SetShader(shader);
    Texture2D headTex(curPath + "obj/head/african_head_diffuse.tga");
    headMat.SetTexture(&headTex);
    Model head(curPath + "obj/head/african_head.obj");
    Mat4x4 headTransformMat = head.SetSize(2.0, 2.0, 2.0);
    head.SetMaterial(0, headMat);

    // head.SetMaterial(headTex);
    //  Mesh
    Mesh cubeMesh;
    cubeMesh.asBox(1.0, 1.0, 1.0);
    Material cubeMat;
    cubeMat.SetShader(shader);
    Texture2D cubeTex(curPath + "obj/cube/container.jpg");
    cubeMat.SetTexture(&cubeTex);
    Object cubeObj(cubeMesh, cubeMat);

    // floor
    Mesh floorMesh;
    floorMesh.asFloor(10.0, -1.5);
    Material floorMat;
    floorMat.SetShader(shader);
    Texture2D floorTex(curPath + "obj/floor/floor.jpg");
    floorMat.SetTexture(&floorTex);
    Object floorObj(floorMesh, floorMat);

    // transformation
    double angle = 0.0;
    Mat4x4 cubeTransformMat[3], floorTransformMat;
    cubeTransformMat[0].SetTranslation(Vec3(3.0f, 0.0f, 1.0f));
    cubeTransformMat[1].SetTranslation(Vec3(4.0f, 0.0f, 1.0f));
    cubeTransformMat[2].SetTranslation(Vec3(3.5f, 1.0f, 1.0f));

    Mat4x4 rotateMat;

    // neptune
    Material bodyMat;
    bodyMat.SetShader(shader);
    Texture2D bodyTexture(curPath + "obj/neptune/Texf_body02.jpg");
    bodyMat.SetTexture(&bodyTexture);
    Material faceMat;
    faceMat.SetShader(shader);
    Texture2D faceTexture(curPath + "obj/neptune/Tex002f_body01.jpg");
    faceMat.SetTexture(&faceTexture);
    Material mouseMat;
    mouseMat.SetShader(shader);
    Texture2D mouseTexture(curPath + "obj/neptune/Texf_mouse.jpg");
    mouseMat.SetTexture(&mouseTexture);
    Material eyeMat;
    eyeMat.SetShader(shader);
    Texture2D eyeTexture(curPath + "obj/neptune/Tex001f_eye.jpg");
    eyeMat.SetTexture(&eyeTexture);
    Model neptune(curPath + "obj/neptune/neptune.obj");
    neptune.SetMaterial(0, mouseMat);
    neptune.SetMaterial(1, faceMat);
    neptune.SetMaterial(2, bodyMat);
    neptune.SetMaterial(3, eyeMat);

    Mat4x4 neptueTransformMat = neptune.SetSize(2.0, 2.0, 2.0);
    Mat4x4 tranlateMat;
    tranlateMat.SetTranslation(Vec3(-1.5f, 0.0f, 1.0f));

    // pipeline settings
    m_pipeline->SetShadingMode(ShadingMode::Simple);
    m_pipeline->SetPolygonMode(PolygonMode::Fill);
    // m_pipeline->SetProjectMatrix(45.0f, static_cast<float>(m_width) / m_height, 0.1f, 100.0f);

    clock_t start, finish;
    m_fps = 0;
    while (!m_stopped)
    {
        start = clock();
        m_pipeline->ClearFrameBuffer(Vec4(0.2f, 0.2f, 0.2f, 1.0f));
        m_pipeline->SetProjectMatrix(m_fpsCamera->GetPerspectiveMatrix());
        m_pipeline->SetViewMatrix(m_fpsCamera->GetPosition(), m_fpsCamera->GetViewMatrix());

        // render cube
        {
            m_pipeline->SetModelMatrix(cubeTransformMat[0]);
            m_pipeline->DrawObject(cubeObj);

            m_pipeline->SetModelMatrix(cubeTransformMat[1]);
            m_pipeline->DrawObject(cubeObj);

            m_pipeline->SetModelMatrix(cubeTransformMat[2]);
            m_pipeline->DrawObject(cubeObj);
        }
        // render head
        {
            // m_pipeline->SetModelMatrix(rotateMat * headTransformMat);
            // m_pipeline->DrawModel(head);
        }

        {
            m_pipeline->SetModelMatrix(tranlateMat * rotateMat * neptueTransformMat);
            m_pipeline->DrawModel(neptune);
        }
        {
            m_pipeline->SetModelMatrix(floorTransformMat);
            m_pipeline->DrawObject(floorObj);
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
    delete shader;
}
void Application::OnReceiveKeyEvent(int key)
{
    m_fpsCamera->OnKeyPress(key);
}
void Application::Stop()
{
    m_stopped = true;
}
