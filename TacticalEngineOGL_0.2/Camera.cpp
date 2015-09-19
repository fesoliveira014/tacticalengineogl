#include "Camera.h"

Camera::Camera() {}
Camera::~Camera() {}

bool Camera::Initialize(glm::vec3 position, glm::vec3 lookat, float fov, int width, int height, Logger* logger) {
	VirtualCamera::Initialize(position, lookat, fov, width, height, logger);

	m_cameraState = STILL;

	m_translation = glm::vec3(0.0f);
	
	m_yaw = 0.0f;
	m_pitch = 0.0f;

	m_moveState.forward = false;
	m_moveState.back	= false;
	m_moveState.left	= false;
	m_moveState.right	= false;
	m_moveState.up		= false;
	m_moveState.down	= false;

	m_perspective = glm::perspective(fov, float(width) / float(height), 0.1f, 100.0f);
	m_orthographic = glm::ortho(0.0f, 20.0f, 15.0f, 0.0f, -10.0f, 10.0f);

	m_projection = m_perspective;
	m_projectionState = PERSPECTIVE;

	m_target = m_position * m_lookAt;
	m_right = glm::cross(m_up, m_lookAt);

	m_view = glm::lookAt(m_position, m_target, m_up);

	return true;
}

void Camera::Shutdown() {

}

void Camera::Update(float msec) {
	m_msec = msec;
	Move3D();

	glm::mat4 rotationMatrix = GetMatrixUsingYawPitchRoll(m_yaw, m_pitch, 0.0f);
	m_position += m_translation;

	m_translation = glm::vec3(0.0f);

	m_lookAt = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	m_target = m_position + m_lookAt;

	m_up = glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
	m_right = glm::cross(m_up, m_lookAt);

	m_view = glm::lookAt(m_position, m_target, m_up);
}

void Camera::Rotate(const float yaw, const float pitch, const float roll) {
	if (pitch > 0.10f) { m_pitch += .10f; }
	else if (pitch < -0.10f) { m_pitch -= .10f; }
	else { m_pitch += pitch; }

	if (m_pitch > 90.0f) { m_pitch = 90.0f; }
	else if (m_pitch <= -90.0f) { m_pitch = -90.0f; }

	if (yaw > 0.10f) { m_yaw += .10f; }
	else if (yaw < -0.10f) { m_yaw-= .10f; }
	else { m_yaw += yaw; }

	if (m_yaw > 360.0f) { m_yaw -= 360.0f; }
	else if (m_yaw < -360.0f) { m_yaw += 360.0f; }
}

void Camera::Move3D() {
	if (m_moveState.forward) {
		Walk(m_speed * m_msec);
	}

	if (m_moveState.back) {
		Walk(-m_speed * m_msec);
	}

	if (m_moveState.left) {
		Strafe(m_speed * m_msec);
	}

	if (m_moveState.right) {
		Strafe(-m_speed * m_msec);
	}

	if (m_moveState.up) {
		Lift(m_speed * m_msec);
	}

	if (m_moveState.down) {
		Lift(-m_speed * m_msec);
	}
}

void Camera::Move2D(glm::vec2 pos) {
	if (m_cameraState == ROTATE) {
		m_deltaMouse = glm::vec2(m_mousePosition.x - pos.x, pos.y - m_mousePosition.y);
		Rotate(m_mouseSensitivity * m_deltaMouse.x, m_mouseSensitivity * m_deltaMouse.y, 0.0f);
		m_mousePosition = pos;
	}
}

void Camera::SetCameraState(int buttom, int action, double x, double y) {
	if (buttom == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		(*m_logger) << Logger::logType::LOG_INFO << "'Right' mouse buttom pressed.";
		m_cameraState = ROTATE;
	}
	else if (buttom == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		m_cameraState = STILL;
	}

	m_mousePosition = glm::vec2(x, y);
}

void Camera::OnKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) {
			(*m_logger) << Logger::logType::LOG_INFO << "W Key pressed.";
			m_moveState.forward = true;
		}

		if (action == GLFW_RELEASE) {
			m_moveState.forward = false;
		}
	}

	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) {
			(*m_logger) << Logger::logType::LOG_INFO << "S Key pressed.";
			m_moveState.back = true;
		}

		if (action == GLFW_RELEASE) {
			m_moveState.back = false;
		}
	}

	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) {
			(*m_logger) << Logger::logType::LOG_INFO << "A Key pressed.";
			m_moveState.left = true;
		}

		if (action == GLFW_RELEASE) {
			m_moveState.left = false;
		}
	}

	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) {
			(*m_logger) << Logger::logType::LOG_INFO << "D Key pressed.";
			m_moveState.right = true;
		}

		if (action == GLFW_RELEASE) {
			m_moveState.right = false;
		}
	}

	if (key == GLFW_KEY_LEFT_SHIFT) {
		if (action == GLFW_PRESS) {
			(*m_logger) << Logger::logType::LOG_INFO << "'Shift' Key pressed.";
			m_moveState.down = true;
		}

		if (action == GLFW_RELEASE) {
			m_moveState.down = false;
		}
	}

	if (key == GLFW_KEY_SPACE) {
		if (action == GLFW_PRESS) {
			(*m_logger) << Logger::logType::LOG_INFO << "'Space' Key pressed.";
			m_moveState.up = true;
		}

		if (action == GLFW_RELEASE) {
			m_moveState.up = false;
		}
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		(*m_logger) << Logger::logType::LOG_INFO << "F Key pressed.";
		if (m_projectionState == PERSPECTIVE) m_projectionState = ORTHO;
		else m_projectionState = PERSPECTIVE;
	}
}

void Camera::OnMouseMotion(GLFWwindow* window, double xpos, double ypos) {
	Move2D(glm::vec2(xpos, ypos));
}

void Camera::OnMouseButtom(GLFWwindow* window, int buttom, int action, int mods) {
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	SetCameraState(buttom, action, x, y);
}