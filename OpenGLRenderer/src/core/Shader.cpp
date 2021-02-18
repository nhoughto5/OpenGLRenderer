#include "pch.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <glad/glad.h>

static GLenum ShaderTypeFromString(const std::string& type) {
	if (type == "vertex") return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

	OGLR_CORE_ASSERT(false, "Unkown Shader type");
	return 0;
}

Shader::Shader()
{
}

Shader::Shader(const std::string& filePath) {
    std::string source = ReadFile(SHADER_FOLDER + filePath);
    auto shaderSources = PreProcess(source);
    Compile(shaderSources);

    auto lastSlash = filePath.find_last_of("/\\");
    lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
    auto lastDot = filePath.rfind('.');
    auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
    m_Name = filePath.substr(lastSlash, count);
}

Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = fragmentSrc;
	m_Name = name;
	Compile(sources);
}

Shader::~Shader() {
	glDeleteProgram(m_ProgramId);
}

void Shader::SetShaderFileName(std::string fileName)
{
    std::string source = ReadFile(SHADER_FOLDER + fileName);
    auto shaderSources = PreProcess(source);
	m_Name = fileName;
    Compile(shaderSources);
}

void Shader::Compile(std::unordered_map<GLenum, std::string>& shaderSources) {
	GLint program = glCreateProgram();
	OGLR_CORE_ASSERT(shaderSources.size() <= 2, "Only support two shaders");
	std::array<GLenum, 2> glShaderIds;
	int glShaderId = 0;
	for (auto&& [type, source] : shaderSources) {
		GLuint shader = glCreateShader(type);
		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shader);

			// Use the infoLog as you see fit.
			OGLR_CORE_ERROR("{0}", infoLog.data());
			OGLR_CORE_ASSERT(false, "Shader Compilation Failure!");

			// In this simple program, we'll just leave
			return;
		}

		glAttachShader(program, shader);
		glShaderIds[glShaderId++] = shader;
	}

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);

		for (auto id : glShaderIds) {
			glDeleteShader(id);
		}

		// Use the infoLog as you see fit.
		OGLR_CORE_ERROR("{0}", infoLog.data());
		OGLR_CORE_ASSERT(false, "Shader Link Failure!");

		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	for (auto id : glShaderIds) {
		glDetachShader(program, id);
	}

	m_ProgramId = program;
	m_IsLoaded = true;
	OGLR_CORE_INFO("Sucesfully Compiled Shader: {0}", m_Name);
}

std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source) {
	std::unordered_map<GLenum, std::string> shaderSources;
	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);

	while (pos != std::string::npos) {
		size_t eol = source.find_first_of("\r\n", pos);
		OGLR_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		OGLR_CORE_ASSERT(ShaderTypeFromString(type), "Invalid Shader type");

		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		pos = source.find(typeToken, nextLinePos);
		shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
	}

	return shaderSources;
}

std::string Shader::ReadFile(const std::string& filePath) {
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	std::string result;

	if (in) {
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else {
		OGLR_CORE_ERROR("Could not open file {0}", filePath);
	}

	return result;
}

void Shader::Bind() const {
	glUseProgram(m_ProgramId);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

void Shader::UploadUniformBool(const std::string& name, bool value) {
	UploadUniformInt(name, value);
}

void Shader::UploadUniformInt(const std::string& name, int value) {
	GLint location = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform1i(location, value);
}

void Shader::UploadUniformFloat(const std::string& name, float value) {
	GLint location = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform1f(location, value);
}

void Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& values) {
	GLint location = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform2f(location, values.x, values.y);
}

void Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& values) {
	GLint location = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform3f(location, values.x, values.y, values.z);
}

void Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& values) {
	GLint location = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniform4f(location, values.x, values.y, values.z, values.w);
}

void Shader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
	GLint location = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
	GLint location = glGetUniformLocation(m_ProgramId, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

bool Shader::isLoaded() {
	return m_IsLoaded;
}

