#include "Texture2D.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <string>
#include <fstream>
#include <iostream>

namespace SurgeNight
{

Texture2D::Texture2D(const std::string &filename, const int index, const int type, const bool reverse) : m_id(0), m_index(index), m_type(type)
{
    if (m_type < TEXTURE_DIFFUSE || m_type > TEXTURE_HEIGHT)
        m_type = TEXTURE_DIFFUSE;
    glGenTextures(1, &m_id);
    reloadFile(filename, index, reverse);
}

Texture2D::~Texture2D()
{
    // glDeleteTextures(GL_TEXTURE_2D, m_id);
}

bool Texture2D::reloadFile(const std::string &filename, const int index, const bool reverse)
{
    m_index = index;
    m_filename = "";
    glBindTexture(GL_TEXTURE_2D, m_id);
    unsigned char *data = stbi_load(filename.c_str(), &m_width, &m_height, &m_clrChanls, 0);
    if (NULL == data) {
        std::cerr << "Error: Image load error!" << std::endl;
        return false;
    }
    int clrmode = (m_clrChanls == 3 ? GL_RGB : (m_clrChanls == 1 ? GL_RED : GL_RGBA));

    stbi_set_flip_vertically_on_load(reverse);

    glTexImage2D(GL_TEXTURE_2D, 0, clrmode, m_width, m_height, 0, clrmode, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    m_filename = filename;
    return true;
}

}
