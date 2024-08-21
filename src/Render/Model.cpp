#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Vertex.h"
Model::Model(const std::string &filename, const std::string &name)
{
    std::string fileStr = filename;
    m_objectNum = 0;
    m_minPoint = Vec3(+10000000000, +10000000000, +10000000000);
    m_maxPoint = Vec3(-10000000000, -10000000000, -10000000000);
    size_t lastDotPos = fileStr.find_last_of('.');
    size_t lastSlashPos = fileStr.find_last_of("\\/");
    if (name != "Unknown")
        m_name = name;
    else if (lastDotPos != std::string::npos && lastDotPos > lastSlashPos)
    {
        m_name = fileStr.substr(lastSlashPos + 1, lastDotPos - lastSlashPos - 1); // 文件名
    }

    if (lastDotPos == std::string::npos)
    {
        std::cout << "Could not find file extension" << std::endl;
        return;
    }
    std::string fileTypeStr = fileStr.substr(lastDotPos + 1, fileStr.length() - lastDotPos);

    if (fileTypeStr == "obj")
    {
        AddObject(filename);
        m_transform = {Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)};
    }
    else
        std::cout << "invalid file type" << std::endl;
}

Model::Model(Mesh *meshPtr, const std::string &name) : m_objectNum(0), m_minPoint(Vec3(+10000000000, +10000000000, +10000000000)),
                                                       m_maxPoint(Vec3(-10000000000, -10000000000, -10000000000)), m_name(name)
{
    m_objectNum++;
    Object o;
    m_objects.push_back(o);
    m_objects[0].m_mesh.reset(meshPtr);
    m_objects[0].m_mesh->m_name = name + "-element" + std::to_string(m_objectNum);
    m_transform = {Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)};
}

void Model::AddObject(const std::string &filename)
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
    std::vector<int> vertID;
    std::vector<Vec3> normals;
    std::vector<Vec2> texcoords;
    std::vector<Vec4> tangents;

    bool flag = false;
    bool hasFileTangent = false;

    while (!file.eof())
    {
        std::getline(file, line);
        std::istringstream buf(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            if (!flag)
            {
                // add tangent
                if (m_objectNum != 0)
                {
                    BuildTangents(tangents, m_objects[m_objectNum - 1].m_mesh.get(), hasFileTangent, vertID);
                    hasFileTangent = false;
                }
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
            {
                flag = false;
                m_objects[m_objectNum - 1].m_mesh->m_name = m_name + "-element" + std::to_string(m_objectNum);
            }
            buf >> trash; // trash: filter "f"
            int index[3];

            while (buf >> index[0] >> trash >> index[1] >> trash >> index[2])
            {
                Vertex data;
                data.position = vertices[index[0] - 1];
                data.texcoord = texcoords[index[1] - 1];
                data.normal = normals[index[2] - 1];
                data.color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
                vertID.push_back(index[0] - 1); // tangent's number is the same as the vertex, so record the vertID
                int offset = m_objects[m_objectNum - 1].m_mesh->m_vertices.size();
                m_objects[m_objectNum - 1].m_mesh->m_indices.push_back(offset);
                m_objects[m_objectNum - 1].m_mesh->m_vertices.push_back(data);
            }
        }
        else if (!line.compare(0, 14, "# ext.tangent "))
        {

            hasFileTangent = true;
            line = line.substr(14);
            std::istringstream iss(line);
            Vec4 tangent;
            iss >> tangent.x;
            iss >> tangent.y;
            iss >> tangent.z;
            iss >> tangent.w;
            tangents.push_back(tangent);
        }
    }
    if (!flag)
    {
        // add tangnet
        if (m_objectNum != 0)
        {
            BuildTangents(tangents, m_objects[m_objectNum - 1].m_mesh.get(), hasFileTangent, vertID);
        }
    }

    file.close();
    return;
}

void Model::AddObject(Object &obj)
{
    m_objects.push_back(obj);
    m_objectNum++;
}

void Model::SetScale(Vec3 &s)
{
    float length = fabs(m_maxPoint.x - m_minPoint.x);
    float scaleFactor = 1.0f / length;

    m_transform.scale = s * scaleFactor;
}

void Model::BuildTangents(std::vector<Vec4> &tangents, Mesh *mesh, bool hasFileTangent, std::vector<int> &vertID)
{
    if (hasFileTangent)
    {
        for (size_t i = 0; i < mesh->m_indices.size(); i += 3)
        {
            mesh->m_vertices[i].tangent = tangents[vertID[i]];
            mesh->m_vertices[i + 1].tangent = tangents[vertID[i + 1]];
            mesh->m_vertices[i + 2].tangent = tangents[vertID[i + 2]];
        }
    }
    else
    {
        for (size_t i = 0; i < mesh->m_indices.size(); i += 3)
        {
            mesh->m_vertices[i].tangent = Vertex::CalTangent(mesh->m_vertices[i], mesh->m_vertices[i + 1], mesh->m_vertices[i + 2]);
            mesh->m_vertices[i + 1].tangent = mesh->m_vertices[i].tangent;
            mesh->m_vertices[i + 2].tangent = mesh->m_vertices[i].tangent;
        }
    }
}
