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

void Camera::move(const float right, const float up, const float front)
{
    glm::vec3 frontv, rightv, upv(m_up);
    if (m_lookAt) {
        frontv = glm::normalize(m_tar - m_pos);
        rightv = glm::normalize(glm::cross(frontv, upv)) * right;
        upv *= up;
        frontv *= front;
    }
    else {
        frontv = m_tar;
        rightv = glm::normalize(glm::cross(frontv, upv)) * right;
        upv *= up;
        frontv *= front;
    }
    m_pos += frontv;
    m_pos += rightv;
    m_pos += upv;
    updateView();
}

void Camera::translate(const float right, const float up, const float front)
{
    m_pos += glm::vec3(right, up, front);
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
