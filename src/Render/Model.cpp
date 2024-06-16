#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>
Model::Model(const char *filename)
{
    loadModel(filename);
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
            m_Vetices.push_back(v);
        }
        else if (!line.compare(0, 2, "f "))
        {
            buf >> trash; // trash: filter "f"
            std::vector<int> f;
            int itrash, vIdx; // itrash: filter "f"
            while (buf >> vIdx >> trash >> itrash >> trash >> itrash)
            {
                f.push_back(vIdx - 1);
            }
            m_Indices.push_back(f);
        }
    }
    m_VeticesSize = m_Vetices.size();
    m_IndicesSize = m_Indices.size();
    file.close();
    return;
}