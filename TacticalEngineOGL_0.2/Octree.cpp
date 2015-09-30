#include "Octree.h"

Octree::Octree() {

}

Octree::~Octree() {
	if (root)
		RecursiveDeletion(root);
}

void Octree::Draw() {
	if (root)
		DrawNode(root);
}

void Octree::UpdateVisibleNodes() {
	m_visibleNodes.clear();
	CheckVisibility(root);
}

bool Octree::Insert(const Voxel &voxel) {
	return InsertRecursive(root, voxel);
}

bool Octree::Remove(const Voxel &voxel) {
	return RemoveRecursive(root, voxel);
}

void Octree::RecursiveDeletion(OctNode* node) {
	if (node->m_type == LEAF) {
		delete node;
	}
	else {
		RecursiveDeletion(node->m_child[0]);
		RecursiveDeletion(node->m_child[1]);
		RecursiveDeletion(node->m_child[2]);
		RecursiveDeletion(node->m_child[3]);
		RecursiveDeletion(node->m_child[4]);
		RecursiveDeletion(node->m_child[5]);
		RecursiveDeletion(node->m_child[6]);
		RecursiveDeletion(node->m_child[7]);

		delete node;
	}
}

bool Octree::InsertRecursive(OctNode* node, const Voxel &voxel) {
	if (node->m_type == LEAF) {
		if (node->m_isEmpty) {
			node->m_voxel = Voxel(voxel);
			node->m_isEmpty = false;
			return true;
		}
		else if (node->m_depth < m_maxDepth) {
			Voxel oldData = Voxel(node->m_voxel);
			
			node->m_child[0] = new OctNode(node, glm::vec3(node->m_center.x - node->m_halfLength, 
														   node->m_center.y + node->m_halfLength, 
														   node->m_center.z + node->m_halfLength), node->m_center, node->m_depth + 1);

			node->m_child[1] = new OctNode(node, glm::vec3(node->m_center.x + node->m_halfLength,
														   node->m_center.y + node->m_halfLength,
														   node->m_center.z + node->m_halfLength), node->m_center, node->m_depth + 1);

			node->m_child[2] = new OctNode(node, glm::vec3(node->m_center.x + node->m_halfLength,
														   node->m_center.y + node->m_halfLength,
														   node->m_center.z - node->m_halfLength), node->m_center, node->m_depth + 1);

			node->m_child[3] = new OctNode(node, glm::vec3(node->m_center.x - node->m_halfLength,
														   node->m_center.y + node->m_halfLength,
														   node->m_center.z - node->m_halfLength), node->m_center, node->m_depth + 1);

			node->m_child[4] = new OctNode(node, glm::vec3(node->m_center.x - node->m_halfLength,
														   node->m_center.y - node->m_halfLength,
														   node->m_center.z + node->m_halfLength), node->m_center, node->m_depth + 1);

			node->m_child[5] = new OctNode(node, glm::vec3(node->m_center.x + node->m_halfLength,
														   node->m_center.y - node->m_halfLength,
														   node->m_center.z + node->m_halfLength), node->m_center, node->m_depth + 1);
			
			node->m_child[6] = new OctNode(node, glm::vec3(node->m_center.x + node->m_halfLength,
														   node->m_center.y - node->m_halfLength,
														   node->m_center.z - node->m_halfLength), node->m_center, node->m_depth + 1);

			node->m_child[7] = new OctNode(node, glm::vec3(node->m_center.x - node->m_halfLength,
				 										   node->m_center.y - node->m_halfLength,
														   node->m_center.z - node->m_halfLength), node->m_center, node->m_depth + 1);
			node->m_type = NODE;

			bool result1 = false; 
			bool result2 = false;

			for (int i = 0; i < 8; ++i) {
				if (node->m_child[i]->m_boundingBox.Contains(oldData.m_position)) {
					result1 = InsertRecursive(node->m_child[i], oldData);
				}
				if (node->m_child[i]->m_boundingBox.Contains(voxel.m_position)) {
					result2 = InsertRecursive(node->m_child[i], voxel);
				}
				if (result1 && result2) break;
			}

			return result1 && result2;

		}
	}
	else {
		for (int i = 0; i < 8; ++i) {
			if (node->m_child[i]->m_boundingBox.Contains(voxel.m_position)) {
				return InsertRecursive(node->m_child[i], voxel);
			}
		}
	}
}

bool Octree::RemoveRecursive(OctNode* node, const Voxel &voxel) {
	if (node->m_type == LEAF) {
		node->m_voxel.m_type = EMPTY;
		node->m_isEmpty = true;
	}
	else {
		for (int i = 0; i < 8; ++i) {
			if (node->m_child[i]->m_boundingBox.Contains(voxel.m_position)) {
				return RemoveRecursive(node->m_child[i], voxel);
			}
		}
	}
}

void Octree::Traversal(Ray ray) {

}

void Octree::CheckVisibility(OctNode* node) {
	
}
