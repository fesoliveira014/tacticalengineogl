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
	Renderer* renderer = Renderer::GetInstance();
	Logger logger("looger.txt", true);
	

	if (window->Initialize(1200.0, 800.0, &logger)) {
		if (renderer == NULL || !renderer->Initialize(window->GetScreenSize(), &logger)) {
			logger << Logger::logType::LOG_ERROR << "Renderer could not be initialized.";
			return 2;
		}
		window->SetRenderer(renderer);
		window->Update();
		window->Shutdown();
	}
	else {
		logger << Logger::logType::LOG_ERROR << "Window could not be initialized.";
		return 1;
	}

	return 0;
}