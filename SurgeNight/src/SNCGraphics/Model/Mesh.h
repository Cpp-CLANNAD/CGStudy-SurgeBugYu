#ifndef SN_MESH_H
#define SN_MESH_H

#include <vector>
#include <memory>
#include "Vertex.h"
#include "Texture2D.h"

namespace SurgeNight
{

class Mesh
{
public:
    Mesh(const std::vector<Vertex> &vertexs, const std::vector<unsigned int> &indexs, std::vector<std::shared_ptr<Texture2D>> &textures);
    ~Mesh();

    void paint();

private:
    void load();

    std::vector<Vertex> m_vertexs;
    std::vector<unsigned int> m_vertexsIndex;
    std::vector<std::shared_ptr<Texture2D>> m_textures;
    unsigned int m_VAO, m_VBO, m_EBO;
};

}

#endif // SN_MESH_H
