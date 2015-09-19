#include "Window.h"

Window* Window::m_instance = NULL;

Window::Window() {}
Window::~Window() {}

bool Window::Initialize(float width, float height, const std::string name, bool fullscreen) {
	m_width		 = width;
	m_height	 = height;
	m_windowName = name;
	m_fullscreen = fullscreen;

	if (!glfwInit()) {
		(*Logger::GetInstance()) << Logger::logType::LOG_ERROR << "GLFW could not be started.";
		return false;
	}

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), NULL, NULL);
	if (!m_window) {
		(*Logger::GetInstance()) << Logger::logType::LOG_ERROR << "GLFW window could not be created.";
		return false;
	}

	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		(*Logger::GetInstance()) << Logger::logType::LOG_ERROR << "GLEW could not be initialized.";
		return false;
	}

	// Gets GPU and renderer information.
	std::string glVersion = reinterpret_cast< char const * >(glGetString(GL_VERSION));
	std::string glShaderVersion = reinterpret_cast< char const * >(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string glVendor = reinterpret_cast< char const * >(glGetString(GL_VENDOR));
	std::string glRenderer = reinterpret_cast< char const * >(glGetString(GL_RENDERER));

	(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "OpenGL version: " + glVersion;
	(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "GLSL version: " + glShaderVersion;
	(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "Vendor: " + glVendor;
	(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "Renderer: " + glRenderer;

	m_timer = new Timer();
	m_numFrames = 0;
	m_lastTime = m_timer->GetMS();

	(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "Window successfully initialized.";

	return true;
}

void Window::Shutdown() {
	(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "Shutting window down...";
	glfwTerminate();
}

void Window::SetRenderer(Renderer* renderer) {
	m_renderer = renderer;

	glfwSetKeyCallback(m_window, &Renderer::KeyboardCallback);
	glfwSetMouseButtonCallback(m_window, &Renderer::MouseButtonCallback);
	glfwSetCursorPosCallback(m_window, &Renderer::MouseMotionCallback);
}

void Window::Update() {
	while (!glfwWindowShouldClose(m_window)) {
		ShowFps();
		m_renderer->UpdateScene();
		m_renderer->RenderScene();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void Window::ShowFps() {
	double currentTime = m_timer->GetMS();
	double delta = currentTime - m_lastTime;
	++m_numFrames;

	if (delta >= 1.0) {
		double fps = double(m_numFrames) / delta;
		
		glfwSetWindowTitle(m_window, (m_windowName + " - FPS: " +  std::to_string(fps)).c_str());

		m_numFrames = 0;
		m_lastTime = currentTime;
	}
}