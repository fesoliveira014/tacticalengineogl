#ifndef _CUBE_H_
#define _CUBE_H_

#include "Model.h"



class Cube : public Model {
public:
	struct CubeFace {
		Mesh* face;
		bool  isVisible;

		CubeFace() {}
		CubeFace(Mesh* mesh) {
			face = mesh;
			isVisible = true;
		}

	};

	Cube(glm::vec3 position) {
		Model::Model(position);

		Mesh* frontFace = Mesh::GenerateQuad(glm::vec3(-0.5f, -0.5f, 0.5f),
											 glm::vec3(-0.5f, 0.5f, 0.5f),
											 glm::vec3(0.5f, -0.5f, 0.5f),
											 glm::vec3( 0.5f,  0.5f, 0.5f));

		Mesh* backFace = Mesh::GenerateQuad(glm::vec3(0.5f, -0.5f, -0.5f),
											glm::vec3(0.5f, 0.5f, -0.5f),
										    glm::vec3(-0.5f, -0.5f, -0.5f),
											glm::vec3(-0.5f, 0.5f,0- 0.5f));

		Mesh* leftFace = Mesh::GenerateQuad(glm::vec3(-0.5f, -0.5f, -0.5f),
											glm::vec3(-0.5f, 0.5f, -0.5f),
											glm::vec3(-0.5f, -0.5f, 0.5f),
											glm::vec3(-0.5f, 0.5f,  0.5f));

		Mesh* rightFace = Mesh::GenerateQuad(glm::vec3( 0.5f, -0.5f,  0.5f),
											 glm::vec3( 0.5f,  0.5f,  0.5f),
											 glm::vec3( 0.5f,  -0.5f, -0.5f),
											 glm::vec3( 0.5f,  0.5f, -0.5f));

		Mesh* bottomFace = Mesh::GenerateQuad(glm::vec3(-0.5f, -0.5f, -0.5f),
											  glm::vec3(-0.5f, -0.5f,  0.5f),
											  glm::vec3( 0.5f, -0.5f, -0.5f),
											  glm::vec3( 0.5f, -0.5f,  0.5f));

		Mesh* topFace = Mesh::GenerateQuad(glm::vec3(-0.5f, 0.5f, 0.5f),
										   glm::vec3( -0.5f,  0.5f,  -0.5f),
										   glm::vec3(0.5f, 0.5f, 0.5f),
										   glm::vec3( 0.5f, 0.5f, -0.5f));

		m_faces[0] = new CubeFace(frontFace);
		m_faces[1] = new CubeFace(backFace);
		m_faces[2] = new CubeFace(leftFace);
		m_faces[3] = new CubeFace(rightFace);
		m_faces[4] = new CubeFace(topFace);
		m_faces[5] = new CubeFace(bottomFace);
	}

	~Cube();

	void Draw() {
		for (int i = 0; i < 6; ++i) {
			if (m_faces[i]->isVisible) {
				m_faces[i]->face->Draw();
			}
		}
	}

	void SetTexture(Texture* texture) {
		for (auto face : m_faces) {
			face->face->SetTexture(texture);
		}
	}

	CubeFace* m_faces[6];
};

#endif