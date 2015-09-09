#include "Mesh.h"

Mesh::Mesh() {
	for (int i = 0; i < MAX_BUFFER; i++) {
		m_bufferObject[i] = 0;
	}

	glGenVertexArrays(1, &m_arrayObject);

	m_numVertices = 0;
	m_vertices = glm::vec3();
	m_colours = glm::vec4();
	m_type = GL_TRIANGLES;
}

Mesh::~Mesh() {
}