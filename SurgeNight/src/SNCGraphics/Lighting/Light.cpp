#include "Light.h"

namespace SurgeNight
{

Light::Light(const glm::vec3 &pos, const glm::vec4 &dir, const glm::vec3 &color) :
    m_pos(pos), m_color(color), m_dir(dir),
    m_ambient(0.2f), m_diffuse(0.5f), m_specular(1.0f)
{

}

Light::~Light()
{

}

void Light::useIn(ShaderProgram &shader, const std::string &name)
{
    shader.setValue(name + ".ambient", m_color * m_ambient);
    shader.setValue(name + ".diffuse", m_color * m_diffuse);
    shader.setValue(name + ".spacular", m_color * m_specular);
    shader.setValue("light.constant", m_constant);
    shader.setValue("light.linear", m_linear);
    shader.setValue("light.quadratic", m_quadratic);
}

}
