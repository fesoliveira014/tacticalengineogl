#include "Renderer.h"

Renderer* Renderer::m_instance = NULL;

Renderer::Renderer() {
	m_triangle = NULL;
	m_currentShader = NULL;
	m_logger = NULL;
}

bool Renderer::Initialize(glm::vec2 screenDimensions, Logger *logger) {
	m_logger = logger;
	(*m_logger) << Logger::logType::LOG_INFO << "Starting renderer initialization...";

	m_triangle = Mesh::GenerateTriangle();

	bool result;
	bool criticalError = false;

	m_currentShader = new Shader();
	m_currentShader->Initialize(m_logger);

	result = m_currentShader->LoadShaderFromFile(GL_VERTEX_SHADER, "./Shader/basicVertex.glsl");
	if (!result) {
		(*m_logger) << Logger::logType::LOG_ERROR << "Could not not load vertex shader.";
	}

	result = m_currentShader->LoadShaderFromFile(GL_FRAGMENT_SHADER, "./Shader/basicFragment.glsl");
	if (!result) {
		(*m_logger) << Logger::logType::LOG_ERROR << "Could not not load fragment shader.";
	}

	result = m_currentShader->CreateAndLinkProgram();
	if (!result) {
		(*m_logger) << Logger::logType::LOG_ERROR << "Could not create and link shader program.";
		criticalError = true;
	}

	m_camera = new Camera();
	result = m_camera->Initialize(glm::vec3(0.0f, 0.0f, -7.0f), glm::vec3(0.0f, 0.0f, -1.0f), 
											45.0f, screenDimensions.x, screenDimensions.y);
	if (!result) {
		(*m_logger) << Logger::logType::LOG_ERROR << "Could not instantiate camera.";
		criticalError = true;
	}

	if (!criticalError)
		(*m_logger) << Logger::logType::LOG_INFO << "Renderer successfully initialized.";

	return !criticalError;
}

void Renderer::Shutdown() {
	delete m_triangle;

	if (m_currentShader) {
		m_currentShader->Shutdown();
	}

	m_logger = NULL;
}

void Renderer::UpdateScene() {

}

void Renderer::RenderScene() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_currentShader->Use();
	m_triangle->Draw();
	m_currentShader->UnUse();
}