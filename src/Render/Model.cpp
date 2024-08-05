#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>
Model::Model(const std::string &filename)
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
        loadObjModel(filename);
    else
        std::cout << "invalid file type" << std::endl;
}

Mat4x4 Model::SetSize(float sx, float sy, float sz) const
{
    float length = fabs(maxPoint.x - minPoint.x);
    float scaleFactor = 1.0f / length;
    Mat4x4 result;
    result.SetScale(Vec3(sx * scaleFactor, sy * scaleFactor, sz * scaleFactor));
    return result;
}

Model::~Model()
{
}

void Model::loadObjModel(const std::string &filename)
{
    std::ifstream file;

    file.open(filename, std::ifstream::in);
    std::cout << "file_name : " << filename << std::endl;
    if (file.fail())
    {
        std::cout << "Could not open file:" << filename << std::endl;
        return;
    }
    std::string line;
    minPoint = Vec3(+10000000000, +10000000000, +10000000000);
    maxPoint = Vec3(-10000000000, -10000000000, -10000000000);
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> texcoords;
    while (!file.eof())
    {
        std::getline(file, line);
        std::istringstream buf(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            buf >> trash; // trash: filter "v"
            Vec3 vertex;
            buf >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
            if (minPoint.x > vertex.x)
                minPoint.x = vertex.x;
            if (minPoint.y > vertex.y)
                minPoint.y = vertex.y;
            if (minPoint.z > vertex.z)
                minPoint.z = vertex.z;
            if (maxPoint.x < vertex.x)
                maxPoint.x = vertex.x;
            if (maxPoint.y < vertex.y)
                maxPoint.y = vertex.y;
            if (maxPoint.z < vertex.z)
                maxPoint.z = vertex.z;
        }

        else if (!line.compare(0, 3, "vn "))
        {
            buf >> trash >> trash; // trash: filter "vn"
            Vec3 normal;
            buf >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (!line.compare(0, 3, "vt "))
        {
            buf >> trash >> trash; // trash: filter "vt"
            Vec2 texcoord;
            buf >> texcoord.x >> texcoord.y; // the vt is the representation of 0.588, 0.975, 0.000
            texcoords.push_back(texcoord);
        }
        else if (!line.compare(0, 2, "f "))
        {
            buf >> trash; // trash: filter "f"
            int index[3];

            while (buf >> index[0] >> trash >> index[1] >> trash >> index[2])
            {
                Vertex data;
                data.position = vertices[index[0] - 1];
                data.texcoord = texcoords[index[1] - 1];
                data.normal = normals[index[2] - 1];
                data.color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);

                m_indices.push_back(m_vertices.size());
                m_vertices.push_back(data);
            }
        }
    }
    file.close();
    return;
}
