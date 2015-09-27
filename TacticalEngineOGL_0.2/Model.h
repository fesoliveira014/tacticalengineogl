#ifndef _MODEL_H_
#define _MODEL_H_

#include "glew\glew.h"
#include "GLFW\glfw3.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include <vector>
#include <string>

class Model {
public:
	Model() {}
	Model(glm::vec3 position);
	~Model();

	bool LoadFromObj(std::string path);

	virtual void Draw();

	void SetPosition(glm::vec3 position) { m_position = position; }
	glm::vec3 GetPosition() { return m_position; }

	virtual void SetTexture(Texture* texture) {
		for (Mesh* mesh : m_meshes) {
			mesh->SetTexture(texture);
		}
	}

protected:
	glm::vec3 m_position;
	std::vector<Mesh*> m_meshes;
};

#endif