#ifndef SN_CAMERA_H
#define SN_CAMERA_H

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"

namespace SurgeNight
{

class Camera
{
public:
    Camera(const glm::vec3 &pos);
    ~Camera();

    void move(const float x, const float y = 0.0f, const float z = 0.0f);
    void addPos(const glm::vec3 &posDelta);
    void setPos(const glm::vec3 &pos);
    void lookAt(const glm::vec3 &tar);
    void lookTo(const glm::vec3 &tar);
    void update(const float dt);

    void useIn(ShaderProgram &shader, const std::string &name = "view") {
        glUniformMatrix4fv(shader.getUniform(name), 1, GL_FALSE, glm::value_ptr(m_view));
    };

    const glm::vec3 getPos() const { return m_pos; }
    const glm::vec3 getTarget() const { return m_tar; }
    const glm::mat4 getViewMatrix() const { return m_view; }
    bool isLookAting() const { return m_lookAt; }

private:
    void updateView();
    glm::mat4 m_view;
    glm::vec3 m_pos, m_up, m_tar;
    bool m_lookAt;
};

}

#endif // SN_CAMERA_H
