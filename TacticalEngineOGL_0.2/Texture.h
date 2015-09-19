#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include <vector>

#include "Image.h"
#include "Logger.h"

class Texture {
public:
	Texture();
	~Texture();

	bool Initialize(GLenum target, char* path);
	bool Initialize(GLenum target, std::vector<char*> textureFaces);

	void Shutdown();

	static void Bind(Texture* texture) {
		glBindTexture(texture->m_textureTarget, texture->m_textureID);
	}

	static void Unbind(Texture* texture) {
		glBindTexture(texture->m_textureTarget, 0);
	}
	
	GLuint GetTextureID() { return m_textureID; }
	GLenum GetTextureTarget() { return m_textureTarget; }
	std::string GetTextureName() { return m_textureName; }

protected:
	bool LoadTexture(GLenum target, char* path);
	bool LoadTexture(GLenum target, std::vector<char*> textureFaces);
	bool LoadTexture1D(char* path);
	bool LoadTexture2D(char* path);
	bool LoadTexture3D(char* path);
	bool LoadTextureRectangle(char* path);
	bool LoadTextureCubemap(std::vector<char*> textureFaces);
	bool LoadTexture1DArray(char* path);
	bool LoadTexture2DArray(char* path);
	bool LoadTextureCubemapArray(char* path);
	bool LoadTexture2DMultisample(char* path);
	bool LoadTexture2DMultisampleArray(char* path);

	GLuint m_textureID;
	GLenum m_textureTarget;
	std::string m_textureName;
};

#endif