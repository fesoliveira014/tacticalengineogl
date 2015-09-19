#ifndef _VIRTUAL_CAMERA_H_
#define _VIRTUAL_CALERA_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\euler_angles.hpp"

#include "Logger.h"

enum MovementDirection {
	FORWARD, BACK, LEFT, RIGHT, UP, DOWN
};

enum CameraState {
	STILL, ROTATE, PAN
};

struct MoveState {
	bool forward, back, right, left, up, down;
};

class VirtualCamera {
public:
	VirtualCamera() {};
	~VirtualCamera() {};

	bool virtual Initialize(glm::vec3 position, glm::vec3 lookat, float fov, int width, int height, Logger* logger);
	void virtual Shutdown() = 0;

	virtual void Update(float msec) = 0;
	virtual void Rotate(const float yaw, const float pitch, const float roll) = 0;

	const glm::mat4 GetView() { return m_view; }

	void SetPosition(const glm::vec3 position) { m_position = position; }
	const glm::vec3 GetPosition() const { return m_position; }

	const glm::vec3 GetLookAt() const { return m_lookAt; }
	const glm::vec3 GetUp() const { return m_up; }
	const glm::vec3 GetRight() const { return m_right; }

	glm::mat4 GetMatrixUsingYawPitchRoll(const float yaw, const float pitch, const float roll) {
		return glm::yawPitchRoll(yaw, pitch, roll);
	}

	const float GetFOV() const { return m_fov; }
	const float GetAspect() const { return m_aspect; }

protected:
	float m_fov, m_aspect;
	int m_width, m_height;
	glm::vec3 m_position, m_lookAt, m_up, m_right;
	glm::mat4 m_view;

	static glm::vec3 staticUp;

	float m_speed;
	float m_mouseSensitivity;

	Logger* m_logger;
};

#endif

