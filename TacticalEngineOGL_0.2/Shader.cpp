#include "Shader.h"

Shader::Shader() {

}

Shader::~Shader() {

}

bool Shader::Initialize(Logger* logger) {
	m_vertexShader = 0;
	m_fragmentShader = 0;
	m_geometryShader = 0;
	m_shaderProgram = 0;

	m_attributeList.clear();
	m_uniformList.clear();

	m_logger = logger;

	return true;
}

void Shader::Shutdown() {
	DeleteShaderProgram();
	m_shaderProgram = 0;

	m_attributeList.clear();
	m_uniformList.clear();
}

bool Shader::LoadShaderFromFile(GLenum shaderType, const char* filename) {
	(*m_logger) << Logger::logType::LOG_INFO << "Loading shader...";
	bool result;

	string shaderSource;

	result = ReadFile(filename, shaderSource);
	if (!result) {
		(*m_logger) << Logger::logType::LOG_ERROR << "Failed to read file " + string(filename) + ".";
		return false;
	}

	result = Compile(shaderSource.c_str(), shaderType);
	if (!result) {
		(*m_logger) << Logger::logType::LOG_WARNING << "Failed to compile shader.";
		return false;
	}

	(*m_logger) << Logger::logType::LOG_INFO << "Shader " + string(filename) + " successfully initialized.";
	return true;
}

bool Shader::CreateAndLinkProgram() {
	(*m_logger) << Logger::logType::LOG_INFO << "Starting shader program creation and linkage...";

	m_shaderProgram = glCreateProgram();
	if (m_shaderProgram == 0) {
		(*m_logger) << Logger::logType::LOG_ERROR << "Shader program could not be created.";
		return false;
	}

	if (m_vertexShader != 0) {
		glAttachShader(m_shaderProgram, m_vertexShader);
	}

	if (m_fragmentShader != 0) {
		glAttachShader(m_shaderProgram, m_vertexShader);
	}

	if (m_geometryShader != 0) {
		glAttachShader(m_shaderProgram, m_geometryShader);
	}

	GLint success = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(m_shaderProgram);

	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, sizeof(errorLog), NULL, errorLog);
		(*m_logger) << Logger::logType::LOG_ERROR << "Error linking shader program: " + string(errorLog);
		return false;
	}

	glValidateProgram(m_shaderProgram);

	glGetProgramiv(m_shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, sizeof(errorLog), NULL, errorLog);
		(*m_logger) << Logger::logType::LOG_WARNING << "Invalid shader program: " + string(errorLog);
		return false;
	}

	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteShader(m_geometryShader);

	(*m_logger) << Logger::logType::LOG_INFO << "Shaders successfully created and linked.";

	return true;
}

bool Shader::Compile(const char* shaderSource, GLenum shaderType) {
	(*m_logger) << Logger::logType::LOG_INFO << "Starting shader compilation...";
	GLuint shaderObject = glCreateShader(shaderType);

	if (shaderObject == 0) {
		(*m_logger) << Logger::logType::LOG_ERROR << "Error creating shader of type " + std::to_string(shaderType);
		return false;
	}

	const GLchar* sources[1];
	sources[0] = shaderSource;
	GLint lengths[1];
	lengths[0] = strlen(shaderSource);

	glShaderSource(shaderObject, 1, sources, lengths);

	glCompileShader(shaderObject);

	GLint success;

	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderObject, sizeof(infoLog), NULL, infoLog);
		(*m_logger) << Logger::logType::LOG_ERROR << "Error compiling shader of type " + std::to_string(shaderType);
		return false;
	}

	if (shaderType == GL_VERTEX_SHADER)
		m_vertexShader = shaderObject;
	else if (shaderType == GL_FRAGMENT_SHADER)
		m_fragmentShader = shaderObject;
	else if (shaderType == GL_GEOMETRY_SHADER)
		m_geometryShader == shaderObject;

	(*m_logger) << Logger::logType::LOG_INFO << "Shader successfully compiled.";

	return true;
}

bool Shader::AddAttribute(string attribute) {
	GLuint attributeLocation = glGetAttribLocation(m_shaderProgram, attribute.c_str());

	if (attributeLocation == 0xFFFFFFFF) {
		(*m_logger) << Logger::logType::LOG_ERROR << "Attribute '" + attribute + "' not found in the program.";
		return false;
	}

	m_attributeList[attribute] = attributeLocation;

	(*m_logger) << Logger::logType::LOG_INFO << "Attribute '" + attribute + "' added to the attribute list.";
	return true;
}

bool Shader::AddUniform(string uniform) {
	GLuint uniformLocation = glGetUniformLocation(m_shaderProgram, uniform.c_str());

	if (uniformLocation == 0xFFFFFFFF) {
		(*m_logger) << Logger::logType::LOG_ERROR << "Uniform '" + uniform + "' not found in the program.";
		return false;
	}

	m_uniformList[uniform] = uniformLocation;

	(*m_logger) << Logger::logType::LOG_INFO << "Uniform '" + uniform + "' added to the uniform list.";
	return true;
}

GLuint Shader::GetAttribute(string attribute) {
	if (m_attributeList.find(attribute) == m_attributeList.end()) {
		(*m_logger) << Logger::logType::LOG_WARNING << "There is no attribute '" + attribute + "' in the shader program.";
		return 0;
	}

	return m_attributeList[attribute];
}

GLuint Shader::GetUniform(string uniform) {
	if (m_uniformList.find(uniform) == m_uniformList.end()) {
		(*m_logger) << Logger::logType::LOG_WARNING << "There is no uniform '" + uniform + "' in the shader program.";
		return 0;
	}

	return m_uniformList[uniform];
}