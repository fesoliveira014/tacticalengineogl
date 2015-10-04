#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Texture.h"

struct byte4 {
	uint8_t x, y, z, w;

	byte4() {}
	byte4(uint8_t x, uint8_t y, uint8_t z, uint8_t w) : x(x), y(y), z(z), w(w) {}
};

#define CHUNK_SIZE 10

class Chunk{
public:
	Chunk();
	Chunk(glm::vec3 position);
	~Chunk();

	void Draw();
	void Update();

	void FillChunk() {
		for (int i = 0; i < CHUNK_SIZE; ++i) {
			for (int j = 0; j < CHUNK_SIZE; ++j) {
				for (int k = 0; k < CHUNK_SIZE; ++k) {
					m_block[i][j][k] = 1;
				}
			}
		}
	}

	void Set(glm::vec3 pos, uint8_t type) {
		int x = (int)pos.x; int y = (int)pos.y; int z = (int)pos.z;

		m_block[x][y][z] = type;
		m_changed = true;
	}

	uint8_t Get(glm::vec3 pos) {
		int x = (int)pos.x; int y = (int)pos.y; int z = (int)pos.z;
		return m_block[x][y][z];
	}

	void SetTexture(Texture* texture) {
		m_texture = texture;
	}

	glm::vec3 GetPosition() { return m_position; }

protected:
	uint8_t m_block[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	byte4 vertices[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 6 * 4];

	bool m_changed;
	static unsigned int numChunks;
	unsigned int m_id;

	GLuint vbo;
	
	int m_numVertices;

	Texture* m_texture;

	glm::vec3 m_position;
};

#endif
