#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include "glm\gtc\type_ptr.hpp"

#include "Shader.h"
#include "Logger.h"
#include "Mesh.h"
#include "Camera.h"
#include "Cube.h"

class Window;

class Renderer {
public:
	static Renderer* GetInstance() {
		if (m_instance == NULL)
			m_instance = new Renderer();
		return m_instance;
	}

	~Renderer() {};

	bool Initialize(glm::vec2 screenDimensions);
	void Shutdown();

	static void MouseMotionCallback(GLFWwindow* window, double xpos, double ypos) {
		GetInstance()->GetCamera()->OnMouseMotion(window, xpos, ypos);
	}

	static void MouseButtonCallback(GLFWwindow* window, int buttom, int action, int mods) {
		GetInstance()->GetCamera()->OnMouseButtom(window, buttom, action, mods);
	}

	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		GetInstance()->GetCamera()->OnKeyboard(window, key, scancode, action, mods);
		if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
			(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "'1' Key pressed.";
			GetInstance()->ToggleWireframe();
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
			(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "'2' Key pressed.";
			GetInstance()->ToggleAlpha();
		}
		if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
			(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "'3' Key pressed.";
			GetInstance()->ToggleBlendMode();
		}
	}

	void UpdateScene(float msec = 1.0f);
	void RenderScene();

	void ToggleAlpha() {
		m_usingAlpha = !m_usingAlpha;
		if (m_usingAlpha) glEnable(GL_BLEND);
		else glDisable(GL_BLEND);
	}

	void ToggleWireframe() {
		m_wireframe = !m_wireframe;
		if (m_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void ToggleBlendMode() {
		m_blendMode = (m_blendMode + 1) % 4;

		switch (m_blendMode) {
		case 0:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case 1:
			glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
			break;
		case 2:
				glBlendFunc(GL_ONE, GL_ZERO);
			break;
		case 3:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		}
	}

protected:
	Renderer();
	void UpdateShaderMatrices(Shader* shader);
	Camera* GetCamera() { return m_camera; }

	static Renderer* m_instance;

	glm::mat4 m_viewProjectionMatrix;
	glm::mat4 m_modelMatrix;
	glm::mat4 m_textureMatrix;

	glm::vec3 m_positions[2];

	Camera* m_camera;
	Shader* m_currentShader;
	Cube* m_cube;

	int m_blendMode;
	bool m_usingAlpha;
	bool m_usingDepth;
	bool m_modifyObject;
	bool m_wireframe;
};


#endif