#include "Mesh.h"

Mesh::Mesh() {
	for (int i = 0; i < MAX_BUFFER; i++) {
		m_bufferObject[i] = 0;
	}

	glGenVertexArrays(1, &m_arrayObject);

	m_numVertices = 0;
	m_texture = 0;

	m_vertices = NULL;
	m_textureCoords = NULL;
	m_colours = NULL;
	m_type = GL_TRIANGLES;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_arrayObject);
	glDeleteBuffers(MAX_BUFFER, m_bufferObject);
	glDeleteTextures(1, &m_texture);
	delete[] m_vertices;
	delete[] m_colours;
	delete[] m_textureCoords;
}

void Mesh::Draw() {
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBindVertexArray(m_arrayObject);
	glDrawArrays(m_type, 0, m_numVertices);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Mesh* Mesh::GenerateTriangle() {
	Mesh* mesh = new Mesh();
	mesh->m_numVertices = 3;

	mesh->m_vertices = new glm::vec3[mesh->m_numVertices];
	mesh->m_vertices[0] = glm::vec3(0.0f, 0.5f, 0.0f);
	mesh->m_vertices[1] = glm::vec3(0.5f, -0.5f, 0.0f);
	mesh->m_vertices[2] = glm::vec3(-0.5f, -0.5f, 0.0f);

	mesh->m_textureCoords = new glm::vec2[mesh->m_numVertices];
	mesh->m_textureCoords[0] = glm::vec2(0.5f, 0.0f);
	mesh->m_textureCoords[1] = glm::vec2(1.0f, 1.0f);
	mesh->m_textureCoords[2] = glm::vec2(0.0f, 1.0f);

	mesh->m_colours = new glm::vec4[mesh->m_numVertices];
	mesh->m_colours[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	mesh->m_colours[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	mesh->m_colours[2] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	mesh->BufferData();

	return mesh;
}

void Mesh::BufferData() {
	glBindVertexArray(m_arrayObject);

	glGenBuffers(1, &m_bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, m_numVertices*sizeof(glm::vec3), m_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTEX_BUFFER);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	if (m_textureCoords != NULL) {
		glGenBuffers(1, &m_bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_numVertices*sizeof(glm::vec2), m_textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}
	if (m_colours != NULL) {
		glGenBuffers(1, &m_bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_numVertices*sizeof(glm::vec4), m_colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}
	glBindVertexArray(0);
}