#include "Mesh.h"
#include "glad/glad.h"

namespace SurgeNight
{

Mesh::Mesh(const std::vector<Vertex> &vertexs, const std::vector<unsigned int> &indexs, std::vector<std::shared_ptr<Texture2D>> &textures) :
    m_vertexs(vertexs), m_vertexsIndex(indexs), m_textures(textures),
    m_VAO(0), m_VBO(0), m_EBO(0)
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(GL_ARRAY_BUFFER, 1, &m_VBO);
    glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, 1, &m_EBO);
    load();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(m_VAO);
    glDeleteBuffers(GL_ARRAY_BUFFER, m_VBO);
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void Mesh::paint()
{
    for ()
}

void Mesh::load()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    glBufferData(GL_ARRAY_BUFFER, m_vertexs.size() * sizeof(Vertex), m_vertexs.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexsIndex.size() * sizeof(unsigned int), m_vertexsIndex.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(std::offset(Vertex, nor)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(std::offset(Vertex, texCor)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(std::offset(Vertex, tangent)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(std::offset(Vertex, bitangent)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
