#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "SOIL.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "assimp.lib")
#pragma comment(lib, "glew32.lib")

#include "Window.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
	Window* window = Window::GetInstance();
	Logger logger("looger.txt", true);

	if (window->Initialize(1200, 800, &logger)) {
		window->Update();
		window->Shutdown();
	}
	else {
		logger << Logger::logType::LOG_ERROR << "Window could not be initialized.";
		return 1;
	}

	return 0;
}