#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <memory>
#include "Texture.h"
#include <string>
#include <unordered_map>
class ResourceManager
{
public:
    static ResourceManager *GetInstance();
    std::shared_ptr<Texture> LoadFromFile(const std::string &path)
    {
        // 检查纹理是否已加载
        auto it = textureCache.find(path);
        if (it != textureCache.end())
        {
            it->second->referenceCount++;
            return it->second->textureUnit;
        }

        std::shared_ptr<Texture> texture = std::make_shared<Texture>();
        bool flag = path != "" && texture->LoadTexture(path);
        if (!flag)
            return nullptr;
        textureCache[path] = std::make_shared<TextureResource>(texture, 1);
        return texture;
    }

    void ReleaseFile(const std::string &path)
    {
        auto it = textureCache.find(path);
        if (it == textureCache.end())
            return;
        it->second->referenceCount--;
        if (it->second->referenceCount == 0)
        {
            it->second->textureUnit.reset();
            textureCache.erase(it);
        }
    }

private:
    ResourceManager() = default;
    ResourceManager(const ResourceManager &s) = delete;
    static ResourceManager *s_resourceManager;
    struct TextureResource
    {
        std::shared_ptr<Texture> textureUnit;
        int referenceCount = 0;
        TextureResource(const std::shared_ptr<Texture> &texture_, int referenceCount_) : textureUnit(texture_), referenceCount(referenceCount_) {}
    };
    std::unordered_map<std::string, std::shared_ptr<TextureResource>> textureCache;
};

#endif // TEXTURE_MANAGER_H