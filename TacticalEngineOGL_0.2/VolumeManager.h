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
	static VolumeManager* GetInstance() {
		if (m_instance == NULL) {
			m_instance = new VolumeManager();
		}
		return m_instance;
	}

	~VolumeManager();

	void UpdateChunks(glm::vec3 camPos, glm::vec3 camLookAt);
	void Draw(Shader* shader);

protected:
	VolumeManager();
	std::map<glm::vec3, VolumeChunk> m_chunks;

	static VolumeManager* m_instance;
	
	int m_numChunks;
	int m_chunkSize;
	
	glm::vec3 m_worldCenter;
	glm::vec3 m_lastCamPosition;
};

#endif