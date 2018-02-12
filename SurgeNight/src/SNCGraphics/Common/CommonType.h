#ifndef SN_COMMON_TYPE_H
#define SN_COMMON_TYPE_H

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SurgeNight
{

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat2 Mat2;
typedef glm::mat3 Mat3;
typedef glm::mat4 Mat4;

template<typename T> inline
	const GLfloat* ValuePtr(const T &t) {
		return glm::value_ptr(t);
	}

}

#endif //SN_COMMON_TYPE_H
