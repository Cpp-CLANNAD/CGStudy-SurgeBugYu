#ifndef SN_SHADER_PROGRAM_H
#define SN_SHADER_PROGRAM_H

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <string>

namespace SurgeNight
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename);
        explicit ShaderProgram(const std::string &path);
        ~ShaderProgram();

        void use() { glUseProgram(m_id); }
        void setValue(const std::string &name, int value);
        void setValue(const std::string &name, unsigned int value);
        void setValue(const std::string &name, bool value);
        void setValue(const std::string &name, float value);
        void setValue(const std::string &name, const glm::vec2 &value);
        void setValue(const std::string &name, const glm::vec3 &value);
        void setValue(const std::string &name, const glm::vec4 &value);
        void setValue(const std::string &name, const glm::mat2 &value);
        void setValue(const std::string &name, const glm::mat3 &value);
        void setValue(const std::string &name, const glm::mat4 &value);
        bool isVaild() const { return 0 != m_id; }
        unsigned int getId() const { return m_id; }
        int getUniform(const std::string &name) { return glGetUniformLocation(m_id, name.c_str()); }

    private:
        unsigned int m_id;
    };
}

#endif // SN_SHADER_PROGRAM_H
