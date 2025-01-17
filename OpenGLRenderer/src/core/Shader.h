#pragma once
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include "glm/glm.hpp"

class Shader {
public:
    Shader();
    Shader(const std::string& filePath);
    Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void SetShaderFileName(std::string fileName);
    void Bind() const;
    void Unbind() const;
    void UploadUniformBool(const std::string& name, bool value);
    void UploadUniformInt(const std::string& name, int value);
    void UploadUniformFloat(const std::string& name, float value);
    void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
    void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
    void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
    void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    uint32_t ShaderId() { return m_ProgramId; }
    bool isLoaded();
private:
    std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source);
    void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
    std::string ReadFile(const std::string& filePath);

    uint32_t m_ProgramId;
    std::string m_VertexCode, m_FragmentCode, m_Name;
    bool m_IsLoaded{ false };
};

