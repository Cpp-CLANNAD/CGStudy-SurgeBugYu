#ifndef SN_CAMERA_H
#define SN_CAMERA_H

#include "SNCGraphics/Common/CommonType.h"
#include "SNCGraphics/ShaderProgram.h"

namespace SurgeNight
{

class Camera
{
public:
    explicit Camera(const Vec3 &pos);
    ~Camera();

    void move(const float right, const float up = 0.0f, const float front = 0.0f);
    void translate(const float right, const float up = 0.0f, const float front = 0.0f);
    void addPos(const Vec3 &posDelta);
    void setPos(const Vec3 &pos);
    void lookAt(const Vec3 &tar);
    void lookTo(const Vec3 &tar);
    void update(const float dt);

    void useIn(ShaderProgram &shader, const std::string &name = "view") {
        glUniformMatrix4fv(shader.getUniform(name), 1, GL_FALSE, ValuePtr(m_view));
    };

    const Vec3 getPos() const { return m_pos; }
    const Vec3 getTarget() const { return m_tar; }
    const Mat4 getViewMatrix() const { return m_view; }
    bool isLookAting() const { return m_lookAt; }

private:
    void updateView();
    Mat4 m_view;
    Vec3 m_pos, m_up, m_tar;
    bool m_lookAt;
};

}

#endif // SN_CAMERA_H
