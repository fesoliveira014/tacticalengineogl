#ifndef _OCTREE_H_
#define _OCTREE_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include <iostream>
#include <vector>

#include "Voxel.h"



struct Ray {
	// r = p + td, p = <px, py, pz>, d = <dx, dy, dz> and t is a vector
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() {}

	Ray(glm::vec3 p, glm::vec3 d) {
		origin = p;
		direction = d;
	}

	Ray(float px, float py, float pz, float dx, float dy, float dz) {
		origin = glm::vec3(px, py, pz);
		direction = glm::vec3(dz, dy, dz);
	}
};

struct AABB {
	glm::vec3 p1, p2;

	AABB() {};

	AABB(glm::vec3 v1, glm::vec3 v2) {
		p1 = v1;
		p2 = v2;
	}

	AABB(float x1, float y1, float z1, float x2, float y2, float z2) {
		p1 = glm::vec3(x1, y1, z1);
		p2 = glm::vec3(x2, y2, z2);
	}

	AABB(glm::vec3 center, float cubeLength) {
		p1 = glm::vec3(center.x + cubeLength / 2.0f, center.y + cubeLength / 2.0f, center.z + cubeLength / 2.0f);
		p2 = glm::vec3(center.x - cubeLength / 2.0f, center.y - cubeLength / 2.0f, center.z - cubeLength / 2.0f);
	}

	bool Contains(glm::vec3 point) {
		bool contains = (point.x >= p1.x && point.x <= p2.x &&
						 point.y >= p1.y && point.y <= p2.y &&
						 point.z >= p1.z && point.z <= p2.z);

		return contains;
	}
};

/*
Octrees are, per definition, recursive structures. Trying to 'encapsulate' some of it's propreties is naive.
That baing said, in order to properly manipulate data on a octree, one must always be dealing with the nodes
that the said tree. That it, insertion, removal, transversal: all of these require a node as a parameter, other-
wise searching the data structure is impossible, since we need recursion.

----------------------------------
Insertion algorithm: the idea is simple: if we are at a leaf, add data to it if it is empty; else, check if it 
is terminal and if not, create its children and add old data and new data to their respective octants. If it not
a leaf, get octant containing data position and add data to that octant.
----------------------------------
insert(node, data):
	if node is leaf:
		if node is empty:
			node.data <- data
			return
		else if node depth is not max depth:
			oldData = node.data
			for i in range 0 to 7:
				create node.child[i]
			insert(node.child[octant containg point oldData.position], oldData)
			insert(node.child[octant containg point data.position], data)
	else:
		octant <- child octant of node containing point data.position
		insert(octant, data)
----------------------------------

----------------------------------
Removal algorithm: removal is simple in this case. If node is a leaf and it contains data, delete data from node. 
Else, if it is not a leaf, find octant containg data position and apply removal method to that octant.
----------------------------------
remove(node, data):
	if node is leaf:
		if node contains data:
			node.data <- empty
	else:
		octant <- child octant of current node containing data.position
		remove(octant, data)
	return


*/

class Octree {
public:
	enum NodeType { ROOT, NODE, LEAF };

	struct OctNode {
		OctNode* m_parent;
		OctNode* m_child[8]; // 0: TLF; 1: TRF; 2: TRB; 3: TLB; 
							 // 4: BLF; 5: BRF; 6: BRF; 7: BRB;

		NodeType m_type;

		bool m_exists;
		bool m_isVisible;
		bool m_hasChildren;
		bool m_isEmpty;

		int m_depth;
		AABB m_boundingBox;
		glm::vec3 m_center;
		float m_halfLength;

		Voxel m_voxel;

		OctNode() {}
		OctNode(OctNode* parentNode,  glm::vec3 corner1, glm::vec3 corner2, int depth) {
			m_boundingBox = AABB(corner1, corner2);
			m_halfLength = (float)glm::abs(corner2.x - corner1.x) / 2.0f;
			m_center = glm::vec3(corner1.x + m_halfLength, corner1.y + m_halfLength, corner1.z + m_halfLength);

			for (int i = 0; i < 8; ++i) {
				m_child[i] = NULL;
			}

			m_depth = depth;
			m_parent = parentNode;

			m_exists = true;
			m_isVisible = false;
			m_hasChildren = false;
			m_isEmpty = true;

			if (m_parent == NULL)
				m_type = ROOT;
			else if (!m_hasChildren)
				m_type = LEAF;
			else
				m_type = NODE;
		}
	};

	Octree(glm::vec3 corner1, glm::vec3 corner2, int maxDepth) {
		m_maxDepth = maxDepth;
		root = new OctNode(NULL, corner1, corner2, 0);
	}
	~Octree();

	void Draw();
	void UpdateVisibleNodes();

	bool Insert(const Voxel &voxel);
	bool Remove(const Voxel &voxel);

	void Traversal();

private:
	Octree();
	void RecursiveDeletion(OctNode* node);
	bool InsertRecursive(OctNode* node, const Voxel &voxel);
	bool RemoveRecursive(OctNode* node, const Voxel &voxel);
	void TraversalRecursive(OctNode* node);
	void CheckVisibility(OctNode* node);

	void DrawNode(OctNode* node){}
	int m_maxDepth;

	std::vector<OctNode> m_visibleNodes;

	OctNode* root;
};

#endif
