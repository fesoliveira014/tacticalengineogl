#ifndef _FRUSTRUM_H_
#define _FRUSTRUM_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"

class Frustum {
public:
	Frustum();
	~Frustum();

	void Update(glm::mat4 projectionViewMatrix);

	bool IsPointInFrustum(glm::vec3 point);
	bool IsBoxInFrustum(glm::vec3 min, glm::vec3 max);

protected:
	glm::vec4 m_topPlane;
	glm::vec4 m_bottomPlane;
	glm::vec4 m_farPlane;
	glm::vec4 m_nearPlane;
	glm::vec4 m_leftPlane;
	glm::vec4 m_rightPlane;
};

#endif