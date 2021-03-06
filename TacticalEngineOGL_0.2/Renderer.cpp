#include "Renderer.h"

Renderer* Renderer::m_instance = NULL;

Renderer::Renderer() {
	m_triangle = NULL;
	m_currentShader = NULL;
}

bool Renderer::Initialize(glm::vec2 screenDimensions) {
	(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "Starting renderer initialization...";

	m_triangle = Mesh::GenerateTriangle();

	bool result;
	bool criticalError = false;

	Texture* texture = new Texture();
	texture->Initialize(GL_TEXTURE_2D, "./Textures/bricks.jpg");
	m_triangle->SetTexture(texture);

	m_currentShader = new Shader();
	m_currentShader->Initialize();

	result = m_currentShader->LoadShaderFromFile(GL_VERTEX_SHADER, "./Shader/basicVertex.glsl");
	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_ERROR << "Could not not load vertex shader.";
	}

	result = m_currentShader->LoadShaderFromFile(GL_FRAGMENT_SHADER, "./Shader/basicFragment.glsl");
	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_ERROR << "Could not not load fragment shader.";
	}

	result = m_currentShader->CreateAndLinkProgram();
	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_ERROR << "Could not create and link shader program.";
		criticalError = true;
	}

	result = m_currentShader->AddUniform("viewProjectionMatrix");
	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "Could not find given uniform";
	}

	result = m_currentShader->AddUniform("modelMatrix");
	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "Could not find given uniform";
	}

	result = m_currentShader->AddUniform("diffuseTex");
	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_WARNING << "Could not find given uniform";
	}

	m_currentShader->SetDefaultAttributes();

	m_camera = new Camera();
	result = m_camera->Initialize(glm::vec3(0.0f, 0.0f, -7.0f), glm::vec3(0.0f, 0.0f, 0.0f), 
											45.0f, screenDimensions.x, screenDimensions.y);
	if (!result) {
		(*Logger::GetInstance()) << Logger::logType::LOG_ERROR << "Could not instantiate camera.";
		criticalError = true;
	}

	if (!criticalError)
		(*Logger::GetInstance()) << Logger::logType::LOG_INFO << "Renderer successfully initialized.";

	return !criticalError;
}

void Renderer::Shutdown() {
	delete m_triangle;

	if (m_currentShader) {
		m_currentShader->Shutdown();
	}
}

void Renderer::UpdateScene(float msec) {
	m_camera->Update(msec);
	m_viewProjectionMatrix = m_camera->GetViewProjection();
}

void Renderer::RenderScene() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_currentShader->Use();

	glm::mat4 modelMatrix(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f));

	m_modelMatrix = modelMatrix;

	UpdateShaderMatrices(m_currentShader);
	m_triangle->Draw();

	m_currentShader->UnUse();
}

void Renderer::UpdateShaderMatrices(Shader* shader) {
	glUniformMatrix4fv(shader->GetUniform("viewProjectionMatrix"), 1, GL_FALSE, 
					  glm::value_ptr(m_viewProjectionMatrix));
	glUniformMatrix4fv(shader->GetUniform("modelMatrix"), 1, false, (float*)&m_modelMatrix);
}