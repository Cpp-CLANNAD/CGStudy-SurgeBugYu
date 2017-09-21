#ifndef SN_TEXTURE_2D_H
#define SN_TEXTURE_2D_H

#include "glad/glad.h"
#include <string>

namespace SurgeNight
{
    class Texture2D
    {
    public:
        enum {
            TEXTURE_DIFFUSE,
            TEXTURE_SPECULAR,
            TEXTURE_AMBIENT,
            TEXTURE_NORMAL,
            TEXTURE_HEIGHT
        };

        Texture2D(const std::string &filename, const int index = 0, const int type = TEXTURE_DIFFUSE, const bool reverse = false);
        ~Texture2D();

        void use() {
                glActiveTexture(GL_TEXTURE0 + m_index);
                glBindTexture(GL_TEXTURE_2D, m_id);
        }
        bool reloadFile(const std::string &filename, const int index = 0, const bool reverse = false);
        bool isVaild() const { return 0 != m_id; }
        unsigned int getId() const { return m_id; }
        int getIndex() const { return m_index; }
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        int getChannels() const { return m_clrChanls; }
        int getType() const { return m_type; }
        const std::string& getFilename() const { return m_filename; }

    private:
        unsigned int m_id;
        int m_width, m_height, m_clrChanls, m_index, m_type;
        std::string m_filename;
    };
}

#endif // SN_TEXTURE_2D_H
