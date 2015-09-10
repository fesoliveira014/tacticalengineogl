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
		if (m_instance == NULL)
			static Renderer* renderer = new Renderer();
		return m_instance;
	}

	~Renderer() {};

	bool Initialize(Window &parent, Logger *logger);
	void Shutdown();

	//void UpdateScene();
	void RenderScene();

protected:
	Renderer();

	static Renderer* m_instance;

	Mesh* m_triangle;
	Shader* m_currentShader;
	Logger* m_logger;
};


#endif