#include "Frustum.h"

Frustum::Frustum() {
	m_topPlane = glm::vec4(0.0f);
	m_bottomPlane = glm::vec4(0.0f);
	m_leftPlane = glm::vec4(0.0f);
	m_rightPlane = glm::vec4(0.0f);
	m_nearPlane = glm::vec4(0.0f);
	m_farPlane = glm::vec4(0.0f);
}

void Frustum::Update(glm::mat4 projectionViewMatrix) {
	m_leftPlane.x = projectionViewMatrix[4][1] + projectionViewMatrix[1][1];
	m_leftPlane.y = projectionViewMatrix[4][2] + projectionViewMatrix[1][2];
	m_leftPlane.z = projectionViewMatrix[4][3] + projectionViewMatrix[1][3];
	m_leftPlane.w = projectionViewMatrix[4][4] + projectionViewMatrix[1][4];

	m_rightPlane.x = projectionViewMatrix[4][1] - projectionViewMatrix[1][1];
	m_rightPlane.y = projectionViewMatrix[4][2] - projectionViewMatrix[1][2];
	m_rightPlane.z = projectionViewMatrix[4][3] - projectionViewMatrix[1][3];
	m_rightPlane.w = projectionViewMatrix[4][4] - projectionViewMatrix[1][4];

	m_bottomPlane.x = projectionViewMatrix[4][1] + projectionViewMatrix[2][1];
	m_bottomPlane.y = projectionViewMatrix[4][2] + projectionViewMatrix[2][2];
	m_bottomPlane.z = projectionViewMatrix[4][3] + projectionViewMatrix[2][3];
	m_bottomPlane.w = projectionViewMatrix[4][4] + projectionViewMatrix[2][4];

	m_topPlane.x = projectionViewMatrix[4][1] - projectionViewMatrix[2][1];
	m_topPlane.y = projectionViewMatrix[4][2] - projectionViewMatrix[2][2];
	m_topPlane.z = projectionViewMatrix[4][3] - projectionViewMatrix[2][3];
	m_topPlane.w = projectionViewMatrix[4][4] - projectionViewMatrix[2][4];

	m_nearPlane.x = projectionViewMatrix[4][1] + projectionViewMatrix[3][1];
	m_nearPlane.y = projectionViewMatrix[4][2] + projectionViewMatrix[3][2];
	m_nearPlane.z = projectionViewMatrix[4][3] + projectionViewMatrix[3][3];
	m_nearPlane.w = projectionViewMatrix[4][4] + projectionViewMatrix[3][4];

	m_farPlane.x = projectionViewMatrix[4][1] - projectionViewMatrix[3][1];
	m_farPlane.y = projectionViewMatrix[4][2] - projectionViewMatrix[3][2];
	m_farPlane.z = projectionViewMatrix[4][3] - projectionViewMatrix[3][3];
	m_farPlane.w = projectionViewMatrix[4][4] - projectionViewMatrix[3][4];

	m_topPlane = glm::normalize(m_topPlane);
	m_bottomPlane = glm::normalize(m_bottomPlane);
	m_leftPlane = glm::normalize(m_leftPlane);
	m_rightPlane = glm::normalize(m_rightPlane);
	m_nearPlane = glm::normalize(m_nearPlane);
	m_farPlane = glm::normalize(m_farPlane);
}

bool Frustum::IsPointInFrustum(glm::vec3 point) {
	if (glm::dot(glm::vec3(m_topPlane.x, m_topPlane.y, m_topPlane.z), point) + m_topPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_bottomPlane.x, m_bottomPlane.y, m_bottomPlane.z), point) + m_bottomPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_nearPlane.x, m_nearPlane.y, m_nearPlane.z), point) + m_nearPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_farPlane.x, m_farPlane.y, m_farPlane.z), point) + m_farPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_leftPlane.x, m_leftPlane.y, m_leftPlane.z), point) + m_leftPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_rightPlane.x, m_rightPlane.y, m_rightPlane.z), point) + m_rightPlane.w < 0.0f)
		return false;

	return true;
}

bool Frustum::IsBoxInFrustum(glm::vec3 min, glm::vec3 max) {
	if (glm::dot(glm::vec3(m_topPlane.x, m_topPlane.y, m_topPlane.z), min) + m_topPlane.w < 0.0f &&
		glm::dot(glm::vec3(m_topPlane.x, m_topPlane.y, m_topPlane.z), max) + m_topPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_bottomPlane.x, m_bottomPlane.y, m_bottomPlane.z), min) + m_bottomPlane.w < 0.0f &&
		glm::dot(glm::vec3(m_bottomPlane.x, m_bottomPlane.y, m_bottomPlane.z), max) + m_bottomPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_nearPlane.x, m_nearPlane.y, m_nearPlane.z), min) + m_nearPlane.w < 0.0f &&
		glm::dot(glm::vec3(m_nearPlane.x, m_nearPlane.y, m_nearPlane.z), max) + m_nearPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_farPlane.x, m_farPlane.y, m_farPlane.z), min) + m_farPlane.w < 0.0f &&
		glm::dot(glm::vec3(m_farPlane.x, m_farPlane.y, m_farPlane.z), min) + m_farPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_leftPlane.x, m_leftPlane.y, m_leftPlane.z), min) + m_leftPlane.w < 0.0f &&
		glm::dot(glm::vec3(m_leftPlane.x, m_leftPlane.y, m_leftPlane.z), min) + m_leftPlane.w < 0.0f)
		return false;
	if (glm::dot(glm::vec3(m_rightPlane.x, m_rightPlane.y, m_rightPlane.z), min) + m_rightPlane.w < 0.0f &&
		glm::dot(glm::vec3(m_rightPlane.x, m_rightPlane.y, m_rightPlane.z), min) + m_rightPlane.w < 0.0f)
		return false;

	return true;
}