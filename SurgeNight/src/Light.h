#ifndef SN_LIGHT_H
#define SN_LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "ShaderProgram.h"

namespace SurgeNight
{

class Light
{
public:
    enum {
        LIGHT_DIRECTIONAL,
        LIGHT_POINT,
        LIGHT_SPOTLIGHT
    };

    Light(const glm::vec3 &pos = glm::vec3(0.0f), const glm::vec4 &dir = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f), const glm::vec3 &color = glm::vec3(1.0f), const std::string &shaderPath = "shader/light");
    ~Light();

    void setColor(const glm::vec3 &color) { m_color = color; }
    void setPosition(const glm::vec3 &pos) { m_pos = pos; m_dir = glm::vec4(pos, 1.0f); updateModelMatrix(); }
    void setDirection(const glm::vec3 &dir) { m_dir = glm::vec4(dir, 0.0f); }
    void setViewMatrix(const glm::mat4 &view) { m_view = view; }
    void setProjectionMatrix(const glm::mat4 &projection) { m_projection = projection; }
    // void setType();

    const glm::vec3 getColor() const { return m_color; }
    const glm::vec4 getPosition() const { return glm::vec4(m_pos, 1.0f); }
    const glm::vec4 getDirection() const { return m_dir; }
    const glm::mat4 getModelMatrix() const { return m_model; }
    const glm::mat4 getViewMatrix() const { return m_view; }
    const glm::mat4 getProjectionMatrix() const { return m_projection; }
    bool isType(const int type) const {
        if (LIGHT_DIRECTIONAL == type) return m_dir.w == 0.0f;
        if (LIGHT_POINT == type) return m_dir.w == 1.0f;
        if (LIGHT_SPOTLIGHT == type) return m_dir.w == 0.0f;
        return false;
    }

    void paint();

private:
    void updateModelMatrix();

    glm::vec3 m_pos, m_color;
    glm::vec4 m_dir;
    ShaderProgram m_shader;
    unsigned int m_VAO, m_VBO, m_EBO;
    glm::mat4 m_model, m_view, m_projection;
};

}

#endif // SN_LIGHT_H
