#ifndef _MESH_H_
#define _MESH_H_

#include "glew\glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

enum MeshBuffer { VERTEX_BUFFER, COLOUR_BUFFER, TEXTURE_BUFFER, MAX_BUFFER };

class Mesh {
public:	
	Mesh();
	~Mesh();

	virtual void Draw();
	static Mesh* GenerateTriangle();

	void SetTexture(GLuint textureID) { m_texture = textureID; }
	GLuint GetTexture()				  { return m_texture; }

protected:
	void BufferData();

	GLuint m_arrayObject;
	GLuint m_bufferObject[MAX_BUFFER];
	GLuint m_numVertices;
	GLuint m_type;
	GLuint m_texture;

	glm::vec3* m_vertices;
	glm::vec2* m_textureCoords;
	glm::vec4* m_colours;
};

#endif