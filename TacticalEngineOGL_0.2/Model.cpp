#include "Model.h"

Model::Model(glm::vec3 position) {
	m_position = position;
	m_meshes.clear();
}

Model::~Model() {
	if (!m_meshes.empty()) {
		for (Mesh* mesh : m_meshes) {
			delete mesh;
		}
	}

	m_meshes.clear();
}

bool Model::LoadFromObj(string path) {
	return true;
}

void Model::Draw() {
	for (Mesh* mesh : m_meshes) {
		mesh->Draw();
	}
}
