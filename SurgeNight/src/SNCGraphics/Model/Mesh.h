#ifndef SN_MESH_H
#define SN_MESH_H

#include <vector>
#include <memory>
#include "Vertex.h"
#include "Texture2D.h"
#include "../ShaderProgram.h"

namespace SurgeNight
{

class Mesh
{
public:
    Mesh();
    Mesh(const std::vector<Vertex> &vertexs, const std::vector<unsigned int> &indexs, std::vector<std::shared_ptr<Texture2D>> &textures);
    ~Mesh();

    std::vector<Vertex>& getVertexs() { return m_vertexs; }
    std::vector<unsigned int>& getIndexes() { return m_vertexsIndex; }
    std::vector<std::shared_ptr<Texture2D>>& getTextures() { return m_textures; }

    void registerTexture(ShaderProgram &shader,
                         const std::string &texture = "texture",
                         const std::string &diffuse = "texture_diffuse",
                         const std::string &specular = "texture_specular",
                         const std::string &normal = "texture_normal",
                         const std::string &height = "texture_height");
    void paint();
    void load();

  private:

    std::vector<Vertex> m_vertexs;
    std::vector<unsigned int> m_vertexsIndex;
    std::vector<std::shared_ptr<Texture2D>> m_textures;
    unsigned int m_VAO, m_VBO, m_EBO;
};

}

#endif // SN_MESH_H
