#ifndef _VOLUME_MESH_BUILDER_H_
#define _VOLUME_MESH_BUILDER_H_

#include "glew\glew.h"

#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include <vector>

#include "BaseVolume.h"
#include "VolumeChunk.h"
#include "Shader.h"
#include "Frustum.h"

/*
Volume Mesh Builder
Given volume data, calculates vertices using the frustum and considering occlusion.
*/

enum Face {
	TOP, BOTTOM, RIGHT, LEFT, FRONT, BACK
};

enum VisibleFaceX {DRAW_BOTH_X, DRAW_LEFT, DRAW_RIGHT};
enum VisibleFaceY {DRAW_BOTH_Y, DRAW_BOTTOM, DRAW_TOP};
enum VisibleFaceZ {DRAW_BOTH_Z, DRAW_BACK, DRAW_FRONT};

struct FaceGroup {
	VisibleFaceX x;
	VisibleFaceY y;
	VisibleFaceZ z;

	FaceGroup() {}
	FaceGroup(VisibleFaceX x, VisibleFaceY y, VisibleFaceZ z) : x(x), y(y), z(z) {

	}

	inline friend bool operator==(const FaceGroup& group1, const FaceGroup& group2) {
		return group1.x == group2.x && group1.y == group2.y && group1.z == group2.z;
	}

	inline friend bool operator!=(const FaceGroup& group1, const FaceGroup& group2) {
		return !(group1 == group2);
	}
};

class VolumeMeshBuilder {
public:
	VolumeMeshBuilder(Shader* shader);
	~VolumeMeshBuilder();

	void BuildMesh(VolumeChunk* chunk, int maxCycles);
	void BuildDisplayLists();

	void Draw(VolumeChunk* chunk, Shader* shader);

	void AddFace(glm::vec3 pos, Face face, int size);

	void StartBuilding() { m_meshBuilderRunning = true; }
	void FinishedBuild() { m_meshBuilderRunning = false; }
	bool IsBuilderRunning() { return m_meshBuilderRunning; }

	void ClearVertexBuffers();
	void ClearVertexLists();

	FaceGroup GetVisibleFaces() { return m_visiblefaces; }
	void SetVisibleFaces(FaceGroup visibleFaces) { m_visiblefaces = visibleFaces; }

	void SetIterator(VolumeIterator iterator);

protected:
	void SwapBuffers();

	std::vector<glm::vec4> m_topFaceVertices;
	std::vector<glm::vec4> m_bottomFaceVertices;
	std::vector<glm::vec4> m_rightFaceVertices;
	std::vector<glm::vec4> m_leftFaceVertices;
	std::vector<glm::vec4> m_frontFaceVertices;
	std::vector<glm::vec4> m_backFaceVertices;

	std::vector<glm::vec4> m_topFaceVerticesBuf;
	std::vector<glm::vec4> m_bottomFaceVerticesBuf;
	std::vector<glm::vec4> m_rightFaceVerticesBuf;
	std::vector<glm::vec4> m_leftFaceVerticesBuf;
	std::vector<glm::vec4> m_frontFaceVerticesBuf;
	std::vector<glm::vec4> m_backFaceVerticesBuf;

	GLuint m_topVBO;
	GLuint m_bottomVBO;
	GLuint m_rightVBO;
	GLuint m_leftVBO;
	GLuint m_frontVBO;
	GLuint m_backVBO;

	GLuint m_posAttrib;
	GLuint m_normAttrib;
	GLuint m_worldPosAttib;

	int m_numVerticesRendered;
	bool m_meshBuilderRunning;

	FaceGroup m_visiblefaces;

	VolumeIterator m_chunkIterator;
};

#endif