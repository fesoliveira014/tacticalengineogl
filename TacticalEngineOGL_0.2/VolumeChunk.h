#ifndef _VOLUME_CHUNK_
#define _VOLUME_CHUNK_

#include <unordered_map>

#include "BaseVolume.h"
#include "VolumeMeshBuilder.h"

class VolumeChunk {
public:
	VolumeChunk();
	~VolumeChunk();

	void Draw();
	void Update();

	bool IsModified() { return m_modified; }
	void Updated();

	bool IsOccludedBtyNeighbors();

	glm::vec3 GetPosition() { return m_position; }
	int GetSize() { return m_chunkSize; }

	friend class VolumeMeshBuilder;

protected:
	void BuildGeometry();

	BaseVolume m_chunkData;

	int m_chunkSize;

	bool m_isVisible;
	bool m_modified;
	bool m_meshBuildRunning;

	glm::vec3 m_position;
};

#endif