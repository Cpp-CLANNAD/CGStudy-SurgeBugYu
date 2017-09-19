#include "ShaderProgram.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace SurgeNight
{

ShaderProgram::ShaderProgram(const std::string &vertexShaderFilename, const std::string &fragmentShaderFilename) : m_id(0)
{
    std::ifstream vsin(vertexShaderFilename, std::fstream::in), fsin(fragmentShaderFilename, std::fstream::in);

    int success;
    char infoLog[512];
    std::string vsbuf, fsbuf;
    std::string vsSrc, fsSrc;
    while (std::getline(vsin, vsbuf)) {
        vsSrc += vsbuf;
        vsSrc += '\n';
    }
    while (std::getline(fsin, fsbuf)) {
        fsSrc += fsbuf;
        fsSrc += '\n';
    }
    const char *vertexShaderSource = vsSrc.data(), *fragmentShaderSource = fsSrc.data();
    vsin.close();
    fsin.close();

    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (0 == success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Error: Vertex vertex compilation failed\n" << infoLog << std::endl;
        return;
    }

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (0 == success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Error: Fragment vertex compilation failed\n" << infoLog << std::endl;
        return;
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (0 == success) {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cerr << "Error: Shader program link failed\n" << infoLog << std::endl;
        m_id = 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::ShaderProgram(const std::string &path) : ShaderProgram(path + "/vertex.vs", path + "/fragment.fs")
{

}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}

void ShaderProgram::setValue(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setValue(const std::string &name, unsigned int value)
{
    glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setValue(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), static_cast<int>(value));
}

void ShaderProgram::setValue(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setValue(const std::string &name, const glm::vec2 &value)
{
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setValue(const std::string &name, const glm::vec3 &value)
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setValue(const std::string &name, const glm::vec4 &value)
{
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setValue(const std::string &name, const glm::mat2 &value)
{
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setValue(const std::string &name, const glm::mat3 &value)
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setValue(const std::string &name, const glm::mat4 &value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

}
