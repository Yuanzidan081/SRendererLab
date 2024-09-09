#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <memory>
#include "Core/Config.h"
#include "Shader/ShaderGroup.h"
#include "Render/Model.h"
#include "Render/Light.h"
class Pipeline;
void SetTestScenePBRSphere(const std::shared_ptr<Config> &config);
void SetTestScenePBRHelmet(const std::shared_ptr<Config> &config);

void SetTestSceneBlinnPhong(const std::shared_ptr<Config> &config);

void SetTestSceneSkyBox(const std::shared_ptr<Config> &config);

#endif // SCENE_H