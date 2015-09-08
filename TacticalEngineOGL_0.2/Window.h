#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>

#include "glew\glew.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

#include "Logger.h"

class Window{
public:

	static Window* GetInstance() {
		static Window* instance = new Window();
		return instance;
	}

	~Window();

	bool Initialize(int width, int height, Logger* logger, const std::string name = "Game Window", bool fullscreen = false);
	void Shutdown();

	void Update();

	void SetRenderer();

	glm::vec2 GetScreenSize() { return glm::vec2(m_width, m_height); }
	void ShowFps();

protected:
	Window();

	GLFWwindow* m_window;

	int m_width;
	int m_height;

	std::string m_windowName;
	bool m_fullscreen = false;

	int m_numFrames;
	double m_lastTime;

	Logger* m_logger;
};

#endif