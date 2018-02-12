#ifndef SN_LIGHT_H
#define SN_LIGHT_H

/*

// relative GLSL struct Light

struct LightSpot {
    vec3 position, direction;
    float cutOff, outerCutOff;

    vec3 ambient, diffuse, specular;
    float constant, linear, quadratic;
};

struct LightNormal {
    vec4 position;
    float cutOff, outerCutOff;

    vec3 ambient, diffuse, specular;
    float constant, linear, quadratic;
};

// relative GLSL light calc funtions

vec3 calcNormalLight(LightNormal tlight, CustomMaterial tmat, vec3 normalDir, vec3 vw2ptDir, vec3 lt2ptDir, vec3 lightDir)
{
    vec3 tnnor = normalize(normalDir), tvnor = normalize(-vw2ptDir), tlpnor = normalize(-lt2ptDir), tlnor = normalize(lightDir);
    float dis = length(lt2ptDir);

    vec3 ambient = tlight.ambient * tmat.ambient;

    float diff = max(dot(tnnor, tlnor), 0.0f);
    vec3 diffuse = tlight.diffuse * diff * tmat.diffuse;

    float spec = pow(max(dot(tvnor, reflect(-tlnor, tnnor)), 0.0f), tmat.shininess);
    vec3 specular = tlight.specular * spec * tmat.specular;

    float attenuation = 1.0f;
    attenuation = 1.0 / (tlight.constant + tlight.linear * dis + tlight.quadratic * (dis * dis));

    return (ambient + diffuse + specular) * attenuation;
}

vec3 calcSpotLight(LightSpot tlight, CustomMaterial tmat, vec3 normalDir, vec3 vw2ptDir, vec3 lt2ptDir, vec3 lightDir)
{
    vec3 tnnor = normalize(normalDir), tvnor = normalize(-vw2ptDir), tlpnor = normalize(-lt2ptDir), tlnor = normalize(lightDir);
    float dis = length(lt2ptDir);

    vec3 ambient = tlight.ambient * tmat.ambient;

    float diff = max(dot(tnnor, tlnor), 0.0f);
    vec3 diffuse = tlight.diffuse * diff * tmat.diffuse;

    float spec = pow(max(dot(tvnor, reflect(-tlnor, tnnor)), 0.0f), tmat.shininess);
    vec3 specular = tlight.specular * spec * tmat.specular;

    float attenuation = 1.0f;
    attenuation = 1.0 / (tlight.constant + tlight.linear * dis + tlight.quadratic * (dis * dis));

    float theta = dot(tlpnor, -tlnor);
    float epsilon = tlight.cutOff - tlight.outerCutOff;
    float intensity = clamp((theta - tlight.outerCutOff) / epsilon, 0.0f, 1.0f);

    return (ambient + diffuse + specular) * attenuation * intensity;
}

*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "SNCGraphics/ShaderProgram.h"

namespace SurgeNight
{

class Light
{
public:
    enum LightType {
        LIGHT_DIRECTIONAL,
        LIGHT_POINT,
        LIGHT_SPOTLIGHT
    };

    explicit Light(const glm::vec3 &pos = glm::vec3(0.0f), const glm::vec4 &dir = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f), const glm::vec3 &color = glm::vec3(1.0f));
    ~Light();

    void setColor(const glm::vec3 &color) { m_color = color; }
    void setPosition(const glm::vec3 &pos) { m_pos = pos; m_dir = glm::vec4(pos, 1.0f); }
    void setDirection(const glm::vec3 &dir) { m_dir = glm::vec4(dir, 0.0f); }
    void setAttenuation(const float constant, const float linear, const float quadratic) { m_constant = constant; m_linear = linear; m_quadratic = quadratic; }
    void setEnvironment(const float ambient, const float diffuse = 0.5f, const float specular = 1.0f) { m_ambient = ambient; m_diffuse = diffuse; m_specular = specular; }
    // void setType();

    const glm::vec3 getColor() const { return m_color; }
    const glm::vec4 getPosition() const { return glm::vec4(m_pos, 1.0f); }
    const glm::vec4 getDirection() const { return m_dir; }
    bool isType(const int type) const {
        if (LIGHT_DIRECTIONAL == type) return m_dir.w == 0.0f;
        if (LIGHT_POINT == type) return m_dir.w == 1.0f;
        if (LIGHT_SPOTLIGHT == type) return m_dir.w == 0.0f;
        return false;
    }

    void useIn(ShaderProgram &shader, const std::string &name = "light");

private:
    void updateModelMatrix();

    glm::vec3 m_pos, m_color;
    glm::vec4 m_dir;
    float m_constant, m_linear, m_quadratic;
    float m_ambient, m_diffuse, m_specular;
};

}

#endif // SN_LIGHT_H
