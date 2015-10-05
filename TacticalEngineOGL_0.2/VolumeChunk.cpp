#include "VolumeChunk.h" 

VolumeChunk::VolumeChunk() {

}

VolumeChunk::VolumeChunk(glm::vec3 position, int size, int maxHeight, Shader* shader) :
m_chunkSize(size), m_maxHeight(maxHeight), m_position(position) {
	m_meshBuilder = new VolumeMeshBuilder(shader);
	
	m_isVisible = false;
	m_modified = false;
}

void VolumeChunk::StartGeometryBuild() {
	m_modified = false;
	m_meshBuilder->SetIterator(m_chunkData.begin());
	m_meshBuilder->StartBuilding();
}

void VolumeChunk::UpdateChunkGeometry(int buildCycles) {
	if (!m_isVisible) {
		m_meshBuilder->ClearVertexLists();
		m_meshBuilder->FinishedBuild();
	}
	else {
		m_meshBuilder->BuildMesh(this, buildCycles);
		if(!IsMeshBuilderRunning())
			m_meshBuilder->BuildDisplayLists();
	}
}

void VolumeChunk::Draw(Shader* shader) {
	if (!m_isVisible) {
		return;
	}
	m_meshBuilder->Draw(this, shader);
}

bool VolumeChunk::RequireGeometryUpdate() {
	return m_modified && m_isVisible && !IsMeshBuilderRunning();
}

bool VolumeChunk::IsMeshBuilderRunning() {
	return m_meshBuilder->IsBuilderRunning();
}

bool VolumeChunk::IsSolid(glm::vec3 pos) {
	return m_chunkData.IsSolid(pos);
}

void VolumeChunk::SetVisibleFaces(FaceGroup visibleFaces) {
	if (m_meshBuilder->GetVisibleFaces() != visibleFaces) {
		m_meshBuilder->SetVisibleFaces(visibleFaces);
		m_meshBuilder->BuildDisplayLists();
	}
}

bool VolumeChunk::IsModified() {
	return m_modified;
}

void VolumeChunk::Updated() {
	m_modified = false;
}

// placeholder
bool VolumeChunk::IsOccludedByNeighbors() {
	return false;
}

void VolumeChunk::Fill() {
	m_chunkData.Fill();
	m_modified = true;
	m_isVisible = true;
}

void VolumeChunk::Empty() {
	m_chunkData.Empty();
	m_modified = true;
	m_isVisible = false;
}

void VolumeChunk::Set(glm::vec3 pos, uint8_t type) {
	m_chunkData.Set(pos, type);
	m_modified = m_chunkData.IsModified() || m_modified;
	m_isVisible = !m_chunkData.IsEmpty();
	m_chunkData.Updated();
}

uint8_t VolumeChunk::Get(glm::vec3 pos) {
	return m_chunkData.Get(pos);
}

void VolumeChunk::SetModified() {
	m_modified = true;
}

void VolumeChunk::SetPosition(glm::vec3 pos) {
	m_position = pos;
}

void VolumeChunk::SetSize(int size) {
	m_chunkSize = size;
}

