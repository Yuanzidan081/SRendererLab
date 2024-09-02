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
    Shader *shaderPhong = PhongShader::GetInstance();
    Shader *shaderNormal = NormalShader::GetInstance();
    Shader *shaderPBR = PBRShader::GetInstance();
    Shader *simpleShader = SimpleShader::GetInstance();
    Model helmetMdl(curPath + "obj/helmet/helmet.obj");
    helmetMdl.m_objects[0].m_material->SetMainTexturePath(curPath + "obj/helmet/helmet_basecolor.tga");
    helmetMdl.m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/helmet/helmet_normal.tga");
    helmetMdl.m_objects[0].m_material->SetMatallicTexPath(curPath + "obj/helmet/helmet_metalness.tga");
    helmetMdl.m_objects[0].m_material->SetAOTexturePath(curPath + "obj/helmet/helmet_occlusion.tga");
    helmetMdl.m_objects[0].m_material->SetRoughnessTexPath(curPath + "obj/helmet/helmet_roughness.tga");
    // helmetMdl.m_objects[0].m_material->m_roughness = 0.1f;
    helmetMdl.m_objects[0].m_material->SetEmissionTexturePath(curPath + "obj/helmet/helmet_emission.tga");
    helmetMdl.SetShader(shaderPhong);
    helmetMdl.SetRotation(Vec3(0.0, 180.0f, 0.0f));
    helmetMdl.SetTranslate(Vec3(-11.0, -8.0f, 0.8f));
    helmetMdl.SetScale(Vec3(5.0, 5.0f, 5.0f));
    m_pipeline->m_config->AddModel(&helmetMdl);

    // Model cubeMdl(Mesh::CreateBox(1.0, 1.0, 1.0), "cube");
    // cubeMdl.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/cube/container.jpg"));
    // cubeMdl.SetShader(shaderPhong);
    // cubeMdl.SetTranslate(Vec3(1.0f, -1.0f, -1.0f));
    // m_pipeline->m_config->AddModel(&cubeMdl);

    Model floorMdl(Mesh::CreateFloor(15, -19), "floor");
    floorMdl.m_objects[0].m_material->SetMainTexturePath(curPath + "obj/wall/brickwall.jpg");
    floorMdl.m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");
    floorMdl.SetShader(shaderPhong);
    floorMdl.SetScale(Vec3(3.0f, 1.0f, 3.0f));
    m_pipeline->m_config->AddModel(&floorMdl);

    Model WallMdl(Mesh::CreateFloor(15, 0), "wall1");
    WallMdl.m_objects[0].m_material->SetMainTexturePath(curPath + "obj/wall/brickwall.jpg");
    WallMdl.m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");
    WallMdl.SetShader(shaderPhong);
    WallMdl.SetRotation(Vec3(90.0f, 0.0f, 0.0f));
    WallMdl.SetTranslate(Vec3(0.0f, 0.5f, -4.5f));
    WallMdl.SetScale(Vec3(3.0f, 1.0f, 3.0f));
    m_pipeline->m_config->AddModel(&WallMdl);

    // Model sphereMdl(curPath + "obj/sphere/sphere.obj", "sphere1");
    // sphereMdl.m_objects[0].m_material->SetMainTexturePath(curPath + "obj/sphere/sphere_diffuse.png");
    // sphereMdl.m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/sphere/sphere_normal.jpg");
    // sphereMdl.m_objects[0].m_material->SetMatallicTexPath(curPath + "obj/sphere/sphere_metalness.jpg");
    // sphereMdl.m_objects[0].m_material->SetRoughnessTexPath(curPath + "obj/sphere/sphere_roughness.png");
    // sphereMdl.m_objects[0].m_material->SetAOTexturePath(curPath + "obj/sphere/sphere_occlusion.jpg");
    // sphereMdl.SetShader(shaderPhong);
    // sphereMdl.SetTranslate(Vec3(-2.0f, 0.0f, 0.0f));
    // sphereMdl.m_objects[0].m_material->m_roughness = 0.5f;
    // sphereMdl.SetRelScale(Vec3(0.8f, 0.8f, 0.8f));
    // m_pipeline->m_config->AddModel(&sphereMdl);

    Model sphereMdl2(curPath + "obj/sphere/sphere.obj", "sphere1");
    sphereMdl2.m_objects[0].m_material->SetMainTexturePath(curPath + "obj/sphere/rustediron/rustediron2_basecolor.png");
    sphereMdl2.m_objects[0].m_material->SetMatallicTexPath(curPath + "obj/sphere/rustediron/rustediron2_metallic.png");
    sphereMdl2.m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/sphere/rustediron/rustediron2_normal.png");
    sphereMdl2.m_objects[0].m_material->SetRoughnessTexPath(curPath + "obj/sphere/rustediron/rustediron2_roughness.png");
    sphereMdl2.SetShader(shaderPhong);
    sphereMdl2.SetTranslate(Vec3(11.7f, -7.5f, -5.5f));
    sphereMdl2.SetRotation(Vec3(0.0f, 0.0f, 0.0f));
    sphereMdl2.SetScale(Vec3(6.0f, 6.0f, 6.0f));
    // sphereMdl2.m_objects[0].m_material->m_roughness = 1.0f;
    m_pipeline->m_config->AddModel(&sphereMdl2);

    // Model sphereMdl3(sphereMdl, "sphere3");
    // sphereMdl3.SetTranslate(Vec3(2.0f, 1.0f, 0.0f));
    // sphereMdl3.m_objects[0].m_material->m_roughness = 0.1f;
    // sphereMdl3.SetShader(shaderPBR);
    // m_pipeline->m_config->AddModel(&sphereMdl3);

    Model neptune(curPath + "obj/neptune/neptune.obj");
    neptune.m_objects[0].m_material->SetMainTexturePath(curPath + "obj/neptune/Texf_mouse.jpg");
    // neptune.m_objects[0].m_material->m_roughness = 0.1f;
    neptune.m_objects[1].m_material->SetMainTexturePath(curPath + "obj/neptune/Tex002f_body01.jpg");
    // neptune.m_objects[1].m_material->m_roughness = 0.1f;

    neptune.m_objects[2].m_material->SetMainTexturePath(curPath + "obj/neptune/Texf_body02.jpg");
    // neptune.m_objects[2].m_material->m_roughness = 0.1f;

    neptune.m_objects[3].m_material->SetMainTexturePath(curPath + "obj/neptune/Tex001f_eye.jpg");
    // neptune.m_objects[3].m_material->SetMainTexturePath(curPath + "obj/neptune/Tex001f_eye.jpg");
    // neptune.m_objects[3].m_material->m_roughness = 0.1f;

    neptune.SetShader(shaderPhong);
    neptune.SetScale(Vec3(0.1774f, 0.1774f, 0.1774f));
    neptune.SetTranslate(Vec3(0.0f, 0.2f, 0.0f));
    m_pipeline->m_config->AddModel(&neptune);

    // // m_pipeline->m_config->m_cubeMap = new CubeMap(
    // //     new Texture2D(curPath + "res/skybox_sea/right.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/left.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/top.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/bottom.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/back.jpg"),
    // //     new Texture2D(curPath + "res/skybox_sea/front.jpg"));
    m_pipeline->m_config->m_cubeMap = new CubeMap(
        new Texture2D(curPath + "res/skybox_room/m0_px.jpg"),
        new Texture2D(curPath + "res/skybox_room/m0_nx.jpg"),
        new Texture2D(curPath + "res/skybox_room/m0_py.jpg"),
        new Texture2D(curPath + "res/skybox_room/m0_ny.jpg"),
        new Texture2D(curPath + "res/skybox_room/m0_nz.jpg"),
        new Texture2D(curPath + "res/skybox_room/m0_pz.jpg"));
    // m_pipeline->m_config->m_cubeMap = new CubeMap(
    //     new Texture2D(curPath + "res/skybox_avenue/posx.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/negx.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/posy.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/negy.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/negz.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/posz.bmp"));
    m_pipeline->m_config->m_useSkyBox = false;

    m_pipeline->SetPolygonMode(PolygonMode::Wire);
    // m_pipeline->AddDirectionLight(
    // Vec3(1.5, -1, -1), Vec4(0.6f, 0.6f, 0.6f, 1.0f));
    // m_pipeline->AddPointLight(Vec3(8.6, -13.5, -1.0),
    //                           Vec3(1.0f, 0.07f, 0.017f), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    // m_pipeline->AddPointLight(Vec3(-17.6, 1.5, 8.8),
    //                           Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    // m_pipeline->AddPointLight(Vec3(19.7, 6.4, 10.0),
    //                           Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    m_pipeline->AddSpotLight(
        60.0f,
        Vec3(0.0, 3.6, 2.4),
        Vec3(0.0, -5.0, -5.0),
        Vec3(1.0f, 0.07f, 0.017f), Vec4(1.0f, 1.0f, 1.0f, 1.0f));

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
