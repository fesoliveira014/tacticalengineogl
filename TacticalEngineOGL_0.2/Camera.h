#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "VirtualCamera.h"

enum ProjectionState {PERSPECTIVE, ORTHO};

class Camera : public VirtualCamera {
public:
	Camera();
	~Camera();

	bool Initialize(glm::vec3 position, glm::vec3 lookat, float fov, int width, int height, Logger* logger);
	void Shutdown();

	void Update(float msec = 1.0f);
	void Rotate(const float yaw, const float pitch, const float roll);

	glm::mat4 GetViewProjection() { return m_projection * m_view; }

	void OnMouseMotion(GLFWwindow* window, double xpos, double ypos);
	void OnMouseButtom(GLFWwindow* window, int buttom, int action, int mods);
	void OnKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

protected:
	void Move3D();
	void Move2D(glm::vec2 pos);
	void SetCameraState(int buttom, int action, double x, double y);

	void Walk(const float distance) { m_translation += m_lookAt * distance; }
	void Strafe(const float distance) { m_translation += m_right * distance; }
	void Lift(const float distance) { m_translation += m_up * distance; }

	float m_yaw, m_pitch;
	float m_msec;

	glm::mat4 m_projection;

	glm::vec3 m_translation; // delta pos
	glm::vec3 m_target;

	glm::vec2 m_mousePosition;
	glm::vec2 m_deltaMouse;

	glm::mat4 m_perspective;
	glm::mat4 m_orthographic;

	CameraState		m_cameraState;
	MoveState		m_moveState;
	ProjectionState m_projectionState;
};

#endif
