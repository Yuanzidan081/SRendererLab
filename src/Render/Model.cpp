#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>
Model::Model(const char *filename)
{
    loadModel(filename);
}

Model::Model(const Model &model) : m_Vertices(model.GetFullVetices()), m_VIndices(model.GetFullVIndcies()),
                                   m_UVCoords(model.GetFullUVCoords()), m_UVIndices(model.GetFullUVIndices()),
                                   m_VerticesSize(model.GetVerticesSize()), m_VIndicesSize(model.GetVIndicesSize()),
                                   m_UVCoordsSize(model.GetUVCoordsSize()), m_UVIndicesSize(model.GetUVIndicesSize())

{
}

Model &Model::operator=(const Model &model)
{
    if (&model == this)
        return *this;
    m_Vertices = model.GetFullVetices();
    m_VIndices = model.GetFullVIndcies();
    m_VerticesSize = model.GetVerticesSize();
    m_VIndicesSize = model.GetVIndicesSize();
    return *this;
}

void Model::loadModel(const char *filename)
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
}
void Model::loadObjModel(const char *filename)
{
    std::ifstream file;

    file.open(filename, std::ifstream::in);

    if (file.fail())
    {
        std::cout << "Could not open file:" << filename << std::endl;
        assert(!file.fail());
        return;
    }
    // int i = 5;
    std::string line = "";
    while (!file.eof())
    {
        std::getline(file, line);
        std::istringstream buf(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            buf >> trash; // trash: filter "v"
            Vec3f v;
            buf >> v.x >> v.y >> v.z;
            m_Vertices.push_back(v);
        }
        else if (!line.compare(0, 3, "vt "))
        {
            buf >> trash >> trash; // trash: filter "vt"
            Vec2f vt;
            buf >> vt.x >> vt.y; // the vt is the representation of 0.588, 0.975, 0.000
            m_UVCoords.push_back(vt);
        }
        else if (!line.compare(0, 2, "f "))
        {
            buf >> trash; // trash: filter "f"
            std::vector<int> vIdxVec;
            std::vector<int> uvIndVec;
            int itrash, vIdx, uvIdx; // itrash: filter "f"

            while (buf >> vIdx >> trash >> uvIdx >> trash >> itrash)
            {

                vIdxVec.push_back(vIdx - 1);

                uvIndVec.push_back(uvIdx - 1);
            }
            m_VIndices.push_back(vIdxVec);
            m_UVIndices.push_back(uvIndVec);
        }
    }
    m_VerticesSize = m_Vertices.size();
    m_VIndicesSize = m_VIndices.size();
    m_UVCoordsSize = m_UVCoords.size();
    m_UVIndicesSize = m_UVIndices.size();
    file.close();
    return;
}