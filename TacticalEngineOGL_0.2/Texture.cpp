#include "Texture.h"

Texture::Texture() {
	m_textureID = 0;
	m_textureTarget = 0;
	m_textureName = "";
}

Texture::~Texture() {

}

bool Texture::Initialize(GLenum target, char* path) {
	bool result;

	glGenTextures(1, &m_textureID);
	m_textureTarget = target;

	std::string name(path);
	std::size_t  found = name.find_last_of("/\\");
	name = name.substr(found + 1);

	found = name.find_last_of(".");
	m_textureName = name.substr(0, found);

	result = LoadTexture(m_textureTarget, path);
	if (!result) {
		this->Shutdown();
		return false;
	}
}

bool Texture::Initialize(GLenum target, std::vector<char*> textureFaces) {

}