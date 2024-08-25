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
#include "Transformation.h"
Application::Application(int width, int height) : m_stopped(false), m_fps(0), m_width(width), m_height(height)
{
    m_pipeline = new Pipeline(width, height);
}

Application::~Application()
{
    if (m_pipeline)
        delete m_pipeline;

    m_pipeline = nullptr;
}

void Application::Run()
{

    std::string curPath = "E:/Computer Graphics/MyProject/SRendererLab/";
    Shader *shader = PhongShader::GetInstance();
    Shader *shader2 = NormalShader::GetInstance();
    // Model helmetMdl(curPath + "obj/helmet/helmet.obj");
    // helmetMdl.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/helmet/helmet_basecolor.tga"));
    // helmetMdl.SetShader(shader);
    // helmetMdl.SetTranslate(Vec3(3.0, 2.0f, 0.0f));
    // m_pipeline->m_config->AddModel(&helmetMdl);

    // Model cubeMdl(Mesh::CreateBox(1.0, 1.0, 1.0), "cube");
    // cubeMdl.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/cube/container.jpg"));
    // cubeMdl.SetShader(shader);
    // cubeMdl.SetTranslate(Vec3(1.0f, -1.0f, -1.0f));
    // m_pipeline->m_config->AddModel(&cubeMdl);

    // Model floorMdl(Mesh::CreateFloor(15.3, -1.0), "floor");
    // floorMdl.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/floor/floor.jpg"));
    // floorMdl.SetShader(shader);
    // m_pipeline->m_config->AddModel(&floorMdl);

    Model WallMdl(Mesh::CreateFloor(3, 0), "wall1");
    WallMdl.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/wall/brickwall.jpg"));
    WallMdl.m_objects[0].m_material->SetNormalTexture(std::make_shared<Texture2D>(curPath + "obj/wall/wall_normal.png"));
    WallMdl.SetShader(shader2);
    WallMdl.SetRotation(Vec3(90.0f, 0.0f, 0.0f));
    WallMdl.SetTranslate(Vec3(0.0f, 0.5f, -0.5f));
    WallMdl.SetScale(Vec3(2.0f, 1.0f, 1.0f));
    m_pipeline->m_config->AddModel(&WallMdl);

    Model WallMd2(Mesh::CreateFloor(3, 0), "wall2");
    WallMd2.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/wall/brickwall.jpg"));
    WallMd2.m_objects[0].m_material->SetNormalTexture(std::make_shared<Texture2D>(curPath + "obj/wall/wall_normal.png"));
    WallMd2.SetShader(shader2);
    WallMd2.SetRotation(Vec3(90.0f, 90.0f, 0.0f));
    WallMd2.SetTranslate(Vec3(-2.9f, 0.5f, 1.2f));
    WallMd2.SetScale(Vec3(1.0f, 1.0f, 1.0f));
    m_pipeline->m_config->AddModel(&WallMd2);

    Model WallMd3(Mesh::CreateFloor(3, 0), "wall3");
    WallMd3.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/wall/brickwall.jpg"));
    WallMd3.m_objects[0].m_material->SetNormalTexture(std::make_shared<Texture2D>(curPath + "obj/wall/wall_normal.png"));
    WallMd3.SetShader(shader2);
    WallMd3.SetRotation(Vec3(90.0f, -90.0f, 0.0f));
    WallMd3.SetTranslate(Vec3(2.9f, 0.5f, 1.2f));
    WallMd3.SetScale(Vec3(1.0f, 1.0f, 1.0f));
    m_pipeline->m_config->AddModel(&WallMd3);

    // Model sphereMdl(curPath + "obj/sphere/sphere.obj", "sphere1");
    // sphereMdl.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/sphere/sphere_diffuse.png"));
    // sphereMdl.SetShader(shader);
    // sphereMdl.SetTranslate(Vec3(-2.0f, 0.0f, 0.0f));
    // sphereMdl.SetRelScale(Vec3(0.8f, 0.8f, 0.8f));
    // m_pipeline->m_config->AddModel(&sphereMdl);

    // Model sphereMdl2(sphereMdl, "sphere2");
    // sphereMdl2.SetTranslate(Vec3(-2.0f, 1.0f, 0.0f));
    // m_pipeline->m_config->AddModel(&sphereMdl2);

    // Model neptune(curPath + "obj/neptune/neptune.obj");
    // neptune.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/neptune/Texf_mouse.jpg"));
    // neptune.m_objects[1].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/neptune/Tex002f_body01.jpg"));
    // neptune.m_objects[2].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/neptune/Texf_body02.jpg"));
    // neptune.m_objects[3].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/neptune/Tex001f_eye.jpg"));
    // neptune.SetShader(shader);
    // neptune.SetRelScale(Vec3(2.0f, 2.0f, 2.0f));
    // neptune.SetTranslate(Vec3(0.0f, 0.2f, 0.0f));
    // m_pipeline->m_config->AddModel(&neptune);

    // // m_pipeline->m_config->m_cubeMap = new CubeMap(
    // //     new Texture2D(curPath + "res/skybox_sea/right.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/left.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/top.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/bottom.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/back.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/front.jpg"));
    // // m_pipeline->m_config->m_cubeMap = new CubeMap(
    // //     new Texture2D(curPath + "res/skybox_room/m0_px.jpg"),
    // //     new Texture2D(curPath + "res/skybox_room/m0_nx.jpg"),
    // //     new Texture2D(curPath + "res/skybox_room/m0_py.jpg"),
    // //     new Texture2D(curPath + "res/skybox_room/m0_ny.jpg"),
    // //     new Texture2D(curPath + "res/skybox_room/m0_nz.jpg"),
    // //     new Texture2D(curPath + "res/skybox_room/m0_pz.jpg"));
    m_pipeline->m_config->m_cubeMap = new CubeMap(
        new Texture2D(curPath + "res/skybox_avenue/posx.bmp"),
        new Texture2D(curPath + "res/skybox_avenue/negx.bmp"),
        new Texture2D(curPath + "res/skybox_avenue/posy.bmp"),
        new Texture2D(curPath + "res/skybox_avenue/negy.bmp"),
        new Texture2D(curPath + "res/skybox_avenue/negz.bmp"),
        new Texture2D(curPath + "res/skybox_avenue/posz.bmp"));
    m_pipeline->m_config->m_useSkyBox = false;

    m_pipeline->SetPolygonMode(PolygonMode::Fill);
    m_pipeline->AddDirectionLight(
        Vec3(1.5, -1, -1), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    m_pipeline->AddPointLight(Vec3(0.0, 3.0, 0.0),
                              Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    m_pipeline->AddSpotLight(
        60.0f,
        Vec3(0.0, 3.6, 2.4),
        Vec3(0.0, -5.0, -5.0),
        Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 0.0f, 1.0f, 1.0f));

    m_pipeline->m_config->NotifyTreeNodeChanged();
    m_pipeline->m_config->NotifyLightChanged();
    m_fps = 0;
    while (!m_stopped)
    {
        m_pipeline->ClearFrameBuffer(Vec4(0.2f, 0.2f, 0.2f, 1.0f));
        m_pipeline->DrawScene();

        m_pipeline->SwapFrameBuffer();
        emit frameReady(m_pipeline->GetFrameResult());
        ++m_fps;
    }
}

void Application::Stop()
{
    m_stopped = true;
}
