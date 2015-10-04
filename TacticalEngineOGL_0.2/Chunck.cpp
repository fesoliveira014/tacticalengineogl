#include "Chunk.h"

unsigned int Chunk::numChunks = 0;

Chunk::Chunk() {
	memset(m_block, 0, sizeof(m_block));
	m_changed = true;
	m_id = ++numChunks;
	m_position = glm::vec3(0.0f);
	m_numVertices = 0;
	glGenBuffers(1, &vbo);
	m_texture = NULL;
}

Chunk::Chunk(glm::vec3 position) {
	Chunk::Chunk();
	m_position = position;
}

Chunk::~Chunk() {
	glDeleteBuffers(1, &vbo);
}

void Chunk::Update() {
	if (m_changed == true) {
		m_changed = false;

		m_numVertices = 0;

		for (int i = 0; i < CHUNK_SIZE; ++i) {
			for (int j = 0; j < CHUNK_SIZE; ++j) {
				for (int k = 0; k < CHUNK_SIZE; ++k) {
					if (m_block[i][j][k] == 0)
						continue;
					
					// front
					vertices[++m_numVertices] = byte4(i , j , k + 1, m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i , j + 1, k + 1, m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j , k + 1, m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j + 1, k + 1, m_block[i][j][k]);

					// back
					vertices[++m_numVertices] = byte4(i + 1, j , k , m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j + 1,  k , m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i , j , k , m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i , j + 1, k , m_block[i][j][k]);

					// left
					vertices[++m_numVertices] = byte4(i , j , k , m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i , j + 1, k , m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i , j , k + 1, m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i , j + 1, k + 1, m_block[i][j][k]);

					// right
					vertices[++m_numVertices] = byte4(i + 1, j , k + 1, m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j + 1, k + 1, m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j , k , m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j + 1, k , m_block[i][j][k]);

					// bottom
					vertices[++m_numVertices] = byte4(i , j , k , m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i , j , k + 1, m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j , k , m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j , k + 1, m_block[i][j][k]);

					// top
					vertices[++m_numVertices] = byte4(i , j + 1, k + 1, m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i , j + 1, k , m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j + 1, k + 1, m_block[i][j][k]),
					vertices[++m_numVertices] = byte4(i + 1, j + 1, k , m_block[i][j][k]);

					//(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "[i, j, k]: (" + std::to_string(i) + ", " + std::to_string(j) + ", " + std::to_string(k) + ")";
				}
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(*vertices), vertices, GL_STATIC_DRAW);
	}
}

void Chunk::Draw() {
	Update();
	//std::cout << "kek2" << std::endl;

	if (m_numVertices == 0)
		return;

	//(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "numVertices: " + std::to_string(m_numVertices);
	if (m_texture != NULL) Texture::Bind(m_texture);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_numVertices);
	if (m_texture != NULL) Texture::Unbind(m_texture);
}