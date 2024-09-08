#include "Sence.h"
#include "Pipeline.h"

void SetTestScenePBRSphere(const std::shared_ptr<Config> &config)
{
    std::string curPath = "E:/Computer Graphics/MyProject/SRendererLab/";
    // Shader *shaderPhong = PhongShader::GetInstance();
    // Shader *shaderNormal = NormalShader::GetInstance();
    Shader *shaderPBR = PBRShader::GetInstance();
    // Shader *simpleShader = SimpleShader::GetInstance();

    std::shared_ptr<Model> sphereMdl = std::make_shared<Model>(curPath + "obj/sphere/sphere.obj", "sphere1");
    sphereMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/sphere/sphere_diffuse.png");
    sphereMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/sphere/sphere_normal.jpg");
    sphereMdl->m_objects[0].m_material->SetAOTexturePath(curPath + "obj/sphere/sphere_occlusion.jpg");
    sphereMdl->SetShader(shaderPBR);
    sphereMdl->SetRelScale(Vec3(0.8f, 0.8f, 0.8f));
    config->AddModel(sphereMdl);

    for (int i = 2; i <= 25; ++i)
    {
        std::shared_ptr<Model> sphereMdlNew = std::make_shared<Model>(*sphereMdl, "sphere" + std::to_string(i));
        config->AddModel(sphereMdlNew);
    }
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            config->m_models[i * 5 + j]->SetTranslate(Vec3(i - 2, j - 2, 0));
            config->m_models[i * 5 + j]->m_objects[0].m_material->m_roughness = i * 0.2 + 0.2;
            config->m_models[i * 5 + j]->m_objects[0].m_material->m_metallic = j * 0.2 + 0.2;
        }
    }

    config->m_polygonMode = PolygonMode::Fill;

    std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>();
    light->SetDirectionalLight(Vec3(1.5, -1, -1), Vec4(0.6f, 0.6f, 0.6f, 1.0f));
    std::shared_ptr<Light> m_light = light;
    config->m_lights.push_back(m_light);
    config->m_useSkyBox = false;
    config->m_fpsCamera->SetPosition(Vec3(0.0f, 0.0f, 8.0f));
}

void SetTestScenePBRHelmet(const std::shared_ptr<Config> &config)
{
    std::string curPath = "E:/Computer Graphics/MyProject/SRendererLab/";
    Shader *shaderPBR = PBRShader::GetInstance();

    std::shared_ptr<Model> helmetMdl = std::make_shared<Model>(curPath + "obj/helmet/helmet.obj", "helmet");
    helmetMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/helmet/helmet_basecolor.tga");
    helmetMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/helmet/helmet_normal.tga");
    helmetMdl->m_objects[0].m_material->SetMatallicTexPath(curPath + "obj/helmet/helmet_metalness.tga");
    helmetMdl->m_objects[0].m_material->SetAOTexturePath(curPath + "obj/helmet/helmet_occlusion.tga");
    helmetMdl->m_objects[0].m_material->SetRoughnessTexPath(curPath + "obj/helmet/helmet_roughness.tga");
    helmetMdl->m_objects[0].m_material->SetEmissionTexturePath(curPath + "obj/helmet/helmet_emission.tga");
    helmetMdl->SetShader(shaderPBR);
    helmetMdl->SetRotation(Vec3(-90.0, 180.0f, 180.0f));
    helmetMdl->SetTranslate(Vec3(-11.0, -13.0f, 0.8f));

    helmetMdl->SetScale(Vec3(5.0, 5.0f, 5.0f));
    config->AddModel(helmetMdl);

    config->m_polygonMode = PolygonMode::Fill;

    std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>();
    light->SetDirectionalLight(Vec3(1.5, -1, -1), Vec4(0.6f, 0.6f, 0.6f, 1.0f));
    std::shared_ptr<Light> m_light = light;
    config->m_lights.push_back(m_light);
    config->m_useSkyBox = false;
    config->m_fpsCamera->SetPosition(Vec3(0.0f, 0.0f, 75.0f));
}

void SetTestSceneBlinnPhong(const std::shared_ptr<Config> &config)
{
    std::string curPath = "E:/Computer Graphics/MyProject/SRendererLab/";
    Shader *shaderPhong = PhongShader::GetInstance();
    Shader *shaderNormal = NormalShader::GetInstance();
    Shader *shaderPBR = PBRShader::GetInstance();
    Shader *simpleShader = SimpleShader::GetInstance();
    std::shared_ptr<Model> helmetMdl = std::make_shared<Model>(curPath + "obj/helmet/helmet.obj", "helmet");
    helmetMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/helmet/helmet_basecolor.tga");
    helmetMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/helmet/helmet_normal.tga");
    helmetMdl->SetShader(shaderPhong);
    helmetMdl->SetRotation(Vec3(-90.0, 180.0f, 180.0f));
    // helmetMdl->SetTranslate(Vec3(-11.0, -8.0f, 0.8f));
    helmetMdl->SetTranslate(Vec3(-11.0, -13.0f, 0.8f));

    helmetMdl->SetScale(Vec3(5.0, 5.0f, 5.0f));
    config->AddModel(helmetMdl);

    std::shared_ptr<Model> helmetMdl2 = std::make_shared<Model>(curPath + "obj/helmet/helmet.obj", "helmet2");
    helmetMdl2->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/helmet/helmet_basecolor.tga");
    helmetMdl2->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/helmet/helmet_normal.tga");
    helmetMdl2->m_objects[0].m_material->SetMatallicTexPath(curPath + "obj/helmet/helmet_metalness.tga");
    helmetMdl2->m_objects[0].m_material->SetAOTexturePath(curPath + "obj/helmet/helmet_occlusion.tga");
    helmetMdl2->m_objects[0].m_material->SetRoughnessTexPath(curPath + "obj/helmet/helmet_roughness.tga");
    // helmetMdl.m_objects[0].m_material->m_roughness = 0.1f;
    helmetMdl2->m_objects[0].m_material->SetEmissionTexturePath(curPath + "obj/helmet/helmet_emission.tga");
    helmetMdl2->SetShader(shaderPBR);
    helmetMdl2->SetRotation(Vec3(0.0, 180.0f, 0.0f));
    // helmetMdl->SetTranslate(Vec3(-11.0, -8.0f, 0.8f));
    helmetMdl2->SetTranslate(Vec3(-11.0, -2.0f, 0.8f));

    helmetMdl2->SetScale(Vec3(5.0, 5.0f, 5.0f));
    config->AddModel(helmetMdl2);

    // Model cubeMdl(Mesh::CreateBox(1.0, 1.0, 1.0), "cube");
    // cubeMdl.m_objects[0].m_material->SetMainTexture(std::make_shared<Texture2D>(curPath + "obj/cube/container.jpg"));
    // cubeMdl.SetShader(shaderPhong);
    // cubeMdl.SetTranslate(Vec3(1.0f, -1.0f, -1.0f));
    // config->AddModel(&cubeMdl);

    std::shared_ptr<Model> floorMdl = std::make_shared<Model>(Mesh::CreateFloor(15, -19), "floor");
    floorMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/wall/brickwall.jpg");
    floorMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");
    floorMdl->SetShader(shaderPhong);
    floorMdl->SetScale(Vec3(3.0f, 1.0f, 3.0f));
    config->AddModel(floorMdl);

    std::shared_ptr<Model> WallMdl = std::make_shared<Model>(Mesh::CreateFloor(15, 0), "wall1");
    WallMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/wall/brickwall.jpg");
    WallMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");
    WallMdl->SetShader(shaderPhong);
    WallMdl->SetRotation(Vec3(90.0f, 0.0f, 0.0f));
    WallMdl->SetTranslate(Vec3(0.0f, 3.5f, -4.5f));
    WallMdl->SetScale(Vec3(3.0f, 1.0f, 3.0f));
    config->AddModel(WallMdl);

    std::shared_ptr<Model> WallMd2 = std::make_shared<Model>(Mesh::CreateFloor(15, 0), "wall2");
    WallMd2->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/wall/brickwall.jpg");
    WallMd2->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");
    WallMd2->SetShader(shaderPhong);
    WallMd2->SetRotation(Vec3(90.0f, 90.0f, 0.0f));
    WallMd2->SetTranslate(Vec3(-22.5f, 3.5f, -0.5f));
    WallMd2->SetScale(Vec3(3.0f, 1.0f, 3.0f));
    config->AddModel(WallMd2);

    std::shared_ptr<Model> WallMd3 = std::make_shared<Model>(Mesh::CreateFloor(15, 0), "wall3");
    WallMd3->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/wall/brickwall.jpg");
    WallMd3->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");
    WallMd3->SetShader(shaderPhong);
    WallMd3->SetRotation(Vec3(90.0f, -90.0f, 0.0f));
    WallMd3->SetTranslate(Vec3(22.5f, 3.5f, -0.5f));
    WallMd3->SetScale(Vec3(3.0f, 1.0f, 3.0f));
    config->AddModel(WallMd3);

    std::shared_ptr<Model> sphereMdl = std::make_shared<Model>(curPath + "obj/sphere/sphere.obj", "sphere1");
    sphereMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/sphere/sphere_diffuse.png");
    sphereMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/sphere/sphere_normal.jpg");
    // sphereMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");

    sphereMdl->m_objects[0].m_material->SetMatallicTexPath(curPath + "obj/sphere/sphere_metalness.jpg");
    sphereMdl->m_objects[0].m_material->SetRoughnessTexPath(curPath + "obj/sphere/sphere_roughness.png");
    sphereMdl->m_objects[0].m_material->SetAOTexturePath(curPath + "obj/sphere/sphere_occlusion.jpg");
    sphereMdl->SetShader(shaderPBR);
    sphereMdl->SetTranslate(Vec3(11.0, -13.0f, 0.8f));
    // sphereMdl.m_objects[0].m_material->m_roughness = 0.5f;
    sphereMdl->SetScale(Vec3(5.0f, 5.0f, 5.0f));
    config->AddModel(sphereMdl);

    std::shared_ptr<Model> sphereMdl2 = std::make_shared<Model>(curPath + "obj/sphere/sphere.obj", "sphere2");
    sphereMdl2->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/sphere/rustediron/rustediron2_basecolor.png");
    sphereMdl2->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/sphere/rustediron/rustediron2_normal.png");
    // sphereMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");

    sphereMdl2->m_objects[0].m_material->SetMatallicTexPath(curPath + "obj/sphere/rustediron/rustediron2_metallic.png");
    sphereMdl2->m_objects[0].m_material->SetRoughnessTexPath(curPath + "obj/sphere/rustediron/rustediron2_roughness.png");
    sphereMdl2->m_objects[0].m_material->SetAOTexturePath(curPath + "obj/sphere/rustediron/rustediron2_ao.png");
    sphereMdl2->SetShader(shaderPBR);
    sphereMdl2->SetTranslate(Vec3(11.0, -2.0f, 0.8f));
    // sphereMdl.m_objects[0].m_material->m_roughness = 0.5f;
    sphereMdl2->SetScale(Vec3(5.0f, 5.0f, 5.0f));
    config->AddModel(sphereMdl2);

    std::shared_ptr<Model> neptune = std::make_shared<Model>(curPath + "obj/neptune/neptune.obj");
    neptune->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/neptune/Texf_mouse.jpg");
    neptune->m_objects[1].m_material->SetMainTexturePath(curPath + "obj/neptune/Tex002f_body01.jpg");
    neptune->m_objects[2].m_material->SetMainTexturePath(curPath + "obj/neptune/Texf_body02.jpg");
    neptune->m_objects[3].m_material->SetMainTexturePath(curPath + "obj/neptune/Tex001f_eye.jpg");

    neptune->SetShader(shaderPhong);
    neptune->SetScale(Vec3(0.1774f, 0.1774f, 0.1774f));
    neptune->SetTranslate(Vec3(0.0f, 0.2f, 0.0f));
    config->AddModel(neptune);

    config->m_cubeMap = new CubeMap(
        new Texture2D(curPath + "res/skybox_sea/right.jpg"),
        new Texture2D(curPath + "res/skybox_sea/left.jpg"),
        new Texture2D(curPath + "res/skybox_sea/top.jpg"),
        new Texture2D(curPath + "res/skybox_sea/bottom.jpg"),
        new Texture2D(curPath + "res/skybox_sea/back.jpg"),
        new Texture2D(curPath + "res/skybox_sea/front.jpg"));
    // config->m_cubeMap = new CubeMap(
    //     new Texture2D(curPath + "res/skybox_room/m0_px.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_nx.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_py.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_ny.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_nz.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_pz.jpg"));
    // config->m_cubeMap = new CubeMap(
    //     new Texture2D(curPath + "res/skybox_avenue/posx.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/negx.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/posy.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/negy.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/negz.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/posz.bmp"));
    config->m_useSkyBox = false;

    config->m_polygonMode = PolygonMode::Fill;

    std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>();
    light->SetDirectionalLight(Vec3(1.5, -1, -1), Vec4(0.6f, 0.6f, 0.6f, 1.0f));
    std::shared_ptr<Light> m_light = light;
    config->AddLight(m_light);

    // std::shared_ptr<PointLight> light2 = std::make_shared<PointLight>();
    // light2->SetPointLight(Vec3(8.6, -13.5, -1.0),
    //                       Vec3(1.0f, 0.07f, 0.017f), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    // std::shared_ptr<Light> m_light2 = light2;
    // config->AddLight(m_light2);

    // std::shared_ptr<PointLight> light3 = std::make_shared<PointLight>();
    // light3->SetPointLight(Vec3(-17.6, 1.5, 8.8),
    //                       Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    // std::shared_ptr<Light> m_light3 = light3;
    // config->AddLight(m_light3);

    // std::shared_ptr<PointLight> light4 = std::make_shared<PointLight>();
    // light4->SetPointLight(Vec3(19.7, 6.4, 10.0),
    //                       Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    // std::shared_ptr<Light> m_light4 = light4;
    // config->AddLight(m_light4);
    // m_pipeline->AddPointLight(Vec3(8.6, -13.5, -1.0),
    //   Vec3(1.0f, 0.07f, 0.017f), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    // m_pipeline->AddPointLight(Vec3(-17.6, 1.5, 8.8),
    //                           Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    // m_pipeline->AddPointLight(Vec3(19.7, 6.4, 10.0),
    //                           Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    // m_pipeline->AddSpotLight(
    //     60.0f,
    //     Vec3(0.0, 3.6, 2.4),
    //     Vec3(0.0, -5.0, -5.0),
    //     Vec3(1.0f, 0.07f, 0.017f), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    config->m_fpsCamera->SetPosition(Vec3(0.0f, 0.0f, 75.0f));
}

void SetTestSceneSkyBox(const std::shared_ptr<Config> &config)
{
    std::string curPath = "E:/Computer Graphics/MyProject/SRendererLab/";
    Shader *shaderPhong = PhongShader::GetInstance();
    Shader *shaderNormal = NormalShader::GetInstance();
    Shader *shaderPBR = PBRShader::GetInstance();
    Shader *simpleShader = SimpleShader::GetInstance();
    std::shared_ptr<Model> helmetMdl = std::make_shared<Model>(curPath + "obj/helmet/helmet.obj", "helmet");
    helmetMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/helmet/helmet_basecolor.tga");
    helmetMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/helmet/helmet_normal.tga");
    helmetMdl->SetShader(shaderPhong);
    helmetMdl->SetRotation(Vec3(-90.0, 180.0f, 180.0f));
    // helmetMdl->SetTranslate(Vec3(-11.0, -8.0f, 0.8f));
    helmetMdl->SetTranslate(Vec3(-11.0, -13.0f, 0.8f));

    helmetMdl->SetScale(Vec3(5.0, 5.0f, 5.0f));
    config->AddModel(helmetMdl);

    std::shared_ptr<Model> cubeMdl = std::make_shared<Model>(Mesh::CreateBox(1.0, 1.0, 1.0), "cube");
    cubeMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/cube/container.jpg");
    cubeMdl->SetShader(shaderPhong);
    cubeMdl->SetTranslate(Vec3(-22.4f, -14.5f, 1.5f));
    cubeMdl->SetScale(Vec3(8.0f, 8.0f, 8.0f));
    config->AddModel(cubeMdl);

    // std::shared_ptr<Model> cubeMdl = std::make_shared<Model>(Mesh::CreateFloor(15, -19), "floor");
    // cubeMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/wall/brickwall.jpg");
    // cubeMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");
    // cubeMdl->SetShader(shaderPhong);
    // cubeMdl->SetScale(Vec3(3.0f, 1.0f, 3.0f));
    // config->AddModel(cubeMdl);

    std::shared_ptr<Model> floorMdl = std::make_shared<Model>(Mesh::CreateFloor(25, -19), "floor");
    floorMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/wall/brickwall.jpg");
    floorMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");
    floorMdl->SetShader(shaderPhong);
    floorMdl->SetScale(Vec3(3.0f, 1.0f, 3.0f));
    config->AddModel(floorMdl);

    std::shared_ptr<Model> sphereMdl = std::make_shared<Model>(curPath + "obj/sphere/sphere.obj", "sphere1");
    sphereMdl->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/sphere/sphere_diffuse.png");
    sphereMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/sphere/sphere_normal.jpg");
    // sphereMdl->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/wall/wall_normal.png");

    sphereMdl->m_objects[0].m_material->SetMatallicTexPath(curPath + "obj/sphere/sphere_metalness.jpg");
    sphereMdl->m_objects[0].m_material->SetRoughnessTexPath(curPath + "obj/sphere/sphere_roughness.png");
    sphereMdl->m_objects[0].m_material->SetAOTexturePath(curPath + "obj/sphere/sphere_occlusion.jpg");
    sphereMdl->SetShader(shaderPBR);
    sphereMdl->SetTranslate(Vec3(11.0, -14.0f, 0.8f));
    // sphereMdl.m_objects[0].m_material->m_roughness = 0.5f;
    sphereMdl->SetScale(Vec3(5.0f, 5.0f, 5.0f));
    config->AddModel(sphereMdl);

    std::shared_ptr<Model> neptune = std::make_shared<Model>(curPath + "obj/neptune/neptune.obj");
    neptune->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/neptune/Texf_mouse.jpg");
    neptune->m_objects[1].m_material->SetMainTexturePath(curPath + "obj/neptune/Tex002f_body01.jpg");
    neptune->m_objects[2].m_material->SetMainTexturePath(curPath + "obj/neptune/Texf_body02.jpg");
    neptune->m_objects[3].m_material->SetMainTexturePath(curPath + "obj/neptune/Tex001f_eye.jpg");

    neptune->SetShader(shaderPhong);
    neptune->SetScale(Vec3(0.1774f, 0.1774f, 0.1774f));
    neptune->SetTranslate(Vec3(0.0f, 0.2f, 0.0f));

    config->AddModel(neptune);

    std::shared_ptr<Model> ponycar = std::make_shared<Model>(curPath + "obj/ponycar/body/body.obj");
    ponycar->AddObject(curPath + "obj/ponycar/interior/interior.obj");
    ponycar->m_objects[0].m_material->SetMainTexturePath(curPath + "obj/ponycar/body/body_basecolor.tga");
    ponycar->m_objects[0].m_material->SetNormalTexturePath(curPath + "obj/ponycar/body/body_normal.tga");
    ponycar->m_objects[0].m_material->SetMatallicTexPath(curPath + "obj/ponycar/body/body_metalness.tga");
    ponycar->m_objects[0].m_material->SetRoughnessTexPath(curPath + "obj/ponycar/body/body_roughness.tga");
    ponycar->m_objects[0].m_material->SetAOTexturePath(curPath + "obj/ponycar/body/body_occlusion.jpg");
    ponycar->m_objects[0].m_material->SetEmissionTexturePath(curPath + "obj/ponycar/body/body_emission.tga");

    ponycar->m_objects[1].m_material->SetMainTexturePath(curPath + "obj/ponycar/interior/interior_basecolor.tga");
    ponycar->m_objects[1].m_material->SetNormalTexturePath(curPath + "obj/ponycar/interior/interior_normal.tga");
    ponycar->m_objects[1].m_material->SetMatallicTexPath(curPath + "obj/ponycar/interior/interior_metalness.tga");
    ponycar->m_objects[1].m_material->SetRoughnessTexPath(curPath + "obj/ponycar/interior/interior_roughness.tga");
    ponycar->m_objects[1].m_material->SetAOTexturePath(curPath + "obj/ponycar/interior/interior_occlusion.jpg");
    ponycar->m_objects[1].m_material->SetEmissionTexturePath(curPath + "obj/ponycar/interior/interior_emission.png");

    ponycar->SetShader(shaderPBR);
    ponycar->SetScale(Vec3(0.05f, 0.05f, 0.05f));
    ponycar->SetRotation(Vec3(-90.0, 0.0f, 0.0f));
    ponycar->SetTranslate(Vec3(22.4f, -14.5f, 1.5f));

    config->AddModel(ponycar);

    config->m_cubeMap = new CubeMap(
        new Texture2D(curPath + "res/skybox_sea/right.jpg"),
        new Texture2D(curPath + "res/skybox_sea/left.jpg"),
        new Texture2D(curPath + "res/skybox_sea/top.jpg"),
        new Texture2D(curPath + "res/skybox_sea/bottom.jpg"),
        new Texture2D(curPath + "res/skybox_sea/back.jpg"),
        new Texture2D(curPath + "res/skybox_sea/front.jpg"));
    // config->m_cubeMap = new CubeMap(
    //     new Texture2D(curPath + "res/skybox_room/m0_px.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_nx.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_py.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_ny.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_nz.jpg"),
    //     new Texture2D(curPath + "res/skybox_room/m0_pz.jpg"));
    // config->m_cubeMap = new CubeMap(
    //     new Texture2D(curPath + "res/skybox_avenue/posx.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/negx.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/posy.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/negy.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/negz.bmp"),
    //     new Texture2D(curPath + "res/skybox_avenue/posz.bmp"));
    config->m_useSkyBox = true;

    config->m_polygonMode = PolygonMode::Fill;

    std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>();
    light->SetDirectionalLight(Vec3(1.5, -1, -1), Vec4(0.6f, 0.6f, 0.6f, 1.0f));
    std::shared_ptr<Light> m_light = light;
    config->AddLight(m_light);

    // std::shared_ptr<PointLight> light2 = std::make_shared<PointLight>();
    // light2->SetPointLight(Vec3(8.6, -13.5, -1.0),
    //                       Vec3(1.0f, 0.07f, 0.017f), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    // std::shared_ptr<Light> m_light2 = light2;
    // config->AddLight(m_light2);

    // std::shared_ptr<PointLight> light3 = std::make_shared<PointLight>();
    // light3->SetPointLight(Vec3(-17.6, 1.5, 8.8),
    //                       Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    // std::shared_ptr<Light> m_light3 = light3;
    // config->AddLight(m_light3);

    // std::shared_ptr<PointLight> light4 = std::make_shared<PointLight>();
    // light4->SetPointLight(Vec3(19.7, 6.4, 10.0),
    //                       Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    // std::shared_ptr<Light> m_light4 = light4;
    // config->AddLight(m_light4);
    // m_pipeline->AddPointLight(Vec3(8.6, -13.5, -1.0),
    //   Vec3(1.0f, 0.07f, 0.017f), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    // m_pipeline->AddPointLight(Vec3(-17.6, 1.5, 8.8),
    //                           Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    // m_pipeline->AddPointLight(Vec3(19.7, 6.4, 10.0),
    //                           Vec3(1.0f, 0.07f, 0.017f), Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    // m_pipeline->AddSpotLight(
    //     60.0f,
    //     Vec3(0.0, 3.6, 2.4),
    //     Vec3(0.0, -5.0, -5.0),
    //     Vec3(1.0f, 0.07f, 0.017f), Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    config->m_fpsCamera->SetPosition(Vec3(0.0f, 0.0f, 75.0f));
}