#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>

#include "glew\glew.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

#include "Renderer.h"
#include "Logger.h"

class Window{
public:

	static Window* GetInstance() {
		if (m_instance == NULL)
			m_instance = new Window();
		return m_instance;
	}

	~Window();

	bool Initialize(int width, int height, Logger* logger, const std::string name = "Game Window", bool fullscreen = false);
	void Shutdown();

	void Update();

	void SetRenderer(Renderer* renderer) { m_renderer = renderer; }

	static int GetKeyState(Window &window, int key) {
		return glfwGetKey(window.m_window, key);
	}

	static int GetMouseButtomState(Window &window, int buttom) { 
		return glfwGetMouseButton(window.m_window, buttom);
	}

	static glm::vec2 GetCursorPos(Window &window) {
		double xpos, ypos;
		glfwGetCursorPos(window.m_window, &xpos, &ypos);
		return glm::vec2(xpos, ypos);
	}
	
	static void SetCursorPos(Window &window, double xpos, double ypos) {
		glfwSetCursorPos(window.m_window, xpos, ypos);
	}


	glm::vec2 GetScreenSize() { return glm::vec2(m_width, m_height); }
	void ShowFps();

protected:
	Window();

	static Window* m_instance;

	GLFWwindow* m_window;

	int m_width;
	int m_height;

	std::string m_windowName;
	bool m_fullscreen = false;

	int m_numFrames;
	double m_lastTime;

	Renderer* m_renderer;
	Logger* m_logger;
};

#endif