#include "Texture2D.h"
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// one divide 255
#define INV_SCALE 0.003921568627451
Texture2D::Texture2D() : m_Width(0), m_Height(0), m_Channels(0), m_texelBuffer(nullptr), m_flipped(true)
{
}

Texture2D::Texture2D(const char *filename) : m_Width(0), m_Height(0), m_Channels(0), m_texelBuffer(nullptr), m_flipped(true)
{
    LoadTexture(filename);
}

Texture2D::Texture2D(const std::string &filename) : m_Width(0), m_Height(0), m_Channels(0), m_texelBuffer(nullptr), m_flipped(true)
{
    LoadTexture(filename.c_str());
}
Texture2D::~Texture2D()
{
    if (m_texelBuffer)
        stbi_image_free(m_texelBuffer);
    m_texelBuffer = nullptr;
}

bool Texture2D::LoadTexture(const std::string &filename)
{
    if (m_texelBuffer)
        delete m_texelBuffer;
    m_texelBuffer = nullptr;
    if (m_flipped)
        stbi_set_flip_vertically_on_load(true);
    m_texelBuffer = stbi_load(filename.c_str(), &m_Width, &m_Height, &m_Channels, 0);
    if (!m_texelBuffer)
    {
        m_Width = -1;
        m_Height = -1;
        m_Channels = -1;
        std::cout << "Failed to load texture " << filename << std::endl;
    }
    return m_texelBuffer != nullptr;
}
// 如果是3位的channel，返回的最后一位为1就可以了
const Vec4 Texture2D::SampleTexture(const Vec2 &texCoords) const
{

    int x = static_cast<int>(texCoords.x * (m_Width - 1)) % m_Width;
    int y = static_cast<int>(texCoords.y * (m_Height - 1)) % m_Height;
    x = x < 0 ? m_Width + x : x;
    y = y < 0 ? m_Height + y : y;

    if (x < 0 || y < 0 || x >= m_Width || y >= m_Height)
        return Vec4(0.0, 0.0, 0.0, 1.0);
    int ind;

    Vec4 res;
    ind = (y * m_Width + x) * m_Channels;
    if (m_Channels == 3)
    {
        res.r = m_texelBuffer[ind + 0] * INV_SCALE;
        res.g = m_texelBuffer[ind + 1] * INV_SCALE;
        res.b = m_texelBuffer[ind + 2] * INV_SCALE;
        res.a = 1.0f;
    }
    else if (m_Channels == 4)
    {
        res.r = m_texelBuffer[ind + 0] * INV_SCALE;
        res.g = m_texelBuffer[ind + 1] * INV_SCALE;
        res.b = m_texelBuffer[ind + 2] * INV_SCALE;
        res.a = m_texelBuffer[ind + 3] * INV_SCALE;
    }
    return res;
}

std::ostream &operator<<(std::ostream &out, const Texture2D &texture)
{
    out << texture.GetWidth() << " " << texture.GetHeight() << " " << texture.GetChannels() << std::endl;
    return out;
}
