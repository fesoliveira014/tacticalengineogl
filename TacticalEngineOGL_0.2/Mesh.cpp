#include "Mesh.h"

Mesh::Mesh() {
	for (int i = 0; i < MAX_BUFFER; i++) {
		m_bufferObject[i] = 0;
	}

	glGenVertexArrays(1, &m_arrayObject);

	m_numVertices = 0;
	m_vertices = NULL;
	m_colours = NULL;
	m_type = GL_TRIANGLES;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_arrayObject);
	glDeleteBuffers(MAX_BUFFER, m_bufferObject);
	delete[] m_vertices;
	delete[] m_colours;
}

void Mesh::Draw() {
	glBindVertexArray(m_arrayObject);
	glDrawArrays(m_type, 0, m_numVertices);
	glBindVertexArray(0);
}

Mesh* Mesh::GenerateTriangle() {
	Mesh* mesh = new Mesh();
	mesh->m_numVertices = 3;

	mesh->m_vertices = new glm::vec3[mesh->m_numVertices];
	mesh->m_vertices[0] = glm::vec3(0.0f, 0.5f, 0.0f);
	mesh->m_vertices[1] = glm::vec3(0.5f, -0.5f, 0.0f);
	mesh->m_vertices[2] = glm::vec3(-0.5f, -0.5f, 0.0f);

	mesh->m_colours = new glm::vec4[mesh->m_numVertices];
	mesh->m_colours[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	mesh->m_colours[0] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	mesh->m_colours[0] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	mesh->BufferData();
	return mesh;
}

void Mesh::BufferData() {
	glBindVertexArray(m_arrayObject);

	glGenBuffers(1, &m_bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, m_numVertices*sizeof(glm::vec3), m_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);
	if (m_colours != NULL) {
		glGenBuffers(1, &m_bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_numVertices*sizeof(glm::vec4), m_colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}
	glBindVertexArray(0);
}