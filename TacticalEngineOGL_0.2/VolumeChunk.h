#ifndef _VOLUME_CHUNK_
#define _VOLUME_CHUNK_

#include <unordered_map>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "Shader.h"
#include "BaseVolume.h"
#include "VolumeMeshBuilder.h"

class VolumeChunk {
public:
	VolumeChunk(glm::vec3 position, int size, int maxHeight, Shader* shader);
	~VolumeChunk();

	void Draw(Shader* shader);

	void StartGeometryBuild();
	void UpdateChunkGeometry(int buildCycles);

	bool RequireGeometryUpdate();
	bool IsMeshBuilderRunning();

	bool IsSolid(glm::vec3 pos);

	void SetVisibleFaces(FaceGroup visibleFaces);

	bool IsModified();
	void Updated();

	// placeholder
	bool IsOccludedByNeighbors();
	bool IsLeftNeighborSolid(glm::vec3 pos);
	bool IsRightNeighborSolid(glm::vec3 pos);
	bool IsTopNeighborSolid(glm::vec3 pos);
	bool IsBottomNeighborSolid(glm::vec3 pos);
	bool IsFrontNeighborSolid(glm::vec3 pos);
	bool IsBackNeighborSolid(glm::vec3 pos);

	void SetTopNeighbor(VolumeChunk* chunk);
	void SetBottomNeighbor(VolumeChunk* chunk);
	void SetLeftNighbor(VolumeChunk* chunk);
	void SetRightNeighbor(VolumeChunk* chunk);
	void SetFrontNeighbor(VolumeChunk* chunk);
	void SetBackNeighbor(VolumeChunk* chunk);

	bool IsTopBorderFull();
	bool IsBottomBorderFull();
	bool IsRightBorderFull();
	bool IsLeftBorderFull();
	bool IsFrontBorderFull();
	bool IsBackBorderFull();

	void Fill();
	void Empty();

	void Set(glm::vec3 pos, uint8_t type);
	uint8_t Get(glm::vec3 pos);

	void SetModified();

	void SetPosition(glm::vec3 pos);
	glm::vec3 GetPosition() { return m_position; }
	void SetSize(int size);
	int GetSize() { return m_chunkSize; }

	friend class VolumeMeshBuilder;

protected:
	VolumeChunk();
	void BuildGeometry();

	BaseVolume m_chunkData;

	int m_chunkSize;
	int m_maxHeight;

	bool m_isVisible;
	bool m_modified;

	glm::vec3 m_position;

	VolumeMeshBuilder* m_meshBuilder;

	// need to include neighbour checks both here and on the mesh builder
	VolumeChunk* m_topNeighbour;
	VolumeChunk* m_bottomNeighbour;
	VolumeChunk* m_rightNeighbour;
	VolumeChunk* m_leftNeighbour;
	VolumeChunk* m_frontNeighbour;
	VolumeChunk* m_backNeighbour;
};

#endif