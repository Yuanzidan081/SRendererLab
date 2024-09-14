#include "Texture.h"
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// one divide 255
#define INV_SCALE 0.003921568627451
Texture::Texture() : m_Width(0), m_Height(0), m_Channels(0), m_textureBufferUC(nullptr), m_flipped(true), m_textureBufferF(nullptr)
{
}

Texture::Texture(const char *filename, bool m_flipped) : m_Width(0), m_Height(0), m_Channels(0), m_textureBufferUC(nullptr), m_flipped(true), m_textureBufferF(nullptr)
{
    LoadTexture(filename);
}

Texture::Texture(const std::string &filename, bool m_flipped) : m_Width(0), m_Height(0), m_Channels(0), m_textureBufferUC(nullptr), m_flipped(true), m_textureBufferF(nullptr)
{
    LoadTexture(filename.c_str());
}
Texture::Texture(int w, int h, int c, TextureRangeFormat f, bool m_flipped) : m_textureBufferUC(nullptr), m_textureBufferF(nullptr)
{
    CreateTexture(w, h, c, f);
}
void Texture::CreateTexture(int w, int h, int c, TextureRangeFormat f)
{
    if (f == TextureRangeFormat::FLOAT)
    {
        m_textureBufferF = (float *)malloc(w * h * c * sizeof(float));
        m_textureBufferUC = nullptr;
        m_Width = w;
        m_Height = h;
        m_Channels = c;
        m_format = f;
    }
    else
    {
        m_textureBufferUC = (unsigned char *)malloc(w * h * c);
        m_textureBufferF = nullptr;
        m_Width = w;
        m_Height = h;
        m_Channels = c;
        m_format = f;
    }
}
Texture::~Texture()
{
    Release();
}

bool Texture::LoadTexture(const std::string &filename)
{

    const char *extension = strrchr(filename.c_str(), '.') + 1;
    if (strcmp(extension, "hdr") == 0)
    {
        if (m_textureBufferF)
            delete m_textureBufferF;
        // stbi_set_flip_vertically_on_load(true);
        m_textureBufferF = stbi_loadf(filename.c_str(), &m_Width, &m_Height, &m_Channels, 0);
        // channel = 4;
        // linear 2 srgb
        m_format = TextureRangeFormat::FLOAT;
        // Linear2Srgb();
        // stbi_set_flip_vertically_on_load(false);
        return m_textureBufferF != nullptr;
    }

    if (m_textureBufferUC)
        delete m_textureBufferUC;
    if (m_flipped)
        stbi_set_flip_vertically_on_load(true);

    m_textureBufferUC = stbi_load(filename.c_str(), &m_Width, &m_Height, &m_Channels, 0);
    // channel = 4;
    m_format = TextureRangeFormat::UNSIGNED_CHAR;
    if (!m_textureBufferUC)
    {
        m_Width = -1;
        m_Height = -1;
        m_Channels = -1;
        std::cout << "Failed to load texture " << filename << std::endl;
    }

    return m_textureBufferUC != nullptr;
}

unsigned char *&Texture::GetTextureDataLDR()
{
    return m_textureBufferUC;
}
float *&Texture::GetTextureDataHDR()
{
    return m_textureBufferF;
}
void Texture::Release()
{
    if (m_textureBufferUC)
        stbi_image_free(m_textureBufferUC);
    if (m_textureBufferF)
        stbi_image_free(m_textureBufferF);
    m_textureBufferUC = nullptr;
    m_textureBufferF = nullptr;
}
const Vec4 Texture::SampleTexture(const Vec2 &texCoords) const
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

    if (m_format == TextureRangeFormat::FLOAT)
    {
        float *p = m_textureBufferF;
        if (m_Channels == 1)
            return Vec4(*(p + ind), 1.0f, 1.0f, 1.0f);
        if (m_Channels == 3)
            return Vec4(*(p + ind), *(p + ind + 1), *(p + ind + 2), 1.0f);
        if (m_Channels == 4)
            return Vec4(*(p + ind), *(p + ind + 1), *(p + ind + 2), *(p + ind + 3));
        if (m_Channels == 2)
            return Vec4(*(p + ind), *(p + ind + 1), 1.0f, 1.0f);
    }
    else
    {
        unsigned char *p = m_textureBufferUC;
        if (m_Channels == 3)
            return Vec4(*(p + ind) * INV_SCALE, *(p + ind + 1) * INV_SCALE, *(p + ind + 2) * INV_SCALE, 1.0f);
        if (m_Channels == 4)
            return Vec4(*(p + ind) * INV_SCALE, *(p + ind + 1) * INV_SCALE, *(p + ind + 2) * INV_SCALE, *(p + ind + 3) * INV_SCALE);
        if (m_Channels == 1)
            return Vec4(*(p + ind) * INV_SCALE, 1.0f, 1.0f, 1.0f);
        if (m_Channels == 2)
            return Vec4(*(p + ind) * INV_SCALE, *(p + ind + 1) * INV_SCALE, 1.0f, 1.0f);
    }

    // if (m_Channels == 3)
    // {
    //     res.r = m_textureBufferUC[ind + 0] * INV_SCALE;
    //     res.g = m_textureBufferUC[ind + 1] * INV_SCALE;
    //     res.b = m_textureBufferUC[ind + 2] * INV_SCALE;
    //     res.a = 1.0f;
    // }
    // else if (m_Channels == 4)
    // {
    //     res.r = m_textureBufferUC[ind + 0] * INV_SCALE;
    //     res.g = m_textureBufferUC[ind + 1] * INV_SCALE;
    //     res.b = m_textureBufferUC[ind + 2] * INV_SCALE;
    //     res.a = m_textureBufferUC[ind + 3] * INV_SCALE;
    // }
    return res;
}

std::ostream &operator<<(std::ostream &out, const Texture &texture)
{
    out << texture.GetWidth() << " " << texture.GetHeight() << " " << texture.GetChannels() << std::endl;
    return out;
}

CubeMap::CubeMap()
{
    cubeImage.resize(6, nullptr);
}

CubeMap::CubeMap(Texture *rightTex, Texture *leftTex,
                 Texture *upTex, Texture *bottomTex,
                 Texture *frontTex, Texture *backTex)
{
    cubeImage.resize(6, nullptr);
    cubeImage[right].reset(rightTex);
    cubeImage[left].reset(leftTex);
    cubeImage[up].reset(upTex);
    cubeImage[bottom].reset(bottomTex);
    cubeImage[front].reset(frontTex);
    cubeImage[back].reset(backTex);
}

CubeMap::CubeMap(const std::string &filename)
{
    cubeImage.resize(6, nullptr);
    const char *extension = strrchr(filename.c_str(), '.') + 1;
    if (strcmp(extension, "hdr") != 0)
    {
        std::cout << "CubeMap should use the HDR file" << std::endl;
    }
    cubeImage.reserve(6);

    std::shared_ptr<Texture> image = std::make_shared<Texture>(filename);
    int width = image->GetWidth();
    int height = image->GetHeight();
    int channels = image->GetChannels();
    const int CUBEMAP_SIZE = 512;

    for (int face = 0; face < 6; ++face)
    {
        std::shared_ptr<Texture> tmp = std::make_shared<Texture>(CUBEMAP_SIZE, CUBEMAP_SIZE, channels, TextureRangeFormat::FLOAT);
        float *src = image->GetTextureDataHDR();
        float *dst = tmp->GetTextureDataHDR();
        for (int y = 0; y < CUBEMAP_SIZE; ++y)
        {
            for (int x = 0; x < CUBEMAP_SIZE; ++x)
            {
                float u = (x + 0.5f) / CUBEMAP_SIZE;
                float v = (y + 0.5f) / CUBEMAP_SIZE;
                u = 2.0f * u - 1.0f;
                v = 2.0f * v - 1.0f;

                // 根据面和 u, v 计算方向向量
                float dirX, dirY, dirZ;
                if (face == right)
                {
                    dirX = 1.0f;
                    dirY = -v;
                    dirZ = -u;
                }
                else if (face == left)
                {
                    dirX = -1.0f;
                    dirY = -v;
                    dirZ = u;
                }
                else if (face == bottom)
                {
                    dirX = u;
                    dirY = 1.0f;
                    dirZ = v;
                }
                else if (face == up)
                {
                    dirX = u;
                    dirY = -1.0f;
                    dirZ = -v;
                }
                else if (face == back)
                {
                    dirX = u;
                    dirY = -v;
                    dirZ = 1.0f;
                }
                else if (face == front)
                {
                    dirX = -u;
                    dirY = -v;
                    dirZ = -1.0f;
                }

                // 归一化方向向量
                float length = std::sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
                dirX /= length;
                dirY /= length;
                dirZ /= length;

                // 映射方向向量到 HDR 图像坐标
                int hdrX = static_cast<int>((0.5f + std::atan2(dirZ, dirX) / (2.0f * M_PI)) * width);
                int hdrY = static_cast<int>((0.5f - std::asin(dirY) / M_PI) * height);

                // 获取像素颜色
                int hdrIndex = (hdrY * width + hdrX) * channels;
                int cubemapIndex = (y * CUBEMAP_SIZE + x) * 3;
                dst[cubemapIndex + 0] = src[hdrIndex + 0];
                dst[cubemapIndex + 1] = src[hdrIndex + 1];
                dst[cubemapIndex + 2] = src[hdrIndex + 2];
            }
        }
        cubeImage[face] = tmp;
    }
}

void CubeMap::SetTexture(int index, const std::shared_ptr<Texture> &texture)
{
    if (index < 0 || index >= 6)
    {
        std::cout << "invalid index: " << index << std::endl;
        return;
    }
    cubeImage[index] = texture;
}

CubeMap::~CubeMap()
{
}

Vec4 CubeMap::SampleCubeMap(const Vec3 &dir) const
{
    int faceIndex = GetFaceID(dir);
    Vec2 uv = GetUV(faceIndex, dir);
    return cubeImage[faceIndex]->SampleTexture(uv);
}

Vec2 CubeMap::GetUV(int index, const Vec3 &dir) const
{
    float u = 0.0f, v = 0.0f, factor;
    // factor归一化，永远是正值
    switch (index)
    {
    case right:
        factor = 1 / dir[0];
        u = 1 + dir[2] * factor;
        v = 1 + dir[1] * factor;
        break;
    case up:
        factor = 1 / dir[1];
        u = 1 + dir[0] * factor;
        v = 1 + dir[2] * factor;

        break;
    case front:
        factor = 1 / dir[2];
        u = 1 - dir[0] * factor;
        v = 1 + dir[1] * factor;
        break;
    case left:
        factor = -1 / dir[0];
        u = 1 - dir[2] * factor;
        v = 1 + dir[1] * factor;
        break;
    case bottom:
        factor = -1 / dir[1];
        u = 1 + dir[0] * factor;
        v = 1 - dir[2] * factor;

        break;
    case back:
        factor = -1 / dir[2];
        u = 1 + dir[0] * factor;
        v = 1 + dir[1] * factor;
        break;
    }
    return Vec2(u / 2, v / 2);
}

Vec3 CubeMap::GetCubeViewWolrdPos(int index, int x, int y, float imageLength)
{
    // nx,ny,nz 的原点在图像的中心，要加上0.5偏移，图像归一化是[-0.5,0.5]*[-0.5,0.5]，而另一个固定坐标范围自然也是0.5
    float nx = 0.0f, ny = 0.0f, nz = 0.0f;
    switch (index)
    {
    case right:
        nx = 0.5f;
        ny = -0.5f + y / imageLength;
        nz = -0.5f + x / imageLength;
        break;
    case up:
        nx = -0.5f + x / imageLength;
        ny = 0.5f;
        nz = -0.5f + y / imageLength;
        break;
    case front:
        nx = 0.5f - x / imageLength;
        ny = -0.5f + y / imageLength;
        nz = 0.5f;
        break;
    case left:
        nx = -0.5f;
        ny = -0.5f + y / imageLength;
        nz = 0.5f - x / imageLength;
        break;
    case bottom:
        nx = -0.5f + x / imageLength;
        ny = -0.5f;
        nz = 0.5f - y / imageLength;
        break;
    case back:
        nx = -0.5f + x / imageLength;
        ny = -0.5f + y / imageLength;
        nz = -0.5f;

        break;
    default:
        break;
    }
    return Vec3(nx, ny, nz);
}

int CubeMap::GetFaceID(const Vec3 &dir) const
{
    int AbsMaxInd = 0;
    for (int i = 1; i < 3; ++i)
    {
        if (std::abs(dir[i]) > std::abs(dir[AbsMaxInd]))
            AbsMaxInd = i;
    }
    return AbsMaxInd + (dir[AbsMaxInd] < 0 ? 3 : 0);
}

std::shared_ptr<Texture> &CubeMap::GetTexture(int index)
{
    return cubeImage[index];
}
