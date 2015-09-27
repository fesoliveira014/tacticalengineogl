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
	CheckVisibility(root, &m_visibleNodes);
}

bool Octree::Insert(Voxel voxel) {
	if (true) {
		
	}
}