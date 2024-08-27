#include "ResourceManager.h"

ResourceManager *ResourceManager::s_resourceManager = nullptr;

ResourceManager *ResourceManager::GetInstance()
{
    if (s_resourceManager == nullptr)
        s_resourceManager = new ResourceManager();
    return s_resourceManager;
}
