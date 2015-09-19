#include "Image.h"

Image::Image() {
	m_data = NULL;
	m_imagePath = NULL;
}

Image::~Image() {

}

bool Image::LoadImage(char* path, bool isCubemap, bool isHeightmap) {
	unsigned char* data;
	m_imagePath = path;

	if (!isHeightmap) {
		data = SOIL_load_image(m_imagePath, &m_width, &m_height, 0, SOIL_LOAD_AUTO);
		if (data == NULL) {
			return false;
		}
	}

	else {
		data = SOIL_load_image(m_imagePath, &m_width, &m_height, 0, SOIL_LOAD_L);
		if (data == NULL) {
			return false;
		}
	}

	m_data = data;

	return true;
}

void Image::DestroyImage() {
	if (m_data) {
		SOIL_free_image_data(m_data);
	}

	m_width = 0;
	m_height = 0;
	m_imagePath = NULL;

	delete this;
}