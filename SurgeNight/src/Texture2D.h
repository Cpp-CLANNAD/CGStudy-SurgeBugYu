#ifndef SN_TEXTURE_2D_H
#define SN_TEXTURE_2D_H

#include "glad/glad.h"
#include <string>

namespace SurgeNight
{
    class Texture2D
    {
    public:
        Texture2D(const std::string &filename, const int index = 0);
        ~Texture2D();

        void use() {
                glActiveTexture(GL_TEXTURE0 + m_index);
                glBindTexture(GL_TEXTURE_2D, m_id);
        }
        bool reloadFile(const std::string &filename, const int index = 0);
        bool isVaild() const { return 0 != m_id; }
        unsigned int getId() const { return m_id; }
        int getIndex() const { return m_index; }

    private:
        unsigned int m_id;
        int m_width, m_height, m_clrChanls, m_index;
    };
}

#endif // SN_TEXTURE_2D_H
