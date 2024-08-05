#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>
Model::Model(const char *filename) : m_diffuseTexture(nullptr),
                                     m_normalTexture(nullptr),
                                     m_specularTexture(nullptr)
{
    std::string fileStr = filename;
    size_t dotLastPos = fileStr.find_last_of('.');
    if (dotLastPos == std::string::npos)
    {
        std::cout << "Could not find file extension" << std::endl;
        return;
    }
    std::string fileTypeStr = fileStr.substr(dotLastPos + 1, fileStr.length() - dotLastPos);
    if (fileTypeStr == "obj")
    {
        loadObjModel(filename);
    }
    else
    {
        std::cout << "invalid file type" << std::endl;
    }
    std::cout << "file_name : " << filename << std::endl;
    std::cout << "vertex_number = " << m_Vertices.size() << std::endl;
    std::cout << "vertex_normal_number = " << m_Normals.size() << std::endl;
    std::cout << "vertex_tex_coord_number = " << m_UVCoords.size() << std::endl;
    std::cout << "faces_number = " << m_Faces.size() << std::endl;
}

Model::Model(const Model &model) : m_Vertices(model.m_Vertices), m_UVCoords(model.m_UVCoords),
                                   m_Normals(model.m_Normals), m_Faces(model.m_Faces),
                                   m_diffuseTexture(model.m_diffuseTexture), m_normalTexture(model.m_normalTexture),
                                   m_specularTexture(model.m_specularTexture)
{
}

Model::~Model()
{
    if (m_diffuseTexture)
        delete m_diffuseTexture;
    if (m_normalTexture)
        delete m_normalTexture;
    if (m_specularTexture)
        delete m_specularTexture;

    m_diffuseTexture = nullptr;
    m_normalTexture = nullptr;
    m_specularTexture = nullptr;
}
Model &Model::operator=(const Model &model)
{
    if (&model == this)
        return *this;
    this->m_diffuseTexture = model.m_diffuseTexture;
    this->m_Vertices = model.m_Vertices;
    this->m_UVCoords = model.m_UVCoords;
    this->m_Normals = model.m_Normals;

    this->m_Faces = model.m_Faces;

    this->m_diffuseTexture = model.m_diffuseTexture;
    this->m_normalTexture = model.m_normalTexture;
    this->m_specularTexture = model.m_specularTexture;
    return *this;
}

void Model::loadObjModel(const char *filename)
{
    std::ifstream file;

    file.open(filename, std::ifstream::in);

    if (file.fail())
    {
        std::cout << "Could not open file:" << filename << std::endl;
        assert(0 == 1);
        return;
    }
    std::string line = "";
    while (!file.eof())
    {
        std::getline(file, line);
        std::istringstream buf(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            buf >> trash; // trash: filter "v"
            Vec3 v;
            buf >> v.x >> v.y >> v.z;
            m_Vertices.push_back(v);
        }
        else if (!line.compare(0, 3, "vt "))
        {
            buf >> trash >> trash; // trash: filter "vt"
            Vec2 vt;
            buf >> vt.x >> vt.y; // the vt is the representation of 0.588, 0.975, 0.000
            m_UVCoords.push_back(vt);
        }
        else if (!line.compare(0, 3, "vn "))
        {
            buf >> trash >> trash; // trash: filter "vn"
            Vec3 vn;
            buf >> vn.x >> vn.y >> vn.z;
            m_Normals.push_back(vn);
        }
        else if (!line.compare(0, 2, "f "))
        {
            buf >> trash; // trash: filter "f"
            int count = 0;
            Vec3 face;
            std::vector<Vec3> f;

            while (buf >> face.x >> trash >> face.y >> trash >> face.z)
            {
                face.x--;
                face.y--;
                face.z--;
                f.push_back(face);
                count++;
            }
            m_Faces.push_back(f);
            if (count != 3)
            {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                return;
            }
        }
    }
    file.close();
    return;
}

void Model::SetDiffuse(const char *diffuseFileName)
{
    if (m_diffuseTexture)
        delete m_diffuseTexture;
    m_diffuseTexture = new Texture2D(diffuseFileName);
}

void Model::SetNormal(const char *normalFileName)
{
    if (m_normalTexture)
        delete m_normalTexture;
    m_normalTexture = new Texture2D(normalFileName);
}

void Model::SetSpecular(const char *specularFileName)
{
    if (m_specularTexture)
        delete m_specularTexture;
    m_specularTexture = new Texture2D(specularFileName);
}

Vec4 Model::GetDiffuseColor(Vec2 &uv)
{
    if (!m_diffuseTexture)
    {
        std::cerr << "Error: the diffuse texture doesn't exist" << std::endl;
        return Vec4();
    }
    return m_diffuseTexture->SampleTexture(uv);
}

Vec4 Model::GetNormalColor(Vec2 &uv)
{
    if (!m_normalTexture)
    {
        std::cerr << "Error: the normal texture doesn't exist" << std::endl;
        return Vec4();
    }
    Vec4 c = m_normalTexture->SampleTexture(uv);
    Vec4 res;
    for (int i = 0; i < 3; i++)
        res[i] = (float)c[i] * 2.f - 1.f;
    res[3] = 0.0f;
    return res;
}

float Model::GetSpecularColor(Vec2 &uv)
{
    if (!m_specularTexture)
    {
        std::cerr << "Error: the specular texture doesn't exist" << std::endl;
        return 1.0f;
    }

    return m_specularTexture->SampleTexture(uv)[0];
}
