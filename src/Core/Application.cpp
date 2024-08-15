#include "Application.h"
#include <QDebug>

#include "Render/Model.h"
#include "Render/Texture2D.h"
#include "Base.h"
#include "Shader/ShaderGroup.h"
#include "time.h"
#include "Render/Mesh.h"
#include "Render/Light.h"
#include <stdio.h>
#include <direct.h>
#include <memory>
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
    Shader *shader = PhongShader::GetInstance();

    Model cubeMdl(Mesh::CreateBox(1.0, 1.0, 1.0), "cube");
    cubeMdl.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/cube/container.jpg"));
    cubeMdl.SetShader(shader);
    m_pipeline->m_config->AddModel(&cubeMdl);

    Model floorMdl(Mesh::CreateFloor(4.3, -1.5), "floor");
    floorMdl.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/floor/floor.jpg"));
    floorMdl.SetShader(shader);
    m_pipeline->m_config->AddModel(&floorMdl);

    // transformation
    double angle = 0.0;
    Mat4x4 cubeTransformMat[3], floorTransformMat;
    cubeTransformMat[0].SetTranslation(Vec3(3.0f, -1.0f, -1.0f));
    cubeTransformMat[1].SetTranslation(Vec3(4.0f, -1.0f, -1.0f));
    cubeTransformMat[2].SetTranslation(Vec3(3.5f, 0.0f, -1.0f));
    Mat4x4 rotateMat;

    Model neptune(curPath + "obj/neptune/neptune.obj");
    neptune.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/neptune/Texf_mouse.jpg"));
    neptune.m_objects[1].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/neptune/Tex002f_body01.jpg"));
    neptune.m_objects[2].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/neptune/Texf_body02.jpg"));
    neptune.m_objects[3].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/neptune/Tex001f_eye.jpg"));
    neptune.SetShader(shader);

    Mat4x4 neptueTransformMat = neptune.SetSize(2.0, 2.0, 2.0);
    Mat4x4 tranlateMat;
    m_pipeline->m_config->AddModel(&neptune);

    // pipeline settings

    m_pipeline->SetShadingMode(ShadingMode::Phong);
    m_pipeline->SetPolygonMode(PolygonMode::Fill);
    m_pipeline->AddDirectionLight(Vec3(0.05, 0.05, 0.05),
                                  Vec3(0.9, 0.1, 0.1),
                                  Vec3(0.9, 0.1, 0.1), Vec3(-1, -2, -1));
    m_pipeline->AddPointLight(Vec3(0.2, 0.2, 0.2),
                              Vec3(0.9, 0.1, 0.1),
                              Vec3(0.9, 0.1, 0.1),
                              Vec3(0.0, 0.0, 0.0),
                              Vec3(1.0f, 0.07f, 0.017f));
    m_pipeline->AddSpotLight(
        Vec3(0.1, 0.1, 0.1),
        Vec3(0.9, 0.1, 0.1),
        Vec3(0.9, 0.1, 0.1),
        15.0f,
        Vec3(0.0, 2.8, 0.0),
        Vec3(0.0, -3.0, 0.0),
        Vec3(1.0f, 0.07f, 0.017f));

    m_pipeline->m_config->NotifyTreeNodeChanged();
    //    m_pipeline->
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
            m_pipeline->DrawModel(cubeMdl);

            m_pipeline->SetModelMatrix(cubeTransformMat[1]);
            m_pipeline->DrawModel(cubeMdl);
            m_pipeline->SetModelMatrix(cubeTransformMat[2]);
            m_pipeline->DrawModel(cubeMdl);
        }

        {
            m_pipeline->SetModelMatrix(tranlateMat * rotateMat * neptueTransformMat);
            m_pipeline->DrawModel(neptune);
        }
        {
            m_pipeline->SetModelMatrix(floorTransformMat);
            m_pipeline->DrawModel(floorMdl);
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
void Application::OnReceiveKeyEvent(int key)
{
    m_fpsCamera->OnKeyPress(key);
}
void Application::Stop()
{
    m_stopped = true;
}
