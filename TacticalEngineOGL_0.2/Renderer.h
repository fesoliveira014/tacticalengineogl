#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "glew\glew.h"

#include "Window.h"
#include "Shader.h"
#include "Logger.h"

class Renderer {
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

};


#endif