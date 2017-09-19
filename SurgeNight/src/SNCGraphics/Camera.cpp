#include "Camera.h"

namespace SurgeNight
{

Camera::Camera(const glm::vec3 &pos) : m_pos(pos), m_up(0.0f, 1.0f, 0.0f), m_tar(0.0f, 0.0f, -1.0f), m_lookAt(false)
{
    updateView();
}

Camera::~Camera()
{

}

void Camera::move(const float x, const float y, const float z)
{
    glm::vec3 front, right, up(m_up);
    if (m_lookAt) {
        front = glm::normalize(m_tar - m_pos);
        right = glm::normalize(glm::cross(front, up)) * x;
        up *= y;
        front *= z;
    }
    else {
        front = m_tar;
        right = glm::normalize(glm::cross(front, up)) * x;
        up *= y;
        front *= z;
    }
    m_pos += front;
    m_pos += right;
    m_pos += up;
    updateView();
}

void Camera::addPos(const glm::vec3 &posDelta)
{
    m_pos += posDelta;
    updateView();
}

void Camera::setPos(const glm::vec3 &pos)
{
    m_pos = pos;
    updateView();
}

void Camera::lookAt(const glm::vec3 &tar)
{
    m_lookAt = true;
    m_tar = tar;
    updateView();
}

void Camera::lookTo(const glm::vec3 &tar)
{
    m_lookAt = false;
    m_tar = glm::normalize(tar);
    updateView();
}

void Camera::update(const float dt)
{
    updateView();
}

void Camera::updateView()
{
    if (m_lookAt)
        m_view = glm::lookAt(m_pos, m_tar, m_up);
    else
        m_view = glm::lookAt(m_pos, m_pos + m_tar, m_up);
}

}
