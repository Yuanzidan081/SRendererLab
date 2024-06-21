#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <iostream>
#include <string>
#include "Math/Vec.h"
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

    bool LoadTexture(const char *filename);
    const Vec4f SampleTexture(const Vec2f &texCoords) const;
    friend std::ostream &operator<<(std::ostream &out, const Texture2D &texture);

private:
    int m_Width, m_Height, m_Channels;
    unsigned char *m_texelData;
    bool m_flipped;
};

#endif // TEXTURE2D_H