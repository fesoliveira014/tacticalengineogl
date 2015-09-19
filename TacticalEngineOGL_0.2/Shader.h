#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <iostream>
#include <map>

#include "glew\glew.h"
#include "Logger.h"
#include "Utils.h"
#include "Mesh.h"

class Shader {
public:


	Shader();
	~Shader();

	bool Initialize();
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

	void Shader::SetDefaultAttributes() {
		glBindAttribLocation(m_shaderProgram, VERTEX_BUFFER, "position");
		glBindAttribLocation(m_shaderProgram, COLOUR_BUFFER, "colour");
		glBindAttribLocation(m_shaderProgram, TEXTURE_BUFFER, "texCoords");

	}

protected:
	bool Compile(const char* shaderSource, GLenum shaderType);
	void DeleteShaderProgram() { glDeleteProgram(m_shaderProgram); }

	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_geometryShader;

	GLuint m_shaderProgram;

	std::map<string, GLuint> m_attributeList;
	std::map<string, GLuint> m_uniformList;
};


#endif
