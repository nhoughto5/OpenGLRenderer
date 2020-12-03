#pragma once
#include "GLFW/glfw3.h"
#include <glad/glad.h>

class Shader {
public:
    Shader(const std::string& filePath);
    Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();
    void Bind() const;
    void Unbind() const;
    void UploadUniformInt(const std::string& name, int value);
    void UploadUniformFloat(const std::string& name, float value);
    void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
    void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
    void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
    void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
    std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source);
    void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
    std::string ReadFile(const std::string& filePath);

    uint32_t m_ProgramId;
    std::string m_VertexCode, m_FragmentCode;
};

