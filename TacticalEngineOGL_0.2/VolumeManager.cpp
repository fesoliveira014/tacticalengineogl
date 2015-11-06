#include "VolumeManager.h"

VolumeManager* VolumeManager::m_instance = NULL;

VolumeManager::VolumeManager() {
	m_numChunks = 0;
	m_chunkSize = 0;

	m_worldCenter = glm::vec3(0.0f);
	m_lastCamPosition = glm::vec3(0.0f);

	m_chunks.clear();
}

VolumeManager::~VolumeManager() {

}

void VolumeManager::UpdateChunks(glm::vec3 camPos, glm::vec3 camLookAt) {
	int cycles = 100000;
	for (std::map<glm::vec3, VolumeChunk>::iterator it = m_chunks.begin(); 
			it != m_chunks.end(); it++) {
		if ((*it).second.RequireGeometryUpdate())
			(*it).second.UpdateChunkGeometry(cycles);
	}
}

void VolumeManager::Draw(Shader* shader) {
	for (it = m_chunks.begin(); it != m_chunks.end(); it++) {
		
	}
}