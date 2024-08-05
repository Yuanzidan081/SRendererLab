#include "Mesh.h"

void Mesh::asBox(double width, double height, double depth)
{
    m_vertices.resize(24);
    m_indices.resize(36);

    float halfW = width * 0.5f;
    float halfH = height * 0.5f;
    float halfD = depth * 0.5f;
    // front
    m_vertices[0].position = Vec3(halfW, halfH, halfD);
    m_vertices[0].normal = Vec3(0.f, 0.f, 1.f);
    m_vertices[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
    m_vertices[0].texcoord = Vec2(1.f, 1.f);
    m_vertices[1].position = Vec3(-halfW, halfH, halfD);
    m_vertices[1].normal = Vec3(0.f, 0.f, 1.f);
    m_vertices[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
    m_vertices[1].texcoord = Vec2(0.f, 1.f);
    m_vertices[2].position = Vec3(-halfW, -halfH, halfD);
    m_vertices[2].normal = Vec3(0.f, 0.f, 1.f);
    m_vertices[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
    m_vertices[2].texcoord = Vec2(0.f, 0.f);
    m_vertices[3].position = Vec3(halfW, -halfH, halfD);
    m_vertices[3].normal = Vec3(0.f, 0.f, 1.f);
    m_vertices[3].color = Vec4(0.f, 1.f, 1.f, 1.f);
    m_vertices[3].texcoord = Vec2(1.f, 0.f);
    // left
    m_vertices[4].position = Vec3(-halfW, +halfH, halfD);
    m_vertices[4].normal = Vec3(-1.f, 0.f, 0.f);
    m_vertices[4].color = Vec4(0.f, 0.f, 1.f, 1.f);
    m_vertices[4].texcoord = Vec2(1.f, 1.f);
    m_vertices[5].position = Vec3(-halfW, +halfH, -halfD);
    m_vertices[5].normal = Vec3(-1.f, 0.f, 0.f);
    m_vertices[5].color = Vec4(1.f, 1.f, 0.f, 1.f);
    m_vertices[5].texcoord = Vec2(0.f, 1.f);
    m_vertices[6].position = Vec3(-halfW, -halfH, -halfD);
    m_vertices[6].normal = Vec3(-1.f, 0.f, 0.f);
    m_vertices[6].color = Vec4(0.f, 1.f, 0.f, 1.f);
    m_vertices[6].texcoord = Vec2(0.f, 0.f);
    m_vertices[7].position = Vec3(-halfW, -halfH, halfD);
    m_vertices[7].normal = Vec3(-1.f, 0.f, 0.f);
    m_vertices[7].color = Vec4(1.f, 1.f, 1.f, 1.f);
    m_vertices[7].texcoord = Vec2(1.f, 0.f);
    // back
    m_vertices[8].position = Vec3(-halfW, +halfH, -halfD);
    m_vertices[8].normal = Vec3(0.f, 0.f, -1.f);
    m_vertices[8].color = Vec4(1.f, 0.f, 1.f, 1.f);
    m_vertices[8].texcoord = Vec2(0.f, 0.f);
    m_vertices[9].position = Vec3(+halfW, +halfH, -halfD);
    m_vertices[9].normal = Vec3(0.f, 0.f, -1.f);
    m_vertices[9].color = Vec4(0.f, 1.f, 1.f, 1.f);
    m_vertices[9].texcoord = Vec2(1.f, 0.f);
    m_vertices[10].position = Vec3(+halfW, -halfH, -halfD);
    m_vertices[10].normal = Vec3(0.f, 0.f, -1.f);
    m_vertices[10].color = Vec4(1.f, 1.f, 0.f, 1.f);
    m_vertices[10].texcoord = Vec2(1.f, 1.f);
    m_vertices[11].position = Vec3(-halfW, -halfH, -halfD);
    m_vertices[11].normal = Vec3(0.f, 0.f, -1.f);
    m_vertices[11].color = Vec4(0.f, 0.f, 1.f, 1.f);
    m_vertices[11].texcoord = Vec2(0.f, 1.f);
    // right
    m_vertices[12].position = Vec3(halfW, +halfH, -halfD);
    m_vertices[12].normal = Vec3(1.f, 0.f, 0.f);
    m_vertices[12].color = Vec4(0.f, 1.f, 0.f, 1.f);
    m_vertices[12].texcoord = Vec2(0.f, 0.f);
    m_vertices[13].position = Vec3(halfW, +halfH, +halfD);
    m_vertices[13].normal = Vec3(1.f, 0.f, 0.f);
    m_vertices[13].color = Vec4(1.f, 0.f, 0.f, 1.f);
    m_vertices[13].texcoord = Vec2(1.f, 0.f);
    m_vertices[14].position = Vec3(halfW, -halfH, +halfD);
    m_vertices[14].normal = Vec3(1.f, 0.f, 0.f);
    m_vertices[14].color = Vec4(0.f, 1.f, 1.f, 1.f);
    m_vertices[14].texcoord = Vec2(1.f, 1.f);
    m_vertices[15].position = Vec3(halfW, -halfH, -halfD);
    m_vertices[15].normal = Vec3(1.f, 0.f, 0.f);
    m_vertices[15].color = Vec4(1.f, 0.f, 1.f, 1.f);
    m_vertices[15].texcoord = Vec2(0.f, 1.f);
    // top
    m_vertices[16].position = Vec3(+halfW, halfH, -halfD);
    m_vertices[16].normal = Vec3(0.f, 1.f, 0.f);
    m_vertices[16].color = Vec4(0.f, 0.f, 0.f, 1.f);
    m_vertices[16].texcoord = Vec2(0.f, 0.f);
    m_vertices[17].position = Vec3(-halfW, halfH, -halfD);
    m_vertices[17].normal = Vec3(0.f, 1.f, 0.f);
    m_vertices[17].color = Vec4(1.f, 1.f, 0.f, 1.f);
    m_vertices[17].texcoord = Vec2(1.f, 0.f);
    m_vertices[18].position = Vec3(-halfW, halfH, halfD);
    m_vertices[18].normal = Vec3(0.f, 1.f, 0.f);
    m_vertices[18].color = Vec4(0.f, 1.f, 1.f, 1.f);
    m_vertices[18].texcoord = Vec2(1.f, 1.f);
    m_vertices[19].position = Vec3(+halfW, halfH, halfD);
    m_vertices[19].normal = Vec3(0.f, 1.f, 0.f);
    m_vertices[19].color = Vec4(1.f, 0.f, 0.f, 1.f);
    m_vertices[19].texcoord = Vec2(0.f, 1.f);
    // down
    m_vertices[20].position = Vec3(+halfW, -halfH, -halfD);
    m_vertices[20].normal = Vec3(0.f, -1.f, 0.f);
    m_vertices[20].color = Vec4(0.f, 0.f, 1.f, 1.f);
    m_vertices[20].texcoord = Vec2(0.f, 0.f);
    m_vertices[21].position = Vec3(+halfW, -halfH, +halfD);
    m_vertices[21].normal = Vec3(0.f, -1.f, 0.f);
    m_vertices[21].color = Vec4(1.f, 1.f, 1.f, 1.f);
    m_vertices[21].texcoord = Vec2(1.f, 0.f);
    m_vertices[22].position = Vec3(-halfW, -halfH, +halfD);
    m_vertices[22].normal = Vec3(0.f, -1.f, 0.f);
    m_vertices[22].color = Vec4(0.f, 1.f, 0.f, 1.f);
    m_vertices[22].texcoord = Vec2(1.f, 1.f);
    m_vertices[23].position = Vec3(-halfW, -halfH, -halfD);
    m_vertices[23].normal = Vec3(0.f, -1.f, 0.f);
    m_vertices[23].color = Vec4(1.f, 0.f, 1.f, 1.f);
    m_vertices[23].texcoord = Vec2(0.f, 1.f);

    // front
    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;
    m_indices[3] = 0;
    m_indices[4] = 2;
    m_indices[5] = 3;
    // left
    m_indices[6] = 4;
    m_indices[7] = 5;
    m_indices[8] = 6;
    m_indices[9] = 4;
    m_indices[10] = 6;
    m_indices[11] = 7;
    // back
    m_indices[12] = 8;
    m_indices[13] = 9;
    m_indices[14] = 10;
    m_indices[15] = 8;
    m_indices[16] = 10;
    m_indices[17] = 11;
    // right
    m_indices[18] = 12;
    m_indices[19] = 13;
    m_indices[20] = 14;
    m_indices[21] = 12;
    m_indices[22] = 14;
    m_indices[23] = 15;
    // top
    m_indices[24] = 16;
    m_indices[25] = 17;
    m_indices[26] = 18;
    m_indices[27] = 16;
    m_indices[28] = 18;
    m_indices[29] = 19;
    // down
    m_indices[30] = 20;
    m_indices[31] = 21;
    m_indices[32] = 22;
    m_indices[33] = 20;
    m_indices[34] = 22;
    m_indices[35] = 23;
}

void Mesh::asFloor(double length, double height)
{
    m_vertices.resize(4);
    m_indices.resize(6);
    m_vertices[0].position = Vec3(+length * 0.5f, height, -length * 0.5f);
    m_vertices[0].normal = Vec3(0.f, 1.f, 0.f);
    m_vertices[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
    m_vertices[0].texcoord = Vec2(0.f, 0.f);
    m_vertices[1].position = Vec3(-length * 0.5f, height, -length * 0.5f);
    m_vertices[1].normal = Vec3(0.f, 1.f, 0.f);
    m_vertices[1].color = Vec4(0.f, 0.f, 0.f, 1.f);
    m_vertices[1].texcoord = Vec2(1.f, 0.f);
    m_vertices[2].position = Vec3(-length * 0.5f, height, +length * 0.5f);
    m_vertices[2].normal = Vec3(0.f, 1.f, 0.f);
    m_vertices[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
    m_vertices[2].texcoord = Vec2(1.f, 1.f);
    m_vertices[3].position = Vec3(+length * 0.5f, height, +length * 0.5f);
    m_vertices[3].normal = Vec3(0.f, 1.f, 0.f);
    m_vertices[3].color = Vec4(0.f, 0.f, 0.f, 1.f);
    m_vertices[3].texcoord = Vec2(0.f, 1.f);
    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;
    m_indices[3] = 0;
    m_indices[4] = 2;
    m_indices[5] = 3;
}

void Mesh::asTriangle(const Vec3 p1, const Vec3 p2, const Vec3 p3)
{
    m_vertices.resize(3);
    m_indices.resize(3);
    m_vertices[0].position = p1;
    m_vertices[0].normal = Vec3(0.f, 0.f, 1.f);
    m_vertices[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
    m_vertices[0].texcoord = Vec2(0.f, 0.f);
    m_vertices[1].position = p2;
    m_vertices[1].normal = Vec3(0.f, 0.f, 1.f);
    m_vertices[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
    m_vertices[1].texcoord = Vec2(1.f, 0.f);
    m_vertices[2].position = p3;
    m_vertices[2].normal = Vec3(0.f, 0.f, 1.f);
    m_vertices[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
    m_vertices[2].texcoord = Vec2(0.5f, 1.f);
    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;
}
