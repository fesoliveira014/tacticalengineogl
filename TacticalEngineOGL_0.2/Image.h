#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>

#include "SOIL\SOIL.h"

class Image {
	Image();
	~Image();

	bool LoadImage(char* path, bool isCubemap = false, bool isHeightmap = false);
	void DestroyImage();

	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }

	unsigned char* GetData() { return m_data; }

protected:
	unsigned char* m_data;
	char* m_imagePath;
	int m_width, m_height;
};

#endif