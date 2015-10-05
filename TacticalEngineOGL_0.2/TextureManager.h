#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <map>
#include <string>

#include "Texture.h"

class TextureManager {
public: 
	TextureManager* GetInstance() {
		if (instance == NULL) {
			instance = new TextureManager();
		}

		return instance;
	}
	
	~TextureManager() {
		m_textures.clear();
		delete instance;
	}

	static void BindTexture(GLuint textureID) {
		Texture::Bind(instance->m_textures[textureID]);
	}

	static void UnbindTexture(GLuint textureID) {
		Texture::Unbind(instance->m_textures[textureID]);
	}

	bool LoadTexture(GLenum target, char* path) {
		Texture* texture = new Texture();
		bool result = texture->Initialize(target, path);

		m_textures[texture->GetTextureID()] = texture;
		m_textureByName[texture->GetTextureName()] = texture->GetTextureID();

		return result;
	}

	GLuint GetTextureIDByName(std::string name) {
		return m_textureByName[name];
	}

protected:
	TextureManager();

	static TextureManager* instance;
	std::map<GLuint, Texture*> m_textures;
	std::map<std::string, GLuint> m_textureByName;
};

#endif