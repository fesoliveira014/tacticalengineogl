#ifndef _MESH_H_
#define _MESH_H_

#include "glew\glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include <vector>

#include "Texture.h"
#include "Logger.h"

enum MeshBuffer { VERTEX_BUFFER, COLOUR_BUFFER, TEXTURE_BUFFER, MAX_BUFFER };

class Mesh {
public:	
	Mesh();
	~Mesh();

	Mesh(GLuint primitiveType, std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords, std::vector<glm::vec4> colours);

	virtual void Draw();

	static Mesh* GenerateTriangle();
	static Mesh* GenerateQuad();
	static Mesh* GenerateQuad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);

	void SetTexture(Texture* texture) { m_texture = texture; }
	Texture* GetTexture()				  { return m_texture; }

	void PushQuad(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);

	void SetType(GLuint type) { m_type = type; }

	void FlushVBO() {
		m_vertices.clear();
		m_textureCoords.clear();
		m_colours.clear();
		m_numVertices = 0;
	}

	void UpdateBufferData();
protected:

	GLuint m_arrayObject;
	GLuint m_bufferObject[MAX_BUFFER];
	GLuint m_numVertices;
	GLuint m_type;
	
	Texture* m_texture;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_textureCoords;
	std::vector<glm::vec4> m_colours;
};

#endif