#ifndef SN_VERTEX_H
#define SN_VERTEX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SurgeNight
{

struct Vertex
{
    glm::vec3 pos, nor;
    glm::vec2 texCor;
    glm::vec3 tangent, bitangent;
    Vertex(const glm::vec3 &posv = glm::vec3(0.0f),
           const glm::vec3 &norv = glm::vec3(0.0f),
           const glm::vec2 &texCorv = glm::vec2(0.0f),
           const glm::vec3 &tangentv = glm::vec3(0.0f),
           const glm::vec3 &bitangentv = glm::vec3(0.0f)
           ) :
           pos(posv),
           nor(norv),
           texCor(texCorv),
           tangent(tangentv),
           bitangent(bitangentv)
    {}
    ~Vertex() {}
};

}

#endif // SN_VERTEX_H
