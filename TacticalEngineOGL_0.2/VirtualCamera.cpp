#include "VirtualCamera.h"

glm::vec3 VirtualCamera::staticUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool VirtualCamera::Initialize(glm::vec3 position, glm::vec3 lookat, float fov, int width, int height, Logger* logger) {
	m_fov = fov;
	m_width = width;
	m_height = height;

	m_position = position;
	m_lookAt = lookat;

	m_speed = 0.05f;
	m_mouseSensitivity = 0.01f;

	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_aspect = float(m_width) / float(m_height);

	m_logger = logger;

	return true;
}