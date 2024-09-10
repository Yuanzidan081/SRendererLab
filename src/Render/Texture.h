#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include "Math/Vec2.h"
#include "Math/Vec4.h"
#include <vector>
enum class TextureFormat
{
    LDR,
    HDR
};
class Texture
{

public:
    Texture();
    Texture(const char *filename, bool m_flipped = false);
    Texture(const std::string &filename, bool m_flipped = false);
    Texture(int w, int h, int c, TextureFormat f, bool m_flipped = false);
    void CreateTexture(int w, int h, int c, TextureFormat f);
    ~Texture();
    const int &GetWidth() const { return m_Width; }
    int &GetWidth() { return m_Width; }
    const int &GetHeight() const { return m_Height; }
    int &GetHeight() { return m_Height; }
    const int &GetChannels() const { return m_Channels; }
    int &GetChannels() { return m_Channels; }

    bool LoadTexture(const std::string &filename);
    unsigned char *&GetTextureDataLDR();
    float *&GetTextureDataHDR();

    void Release();
    const Vec4 SampleTexture(const Vec2 &texCoords) const;
    friend std::ostream &operator<<(std::ostream &out, const Texture &texture);

private:
    int m_Width, m_Height, m_Channels;
    unsigned char *m_texelBufferLDR;
    float *m_texelBufferHDR;
    bool m_flipped;
    TextureFormat m_format;
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
    CubeMap();
    CubeMap(Texture *rightTex, Texture *leftTex,
            Texture *upTex, Texture *bottomTex,
            Texture *frontTex, Texture *backTex);
    CubeMap(const std::string &filename);
    void SetTexture(int index, const std::shared_ptr<Texture> &texture);
    ~CubeMap();
    Vec4 SampleCubeMap(const Vec3 &dir) const;
    Vec2 GetUV(int index, const Vec3 &dir) const;
    int GetFaceID(const Vec3 &dir) const;
    std::shared_ptr<Texture> &GetTexture(int index);

private:
    std::vector<std::shared_ptr<Texture>> cubeImage;
};

#endif // TEXTURE_H