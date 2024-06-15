#ifndef MODEL_H
#define MODEL_H
#include "Math/Vec.h"
#include <vector>
#include <string>
class Model
{

public:
    Model(char const *filename);
    ~Model() = default;
    void loadModel(const char *filename);

    void loadObjModel(const char *filename);
    Vec3f GetVetices(int i) { return m_Vetices[i]; }
    std::vector<int> GetFaces(int i) { return m_Faces[i]; }
    int GetVerticesSize() { return m_VeticesSize; }
    int GetFacesSize() { return m_FacesSize; }

private:
    std::vector<Vec3f> m_Vetices;
    std::vector<std::vector<int>> m_Faces;
    int m_VeticesSize;
    int m_FacesSize;
};

#endif // MODEL_H