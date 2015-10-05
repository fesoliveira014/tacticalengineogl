#include "Texture.h"

Texture::Texture() {
	m_textureID = 0;
	m_textureTarget = 0;
	m_textureName = "";
}

Texture::~Texture() {
	Shutdown();
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
		(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "Could not load texture " + m_textureName + ".";
		this->Shutdown();
		return false;
	}

	return true;
}

bool Texture::Initialize(GLenum target, std::vector<char*> textureFaces) {
	bool result;

	glGenTextures(1, &m_textureID);

	result = LoadTexture(m_textureTarget, textureFaces);
	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "Could not load texture array.";
		this->Shutdown();
		return false;
	}

	return true;
}

void Texture::Shutdown() {
	if (m_textureID) {
		glDeleteTextures(1, &m_textureID);
	}

	if (m_textureTarget) {
		m_textureTarget = 0;
	}

	m_textureName.clear();
}

bool Texture::LoadTexture(GLenum target, char *path) {
	bool result;

	switch (target) {
	case (GL_TEXTURE_1D) :
		result = LoadTexture1D(path);
		break;

	case (GL_TEXTURE_2D) :
		result = LoadTexture2D(path);
		break;

	case (GL_TEXTURE_3D) :
		result = LoadTexture3D(path);
		break;

	case (GL_TEXTURE_RECTANGLE) :
		result = LoadTextureRectangle(path);
		break;

	case (GL_TEXTURE_1D_ARRAY) :
		result = LoadTexture1DArray(path);
		break;

	case (GL_TEXTURE_2D_ARRAY) :
		result = LoadTexture2DArray(path);
		break;

	case (GL_TEXTURE_CUBE_MAP_ARRAY) :
		result = LoadTextureCubemapArray(path);
		break;

	case (GL_TEXTURE_2D_MULTISAMPLE) :
		result = LoadTexture2DMultisample(path);
		break;

	case (GL_TEXTURE_2D_MULTISAMPLE_ARRAY) :
		result = LoadTexture2DMultisampleArray(path);
		break;

	default:
		(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "Invalid texture target.";
		return false;
	}

	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_ERROR << "Failed to read image file.";
		return false;
	}

	return true;
}

bool Texture::LoadTexture(GLenum target, std::vector<char*> textureFaces) {
	bool result;

	result = LoadTextureCubemap(textureFaces);

	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_ERROR << "Failed to read image file.";
		return false;
	}

	return true;
}

bool Texture::LoadTexture1D(char *path) {
	Image *image = new Image();
	bool result;

	result = image->Image::LoadImage(path);

	if (!result) {
		delete image;
		return false;
	}

	glBindTexture(m_textureTarget, m_textureID);
	glTexImage1D(m_textureTarget, 0, GL_RGB, image->GetWidth(),
		image->GetHeight(), 0, GL_UNSIGNED_BYTE, image->GetData());

	glGenerateMipmap(m_textureTarget);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image->DestroyImage();

	glBindTexture(m_textureTarget, 0);

	return true;
}

bool Texture::LoadTexture2D(char *path) {
	Image *image = new Image();
	bool result;

	result = image->Image::LoadImage(path);

	if (!result) {
		delete image;
		return false;
	}

	glBindTexture(m_textureTarget, m_textureID);

	glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(m_textureTarget, 0, GL_RGB, image->GetWidth(), image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetData());

	glGenerateMipmap(m_textureTarget);

	//glGenerateMipmap(m_textureTarget);


	image->DestroyImage();

	glBindTexture(m_textureTarget, 0);

	return true;
}

bool Texture::LoadTexture3D(char *path) {
	/*
	Texture3DFile* image = new Texture3DFile();
	bool result;

	result = image->Texture3DFile::LoadImage(path);
	if (!result)
	{
	return false;
	}

	this->BindTexture();
	glTexImage3D(m_textureTarget, 0, GL_RGB, image->GetWidth(), image->GetHeight(),
	image->GetDepth(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetData());

	glGenerateMipmap(m_textureTarget);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image->DestroyImage();

	Texture::Unbind();

	return true;
	*/

	(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "3D textures not yet implemented.";
	return false;
}

bool Texture::LoadTextureRectangle(char *path) {
	Image *image = new Image();
	bool result;

	result = image->Image::LoadImage(path);

	if (!result) {
		delete image;
		return false;
	}

	glBindTexture(m_textureTarget, m_textureID);
	glTexImage2D(m_textureTarget, 0, GL_RGB, image->GetWidth(), image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetData());

	glGenerateMipmap(m_textureTarget);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image->DestroyImage();

	glBindTexture(m_textureTarget, 0);

	return true;
}

bool Texture::LoadTextureCubemap(std::vector<char *> textureFaces) {
	Image *image = new Image();
	bool result;

	for (int i = 0; i < textureFaces.size(); i++) {
		result = image->Image::LoadImage(textureFaces[i]);

		if (!result) {
			delete image;
			return false;
		}

		glBindTexture(m_textureTarget, m_textureID);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, image->GetWidth(),
			image->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetData());
	}

	glTexParameteri(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	image->DestroyImage();

	glBindTexture(m_textureTarget, 0);

	return true;
}

bool Texture::LoadTexture1DArray(char *path) {
	(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "1D texture arrays not yet implemented.";
	return false;
}

bool Texture::LoadTexture2DArray(char *path) {
	(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "2D texture arrays not yet implemented.";
	return false;
}

bool Texture::LoadTextureCubemapArray(char *path) {
	(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "Cubemap texture arrays not yet implemented.";
	return false;
}

bool Texture::LoadTexture2DMultisample(char *path) {
	(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "2D multisample textures not yet implemented.";
	return false;
}

bool Texture::LoadTexture2DMultisampleArray(char *path) {
	(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "2D multisample texture arrays not yet implemented.";
	return false;
}