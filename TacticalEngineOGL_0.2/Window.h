#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>

#include "glew\glew.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

#include "Renderer.h"
#include "Logger.h"
#include "Timer.h"

class Window{
public:

	static Window* GetInstance() {
		if (m_instance == NULL)
			m_instance = new Window();
		return m_instance;
	}

	~Window();

	bool Initialize(float width, float height, const std::string name = "Game Window", bool fullscreen = false);
	void Shutdown();

	void Update();

	void SetRenderer(Renderer* renderer);

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
	Timer* m_timer;
};

#endif