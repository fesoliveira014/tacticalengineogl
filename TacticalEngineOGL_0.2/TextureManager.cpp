#include "TextureManager.h"

TextureManager* TextureManager::instance = NULL;

TextureManager::TextureManager() {
	m_textures.clear();
}