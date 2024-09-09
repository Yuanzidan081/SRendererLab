#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <iostream>
#include <string>
#include "Math/Vec2.h"
#include "Math/Vec4.h"
#include <vector>
class Texture2D
{
public:
    Texture2D();
    Texture2D(const char *filename);
    Texture2D(const std::string &filename);

    ~Texture2D();
    const int GetWidth() const { return m_Width; }
    int GetWidth() { return m_Width; }
    const int GetHeight() const { return m_Height; }
    int GetHeight() { return m_Height; }
    const int GetChannels() const { return m_Channels; }
    int GetChannels() { return m_Channels; }

    bool LoadTexture(const std::string &filename);
    unsigned char *GetTextureData();
    const Vec4 SampleTexture(const Vec2 &texCoords) const;
    friend std::ostream &operator<<(std::ostream &out, const Texture2D &texture);

private:
    int m_Width, m_Height, m_Channels;
    unsigned char *m_texelBuffer;
    bool m_flipped;
};

class CubeMap
{
public:
    enum FaceDir
    {
        right = 0,  // +x
        up = 1,     // +y
        front = 2,  // +z
        left = 3,   // -x
        bottom = 4, // -y
        back = 5    // -z
    };
    CubeMap() = default;
    CubeMap(Texture2D *rightTex, Texture2D *leftTex,
            Texture2D *upTex, Texture2D *bottomTex,
            Texture2D *frontTex, Texture2D *backTex);
    ~CubeMap();
    Vec4 SampleCubeMap(const Vec3 &dir) const;
    Vec2 GetUV(int index, const Vec3 &dir) const;
    int GetFaceID(const Vec3 &dir) const;

private:
    std::vector<std::shared_ptr<Texture2D>> cubeImage;
};

#endif // TEXTURE2D_H