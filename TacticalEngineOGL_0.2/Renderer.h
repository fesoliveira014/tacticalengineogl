#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include "Shader.h"
#include "Logger.h"
#include "Mesh.h"
#include "Camera.h"

class Window;

class Renderer {
public:
	static Renderer* GetInstance() {
		if (m_instance == NULL)
			m_instance = new Renderer();
		return m_instance;
	}

	~Renderer() {};

	bool Initialize(glm::vec2 screenDimensions, Logger *logger);
	void Shutdown();

	void MouseMotionCallback(GLFWwindow* window, double xpos, double ypos) {
		m_camera->OnMouseMotion(window, xpos, ypos);
	}

	void MouseButtonCallback(GLFWwindow* window, int buttom, int action, int mods) {
		m_camera->OnMouseButtom(window, buttom, action, mods);
	}

	void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		m_camera->OnKeyboard(window, key, scancode, action, mods);
	}

	void UpdateScene();
	void RenderScene();

protected:
	Renderer();

	static Renderer* m_instance;

	Camera* m_camera;
	Mesh* m_triangle;
	Shader* m_currentShader;
	Logger* m_logger;
};


#endif