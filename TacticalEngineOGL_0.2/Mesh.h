#ifndef _MESH_H_
#define _MESH_H_

#include "glew\glew.h"
#include "glm\glm.hpp"

enum MeshBuffer { VERTEX_BUFFER, COLOUR_BUFFER, MAX_BUFFER };

class Mesh {
public:	
	Mesh();
	~Mesh();

	virtual void Draw();
	static Mesh* GenerateTriangle();

protected:
	void BufferData();

	GLuint m_arrayObject;
	GLuint m_bufferObject[MAX_BUFFER];
	GLuint m_numVertices;
	GLuint m_type;

	glm::vec3* m_vertices;
	glm::vec4* m_colours;
};

#endif