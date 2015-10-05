#include "VolumeMeshBuilder.h"

VolumeMeshBuilder::VolumeMeshBuilder(Shader* shader) {
	m_topFaceVertices.clear();
	m_bottomFaceVertices.clear();
	m_rightFaceVertices.clear();
	m_leftFaceVertices.clear();
	m_frontFaceVertices.clear();
	m_backFaceVertices.clear();

	m_topFaceVerticesBuf.clear();
	m_bottomFaceVerticesBuf.clear();
	m_rightFaceVerticesBuf.clear();
	m_leftFaceVerticesBuf.clear();
	m_frontFaceVerticesBuf.clear();
	m_backFaceVerticesBuf.clear();

	glGenBuffers(1, &m_topVBO);
	glGenBuffers(1, &m_bottomVBO);
	glGenBuffers(1, &m_rightVBO);
	glGenBuffers(1, &m_leftVBO);
	glGenBuffers(1, &m_frontVBO);
	glGenBuffers(1, &m_backVBO);

	shader->Use();
	m_posAttrib = shader->GetAttribute("position");
	m_normAttrib = shader->GetAttribute("normal");
	m_worldPosAttib = shader->GetAttribute("worldPosition");
	shader->UnUse();

	m_meshBuilderRunning = false;
	m_numVerticesRendered = 0;

	m_visiblefaces.x = DRAW_BOTH_X;
	m_visiblefaces.y = DRAW_BOTH_Y;
	m_visiblefaces.z = DRAW_BOTH_Z;
}

void VolumeMeshBuilder::BuildMesh(VolumeChunk* chunk, Frustum frustum, int maxCycles) {
	if (chunk->IsModified()) {
		chunk->Updated();
		m_chunkIterator = chunk->m_chunkData.begin();
	}

	glm::vec3 coords;

	// executes when starting from zero
	if (m_chunkIterator == chunk->m_chunkData.begin()) {
		ClearVertexBuffers();

		if (chunk->IsOccludedBtyNeighbors()) {
			ClearVertexLists();
			m_meshBuilderRunning = false;
			return;
		}

		if (chunk->m_chunkData.IsFull()) {
			AddFace(glm::vec3(0), TOP, chunk->GetSize());
			AddFace(glm::vec3(0), BOTTOM, chunk->GetSize());
			AddFace(glm::vec3(0), RIGHT, chunk->GetSize());
			AddFace(glm::vec3(0), LEFT, chunk->GetSize());
			AddFace(glm::vec3(0), FRONT, chunk->GetSize());
			AddFace(glm::vec3(0), BACK, chunk->GetSize());
			SwapBuffers();
			m_meshBuilderRunning = false;
			return;
		}
	}

	for (int i = 0; i < maxCycles; ++i) {
		if (m_chunkIterator == chunk->m_chunkData.end()) {
			SwapBuffers();
			m_meshBuilderRunning = false;
			m_chunkIterator = chunk->m_chunkData.begin();
		}

		coords = (*m_chunkIterator).first;

		if (coords.x > 0) {
			if (chunk->m_chunkData.LeftVisible(coords)) {
				AddFace(coords, LEFT, 1);
			}
		}

		if (coords.x < chunk->m_chunkSize -1) {
			if (chunk->m_chunkData.RightVisible(coords)) {
				AddFace(coords, RIGHT, 1);
			}
		}

		if (coords.y > 0) {
			if (chunk->m_chunkData.LeftVisible(coords)) {
				AddFace(coords, BOTTOM, 1);
			}
		}

		if (coords.y < chunk->m_chunkSize - 1) {
			if (chunk->m_chunkData.RightVisible(coords)) {
				AddFace(coords, TOP, 1);
			}
		}

		if (coords.z > 0) {
			if (chunk->m_chunkData.LeftVisible(coords)) {
				AddFace(coords, BACK, 1);
			}
		}

		if (coords.z < chunk->m_chunkSize - 1) {
			if (chunk->m_chunkData.RightVisible(coords)) {
				AddFace(coords, FRONT, 1);
			}
		}

		++m_chunkIterator;
	}
}

void VolumeMeshBuilder::BuildDisplayLists() {
	m_numVerticesRendered = 0;
	if (!m_frontFaceVertices.empty() && (m_visiblefaces.z == DRAW_FRONT || m_visiblefaces.z == DRAW_BOTH_Z)) {
		m_numVerticesRendered += m_frontFaceVertices.size();
		glBindBuffer(GL_ARRAY_BUFFER, m_frontVBO);
		glBufferData(GL_ARRAY_BUFFER, m_frontFaceVertices.size(), &m_frontFaceVertices[0], GL_STATIC_DRAW);
	}
	if (!m_backFaceVertices.empty() && (m_visiblefaces.z == DRAW_BACK || m_visiblefaces.z == DRAW_BOTH_Z)) {
		m_numVerticesRendered += m_backFaceVertices.size();
		glBindBuffer(GL_ARRAY_BUFFER, m_backVBO);
		glBufferData(GL_ARRAY_BUFFER, m_backFaceVertices.size(), &m_backFaceVertices[0], GL_STATIC_DRAW);
	}
	if (!m_leftFaceVertices.empty() && (m_visiblefaces.x == DRAW_LEFT || m_visiblefaces.x == DRAW_BOTH_X)) {
		m_numVerticesRendered += m_leftFaceVertices.size();
		glBindBuffer(GL_ARRAY_BUFFER, m_leftVBO);
		glBufferData(GL_ARRAY_BUFFER, m_leftFaceVertices.size(), &m_leftFaceVertices[0], GL_STATIC_DRAW);
	}
	if (!m_rightFaceVertices.empty() && (m_visiblefaces.x == DRAW_RIGHT || m_visiblefaces.x == DRAW_BOTH_X)) {
		m_numVerticesRendered += m_rightFaceVertices.size();
		glBindBuffer(GL_ARRAY_BUFFER, m_rightVBO);
		glBufferData(GL_ARRAY_BUFFER, m_rightFaceVertices.size(), &m_rightFaceVertices[0], GL_STATIC_DRAW);
	}
	if (!m_topFaceVertices.empty() && (m_visiblefaces.y == DRAW_TOP || m_visiblefaces.y == DRAW_BOTH_Y)) {
		m_numVerticesRendered += m_topFaceVertices.size();
		glBindBuffer(GL_ARRAY_BUFFER, m_topVBO);
		glBufferData(GL_ARRAY_BUFFER, m_topFaceVertices.size(), &m_topFaceVertices[0], GL_STATIC_DRAW);
	}
	if (!m_bottomFaceVertices.empty() && (m_visiblefaces.y == DRAW_BOTTOM || m_visiblefaces.y == DRAW_BOTH_Y)) {
		m_numVerticesRendered += m_bottomFaceVertices.size();
		glBindBuffer(GL_ARRAY_BUFFER, m_bottomVBO);
		glBufferData(GL_ARRAY_BUFFER, m_bottomFaceVertices.size(), &m_bottomFaceVertices[0], GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VolumeMeshBuilder::Draw(VolumeChunk* chunk, Shader* shader) {
	shader->Use();

	glUniform3fv(m_worldPosAttib, 1, glm::value_ptr(chunk->m_position));

	glEnableVertexAttribArray(m_posAttrib);
	if (m_visiblefaces.z == DRAW_FRONT || m_visiblefaces.z == DRAW_BOTH_Z) {
		glUniform3fv(m_normAttrib, 1, glm::value_ptr(glm::vec3(0, 0, -1)));
		glBindBuffer(GL_ARRAY_BUFFER, m_frontVBO);
		glVertexAttribPointer(m_posAttrib, 4, GL_INT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, m_frontFaceVertices.size());
	}
	if (m_visiblefaces.z == DRAW_BACK || m_visiblefaces.z == DRAW_BOTH_Z) {
		glUniform3fv(m_normAttrib, 1, glm::value_ptr(glm::vec3(0, 0, 1)));
		glBindBuffer(GL_ARRAY_BUFFER, m_backVBO);
		glVertexAttribPointer(m_posAttrib, 4, GL_INT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, m_backFaceVertices.size());
	}
	if (m_visiblefaces.x == DRAW_LEFT|| m_visiblefaces.x == DRAW_BOTH_X) {
		glUniform3fv(m_normAttrib, 1, glm::value_ptr(glm::vec3(1, 0, 0)));
		glBindBuffer(GL_ARRAY_BUFFER, m_leftVBO);
		glVertexAttribPointer(m_posAttrib, 4, GL_INT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, m_rightFaceVertices.size());
	}
	if (m_visiblefaces.x == DRAW_RIGHT || m_visiblefaces.x == DRAW_BOTH_X) {
		glUniform3fv(m_normAttrib, 1, glm::value_ptr(glm::vec3(-1, 0, 0)));
		glBindBuffer(GL_ARRAY_BUFFER, m_rightVBO);
		glVertexAttribPointer(m_posAttrib, 4, GL_INT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, m_rightFaceVertices.size());
	}
	if (m_visiblefaces.y == DRAW_TOP || m_visiblefaces.y == DRAW_BOTH_Y) {
		glUniform3fv(m_normAttrib, 1, glm::value_ptr(glm::vec3(0, -1, 0)));
		glBindBuffer(GL_ARRAY_BUFFER, m_topVBO);
		glVertexAttribPointer(m_posAttrib, 4, GL_INT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, m_topFaceVertices.size());
	}
	if (m_visiblefaces.y == DRAW_BOTTOM || m_visiblefaces.y == DRAW_BOTH_Y) {
		glUniform3fv(m_normAttrib, 1, glm::value_ptr(glm::vec3(0, 1, 0)));
		glBindBuffer(GL_ARRAY_BUFFER, m_bottomVBO);
		glVertexAttribPointer(m_posAttrib, 4, GL_INT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, m_backFaceVertices.size());
	}
	glDisableVertexAttribArray(m_posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->UnUse();
}

void VolumeMeshBuilder::AddFace(glm::vec3 pos, Face face, int size) {
	glm::vec4 vertex;
	int size = size;
	vertex.w = pos.y; // Vector.w is static.

	switch (face) {
	case TOP:
		// Add a new face.
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z + size; m_topFaceVerticesBuf.push_back(vertex); //C
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z;   m_topFaceVerticesBuf.push_back(vertex); //D
		vertex.x = pos.x;   vertex.y = pos.y + size; vertex.z = pos.z + size; m_topFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x;   vertex.y = pos.y + size; vertex.z = pos.z + size; m_topFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z;   m_topFaceVerticesBuf.push_back(vertex); //D
		vertex.x = pos.x;   vertex.y = pos.y + size; vertex.z = pos.z;   m_topFaceVerticesBuf.push_back(vertex); //A
		break;

	case BOTTOM:
		// Add a new face.
		vertex.x = pos.x + size; vertex.y = pos.y;   vertex.z = pos.z + size; m_bottomFaceVerticesBuf.push_back(vertex); //C
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z + size; m_bottomFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x + size; vertex.y = pos.y;   vertex.z = pos.z;   m_bottomFaceVerticesBuf.push_back(vertex); //D
		vertex.x = pos.x + size; vertex.y = pos.y;   vertex.z = pos.z;   m_bottomFaceVerticesBuf.push_back(vertex); //D
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z + size; m_bottomFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z;   m_bottomFaceVerticesBuf.push_back(vertex); //A
		break;

	case LEFT:
		// Add a new face.
		vertex.x = pos.x;   vertex.y = pos.y + size; vertex.z = pos.z + size; m_leftFaceVerticesBuf.push_back(vertex); //A
		vertex.x = pos.x;   vertex.y = pos.y + size; vertex.z = pos.z;   m_leftFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z + size; m_leftFaceVerticesBuf.push_back(vertex); //D
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z + size; m_leftFaceVerticesBuf.push_back(vertex); //D
		vertex.x = pos.x;   vertex.y = pos.y + size; vertex.z = pos.z;   m_leftFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z;   m_leftFaceVerticesBuf.push_back(vertex); //C
		break;

	case RIGHT:
		// Add a new face.
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z + size; m_rightFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x + size; vertex.y = pos.y;   vertex.z = pos.z + size; m_rightFaceVerticesBuf.push_back(vertex); //C
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z;   m_rightFaceVerticesBuf.push_back(vertex); //A
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z;   m_rightFaceVerticesBuf.push_back(vertex); //A
		vertex.x = pos.x + size; vertex.y = pos.y;   vertex.z = pos.z + size; m_rightFaceVerticesBuf.push_back(vertex); //C
		vertex.x = pos.x + size; vertex.y = pos.y;   vertex.z = pos.z;   m_rightFaceVerticesBuf.push_back(vertex); //D
		break;

	case FRONT:
		// Add a new face.
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z + size; m_frontFaceVerticesBuf.push_back(vertex); //A
		vertex.x = pos.x;   vertex.y = pos.y + size; vertex.z = pos.z + size; m_frontFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z + size; m_frontFaceVerticesBuf.push_back(vertex); //C
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z + size; m_frontFaceVerticesBuf.push_back(vertex); //C
		vertex.x = pos.x + size; vertex.y = pos.y;   vertex.z = pos.z + size; m_frontFaceVerticesBuf.push_back(vertex); //D
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z + size; m_frontFaceVerticesBuf.push_back(vertex); //A
		break;

	case BACK:
		// Add a new face.
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z;   m_backFaceVerticesBuf.push_back(vertex); //D
		vertex.x = pos.x;   vertex.y = pos.y + size; vertex.z = pos.z;   m_backFaceVerticesBuf.push_back(vertex); //A
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z;   m_backFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x + size; vertex.y = pos.y + size; vertex.z = pos.z;   m_backFaceVerticesBuf.push_back(vertex); //B
		vertex.x = pos.x + size; vertex.y = pos.y;   vertex.z = pos.z;   m_backFaceVerticesBuf.push_back(vertex); //C
		vertex.x = pos.x;   vertex.y = pos.y;   vertex.z = pos.z;   m_backFaceVerticesBuf.push_back(vertex); //D
		break;

	default:
		break;
	}
}

void VolumeMeshBuilder::ClearVertexBuffers() {
	m_topFaceVerticesBuf.clear();
	m_bottomFaceVerticesBuf.clear();
	m_rightFaceVerticesBuf.clear();
	m_leftFaceVerticesBuf.clear();
	m_frontFaceVerticesBuf.clear();
	m_backFaceVerticesBuf.clear();
}

void VolumeMeshBuilder::ClearVertexLists() {
	m_topFaceVertices.clear();
	m_bottomFaceVertices.clear();
	m_rightFaceVertices.clear();
	m_leftFaceVertices.clear();
	m_frontFaceVertices.clear();
	m_backFaceVertices.clear();
}

void VolumeMeshBuilder::SwapBuffers() {
	m_topFaceVertices.swap(m_topFaceVerticesBuf);
	m_bottomFaceVertices.swap(m_bottomFaceVerticesBuf);
	m_rightFaceVertices.swap(m_rightFaceVerticesBuf);
	m_leftFaceVertices.swap(m_leftFaceVerticesBuf);
	m_frontFaceVertices.swap(m_frontFaceVerticesBuf);
	m_backFaceVertices.swap(m_backFaceVerticesBuf);
}