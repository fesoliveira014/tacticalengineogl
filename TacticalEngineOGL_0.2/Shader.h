#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <iostream>
#include <map>

#include "glew\glew.h"
#include "Logger.h"
#include "Utils.h"

class Shader {
public:


	Shader();
	~Shader();

	bool Initialize(Logger* logger);
	void Shutdown();

	bool LoadShaderFromFile(GLenum shaderType, const char* fileName);
	bool CreateAndLinkProgram();

	void Use() { glUseProgram(m_shaderProgram); }
	void UnUse() { glUseProgram(0); }

	bool AddAttribute(string attribute);
	bool AddUniform(string uniform);

	GLuint GetAttribute(string attribute);
	GLuint GetUniform(string uniform);

	GLuint GetProgram() { return m_shaderProgram; }

protected:
	bool Compile(const char* shaderSource, GLenum shaderType);
	void DeleteShaderProgram() { glDeleteProgram(m_shaderProgram); }

	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_geometryShader;

	GLuint m_shaderProgram;

	std::map<string, GLuint> m_attributeList;
	std::map<string, GLuint> m_uniformList;

	Logger* m_logger;
};


#endif
