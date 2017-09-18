#include "Texture2D.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <string>
#include <fstream>
#include <iostream>

namespace SurgeNight
{

Texture2D::Texture2D(const std::string &filename, const int index) : m_id(0), m_index(index)
{
    glGenTextures(1, &m_id);
    reloadFile(filename, index);
}

Texture2D::~Texture2D()
{
    // glDeleteTextures(GL_TEXTURE_2D, m_id);
}

bool Texture2D::reloadFile(const std::string &filename, const int index)
{
    m_index = index;
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.c_str(), &m_width, &m_height, &m_clrChanls, 0);
    if (NULL == data) {
        std::cerr << "Error: Image load error!" << std::endl;
        return false;
    }
    int clrmode = (m_clrChanls == 3 ? GL_RGB : GL_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, clrmode, m_width, m_height, 0, clrmode, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return true;
}

}
