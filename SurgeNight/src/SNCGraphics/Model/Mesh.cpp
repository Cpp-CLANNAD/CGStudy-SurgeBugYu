#include "Mesh.h"
#include "glad/glad.h"
#include <cstddef>
#include <iostream>

namespace SurgeNight
{

Mesh::Mesh() : m_VAO(0), m_VBO(0), m_EBO(0)
{
    // std::cout << "Constructor: " << m_VAO << " " << m_VBO << " " << m_EBO << std::endl;
}

Mesh::Mesh(const std::vector<Vertex> &vertexs, const std::vector<unsigned int> &indexs, std::vector<std::shared_ptr<Texture2D>> &textures) :
    m_vertexs(vertexs), m_vertexsIndex(indexs), m_textures(textures), m_VAO(0), m_VBO(0), m_EBO(0)
{
    // std::cout << "Constructor: " << m_VAO << " " << m_VBO << " " << m_EBO << std::endl;
    load();
}

Mesh::Mesh(const Mesh &mesh) : m_vertexs(mesh.m_vertexs), m_vertexsIndex(mesh.m_vertexsIndex), m_textures(mesh.m_textures), m_VAO(0), m_VBO(0), m_EBO(0)
{
    // std::cout << "Copy: " << m_VAO << " " << m_VBO << " " << m_EBO << std::endl;
    load();
}

Mesh& Mesh::operator=(const Mesh &mesh)
{
    this->~Mesh();
    m_vertexs = mesh.m_vertexs;
    m_vertexsIndex = mesh.m_vertexsIndex;
    m_textures = mesh.m_textures;
    load();
    return *this;
}

Mesh::~Mesh()
{
    // std::cout << "Destructor: " << m_VAO << " " << m_VBO << " " << m_EBO << std::endl;
    if (0 != m_VAO)
        glDeleteVertexArrays(1, &m_VAO);
    if (0 != m_VBO)
        glDeleteBuffers(1, &m_VBO);
    if (0 != m_EBO)
        glDeleteBuffers(1, &m_EBO);
}

void Mesh::registerTexture(ShaderProgram &shader,
                        const std::string &texture,
                        const std::string &diffuse,
                        const std::string &specular,
                        const std::string &normal,
                        const std::string &height)
{
    unsigned int itex = 0, idiff = 0, ispec = 0, inor = 0, iheig = 0;
    std::string name;
    for (auto &i : m_textures) {
        switch (i->getType()) {
            case Texture2D::TEXTURE_DIFFUSE:
                name = diffuse + std::to_string(idiff++);
                break;
            case Texture2D::TEXTURE_SPECULAR:
                name = specular + std::to_string(ispec++);
                break;
            case Texture2D::TEXTURE_NORMAL:
                name = normal + std::to_string(inor++);
                break;
            case Texture2D::TEXTURE_HEIGHT:
                name = height + std::to_string(iheig++);
                break;
            default:
                continue;
        }
        shader.setValue(name, i->getId());
        i->use();
    }
}

void Mesh::paint()
{
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_vertexsIndex.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::load()
{
    if (m_vertexs.empty() || m_vertexsIndex.empty())
        return;

    if (0 != m_VAO)
        glDeleteVertexArrays(1, &m_VAO);
    if (0 != m_VBO)
        glDeleteBuffers(1, &m_VBO);
    if (0 != m_EBO)
        glDeleteBuffers(1, &m_EBO);
    m_VAO = m_VBO = m_EBO = 0;

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertexs.size() * sizeof(Vertex), m_vertexs.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexsIndex.size() * sizeof(unsigned int), m_vertexsIndex.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, nor)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCor)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, tangent)));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, bitangent)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // std::cout << "Loading: " << m_VAO << " " << m_VBO << " " << m_EBO << std::endl;
}

}
