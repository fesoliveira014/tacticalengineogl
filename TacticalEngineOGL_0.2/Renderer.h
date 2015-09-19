#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include "glm\gtc\type_ptr.hpp"

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
	}

	void UpdateScene(float msec = 1.0f);
	void RenderScene();

protected:
	Renderer();
	void UpdateShaderMatrices(Shader* shader);
	Camera* GetCamera() { return m_camera; }

	static Renderer* m_instance;

	glm::mat4 m_viewProjectionMatrix;
	glm::mat4 m_modelMatrix;
	glm::mat4 m_textureMatrix;

	Camera* m_camera;
	Mesh* m_triangle;
	Shader* m_currentShader;
};


#endif