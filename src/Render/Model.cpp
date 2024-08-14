#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>
Model::Model(const std::string &filename)
{
    std::string fileStr = filename;
    m_objectNum = 0;
    m_minPoint = Vec3(+10000000000, +10000000000, +10000000000);
    m_maxPoint = Vec3(-10000000000, -10000000000, -10000000000);
    size_t lastDotPos = fileStr.find_last_of('.');
    if (lastDotPos == std::string::npos)
    {
        std::cout << "Could not find file extension" << std::endl;
        return;
    }
    std::string fileTypeStr = fileStr.substr(lastDotPos + 1, fileStr.length() - lastDotPos);

    if (fileTypeStr == "obj")
    {
        AddObjModel(filename);
    }
    else
        std::cout << "invalid file type" << std::endl;

    size_t lastSlashPos = fileStr.find_last_of("\\/");

    if (lastDotPos != std::string::npos && lastDotPos > lastSlashPos)
    {
        m_name = fileStr.substr(lastSlashPos + 1, lastDotPos - lastSlashPos - 1); // 文件名
    }
}

Model::Model(const std::initializer_list<std::string> &list)
{
    std::string fileStr;
    m_objectNum = 0;
    size_t lastDotPos;
    std::string fileTypeStr;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        fileStr = *it;
        lastDotPos = fileStr.find_last_of('.');
        if (lastDotPos == std::string::npos)
        {
            std::cout << "Could not find file extension" << std::endl;
            return;
        }
        fileTypeStr = fileStr.substr(lastDotPos + 1, fileStr.length() - lastDotPos);
        if (fileStr == "obj")
            AddObjModel(fileStr);
        else
        {
            std::cout << "invalid file type" << std::endl;
            return;
        }

        size_t lastSlashPos = fileStr.find_last_of("\\/");
        if (lastDotPos != std::string::npos && lastDotPos > lastSlashPos)
        {
            m_name = fileStr.substr(lastSlashPos + 1, lastDotPos - lastSlashPos - 1); // 文件名
        }
    }
}

Model::Model(const Mesh *mesh)
{
    m_objectNum = 1;
}

Mat4x4 Model::SetSize(float sx, float sy, float sz) const
{
    float length = fabs(m_maxPoint.x - m_minPoint.x);
    float scaleFactor = 1.0f / length;
    Mat4x4 result;
    result.SetScale(Vec3(sx * scaleFactor, sy * scaleFactor, sz * scaleFactor));
    return result;
}

void Model::AddObjModel(const std::string &filename)
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

    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> texcoords;

    bool flag = false;
    while (!file.eof())
    {
        std::getline(file, line);
        std::istringstream buf(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            if (!flag)
            {
                m_objectNum++;
                Object o;
                m_objects.push_back(o);
                flag = true;
            }
            buf >> trash; // trash: filter "v"
            Vec3 vertex;
            buf >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
            if (m_minPoint.x > vertex.x)
                m_minPoint.x = vertex.x;
            if (m_minPoint.y > vertex.y)
                m_minPoint.y = vertex.y;
            if (m_minPoint.z > vertex.z)
                m_minPoint.z = vertex.z;
            if (m_maxPoint.x < vertex.x)
                m_maxPoint.x = vertex.x;
            if (m_maxPoint.y < vertex.y)
                m_maxPoint.y = vertex.y;
            if (m_maxPoint.z < vertex.z)
                m_maxPoint.z = vertex.z;
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
            if (flag)
                flag = false;
            buf >> trash; // trash: filter "f"
            int index[3];

            while (buf >> index[0] >> trash >> index[1] >> trash >> index[2])
            {
                Vertex data;
                data.position = vertices[index[0] - 1];
                data.texcoord = texcoords[index[1] - 1];
                data.normal = normals[index[2] - 1];
                data.color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
                int offset = m_objects[m_objectNum - 1].m_mesh.m_vertices.size();
                m_objects[m_objectNum - 1].m_mesh.m_indices.push_back(offset);
                m_objects[m_objectNum - 1].m_mesh.m_vertices.push_back(data);
            }
        }
    }
    file.close();
    return;
}

void Model::AddObjModel(Object &obj)
{
    m_objects.push_back(obj);
    m_objectNum++;
}
