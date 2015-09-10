#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "glew\glew.h"

#include "Shader.h"
#include "Logger.h"
#include "Mesh.h"

class Window;

class Renderer {
public:
	static Renderer* GetInstance() {
		static Renderer* renderer = new Renderer();
		return renderer;
	}

	~Renderer() {};

	bool Initialize(Window &parent, Logger *logger);
	void Shutdown();

	//void UpdateScene();
	void RenderScene();

protected:
	Renderer();
	Mesh* m_triangle;
	Shader* m_currentShader;
	Logger* m_logger;
};


#endif