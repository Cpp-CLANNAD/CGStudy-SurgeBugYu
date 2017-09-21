#include "Light.h"

namespace SurgeNight
{

Light::Light(const glm::vec3 &pos, const glm::vec4 &dir, const glm::vec3 &color) :
    m_pos(pos), m_color(color), m_dir(dir)
{

}

Light::~Light()
{

}

void Light::useIn(ShaderProgram &shader, const std::string &name)
{
    shader.setValue(name + ".ambient", m_color * 0.2f);
    shader.setValue(name + ".diffuse", m_color * 0.5f);
    shader.setValue(name + ".spacular", m_color * 1.0f);
    shader.setValue("light.constant", m_constant);
    shader.setValue("light.linear", m_linear);
    shader.setValue("light.quadratic", m_quadratic);
}

}
