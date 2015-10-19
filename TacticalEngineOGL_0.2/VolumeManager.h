#ifndef _VOLUME_MANAGER_H_
#define _VOLUME_MANAGER_H_

#include <glew\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Shader.h"
#include "Camera.h"
#include "VolumeChunk.h"

#include <map>
#include <vector>

class VolumeManager {
	VolumeManager();
	~VolumeManager();

	void Draw(Shader* shader, glm::vec3 camPos, glm::vec3 camLookAt);

protected:
	std::map<glm::vec3, VolumeChunk> chunks;
	
	int m_numChunks;
	int m_chunkSize;
	
	glm::vec3 m_worldCenter;
	glm::vec3 m_lastCamPosition;
};

#endif