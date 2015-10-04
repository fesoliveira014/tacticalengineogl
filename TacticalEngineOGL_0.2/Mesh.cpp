#include "Mesh.h"
#include "Logger.h"

Mesh::Mesh() {
	for (int i = 0; i < MAX_BUFFER; i++) {
		m_bufferObject[i] = 0;
	}

	glGenVertexArrays(1, &m_arrayObject);

	m_numVertices = 0;
	m_texture = 0;

	m_vertices.clear();
	m_textureCoords.clear();
	m_colours.clear();

	m_type = GL_TRIANGLES;
}

Mesh::Mesh(GLuint primitiveType, std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<glm::vec4> colours) {
	Mesh::Mesh();
	
	m_type = primitiveType;
	m_numVertices = vertices.size();

	(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "Size of vertex vector: " + std::to_string(vertices.size());
	
	m_vertices.resize(m_numVertices);
	for (int i = 0; i < m_numVertices; ++i) {
		m_vertices[i] = vertices[i];
	}

	if (!texCoords.empty()) {
		m_textureCoords.resize(m_numVertices);
		for (int i = 0; i < m_numVertices; ++i) {
			m_textureCoords[i] = texCoords[i];
		}
	}

	if (!colours.empty()) {
		m_colours.resize(m_numVertices);
		for (int i = 0; i < m_numVertices; ++i) {
			m_colours[i] = colours[i];
		}
	}

	UpdateBufferData();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_arrayObject);
	glDeleteBuffers(MAX_BUFFER, m_bufferObject);

	if (m_texture != NULL)
		m_texture->Shutdown();

	m_vertices.clear();
	m_colours.clear();
	m_textureCoords.clear();
}

void Mesh::Draw() {
	if (m_texture != 0) Texture::Bind(m_texture);
	glBindVertexArray(m_arrayObject);
	glDrawArrays(m_type, 0, m_numVertices);
	glBindVertexArray(0);
	if (m_texture != 0) Texture::Unbind(m_texture);
}

Mesh* Mesh::GenerateTriangle() {
	Mesh* mesh = new Mesh();
	mesh->m_numVertices = 3;

	mesh->m_vertices.resize(mesh->m_numVertices);
	mesh->m_vertices[0] = glm::vec3(0.0f, 0.5f, 0.0f);
	mesh->m_vertices[1] = glm::vec3(0.5f, -0.5f, 0.0f);
	mesh->m_vertices[2] = glm::vec3(-0.5f, -0.5f, 0.0f);

	mesh->m_textureCoords.resize(mesh->m_numVertices);
	mesh->m_textureCoords[0] = glm::vec2(0.5f, 0.0f);
	mesh->m_textureCoords[1] = glm::vec2(1.0f, 1.0f);
	mesh->m_textureCoords[2] = glm::vec2(0.0f, 1.0f);

	mesh->m_colours.resize(mesh->m_numVertices);
	mesh->m_colours[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	mesh->m_colours[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	mesh->m_colours[2] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	mesh->UpdateBufferData();

	return mesh;
}

Mesh* Mesh::GenerateQuad() {
	Mesh* mesh = new Mesh();
	mesh->m_type = GL_TRIANGLE_STRIP;
	mesh->m_numVertices = 4;

	mesh->m_vertices.resize(mesh->m_numVertices);
	mesh->m_textureCoords.resize(mesh->m_numVertices);
	mesh->m_colours.resize(mesh->m_numVertices);

	mesh->m_vertices[0] = glm::vec3(-0.5f, -0.5f, 0.0f);
	mesh->m_vertices[1] = glm::vec3(-0.5f,  0.5f, 0.0f);
	mesh->m_vertices[2] = glm::vec3( 0.5f, -0.5f, 0.0f);
	mesh->m_vertices[3] = glm::vec3( 0.5f,  0.5f, 0.0f);

	mesh->m_textureCoords[0] = glm::vec2(0.0f, 1.0f);
	mesh->m_textureCoords[1] = glm::vec2(0.0f, 0.0f);
	mesh->m_textureCoords[2] = glm::vec2(1.0f, 1.0f);
	mesh->m_textureCoords[3] = glm::vec2(1.0f, 0.0f);

	for (int i = 0; i < 4; ++i) {
		mesh->m_colours[i] = glm::vec4(1.0f);
	}

	mesh->UpdateBufferData();
	return mesh;
}

Mesh* Mesh::GenerateQuad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) {
	Mesh* mesh = new Mesh();
	mesh->m_type = GL_TRIANGLE_STRIP;
	mesh->m_numVertices = 4;

	mesh->m_vertices.resize(mesh->m_numVertices);
	mesh->m_textureCoords.resize(mesh->m_numVertices);
	mesh->m_colours.resize(mesh->m_numVertices);

	mesh->m_vertices[0] = p1;
	mesh->m_vertices[1] = p2;
	mesh->m_vertices[2] = p3;
	mesh->m_vertices[3] = p4;

	mesh->m_textureCoords[0] = glm::vec2(0.0f, 1.0f);
	mesh->m_textureCoords[1] = glm::vec2(0.0f, 0.0f);
	mesh->m_textureCoords[2] = glm::vec2(1.0f, 1.0f);
	mesh->m_textureCoords[3] = glm::vec2(1.0f, 0.0f);

	for (int i = 0; i < 4; ++i) {
		mesh->m_colours[i] = glm::vec4(1.0f);
	}

	mesh->UpdateBufferData();
	return mesh;
}

void Mesh::PushQuad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) {
	m_vertices.push_back(p1);
	m_vertices.push_back(p2);
	m_vertices.push_back(p3);
	m_vertices.push_back(p4);

	m_textureCoords.push_back(glm::vec2(0.0f, 1.0f));
	m_textureCoords.push_back(glm::vec2(0.0f, 0.0f));
	m_textureCoords.push_back(glm::vec2(1.0f, 1.0f));
	m_textureCoords.push_back(glm::vec2(1.0f, 0.0f));

	m_colours.push_back(glm::vec4(1.0f));
	m_colours.push_back(glm::vec4(1.0f));
	m_colours.push_back(glm::vec4(1.0f));
	m_colours.push_back(glm::vec4(1.0f));

	m_numVertices += 4;
	//(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "numvertices: " + std::to_string(m_numVertices);
	UpdateBufferData();
}

void Mesh::UpdateBufferData() {
	glBindVertexArray(m_arrayObject);

	glGenBuffers(1, &m_bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, m_numVertices*sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTEX_BUFFER);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	if (!m_textureCoords.empty()) {
		glGenBuffers(1, &m_bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_numVertices*sizeof(glm::vec2), &m_textureCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}
	if (!m_colours.empty()) {
		glGenBuffers(1, &m_bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, m_numVertices*sizeof(glm::vec4), &m_colours[0], GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}
	glBindVertexArray(0);
}