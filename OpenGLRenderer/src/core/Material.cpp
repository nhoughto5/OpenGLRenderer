#include "pch.h"
#include "Material.h"

Material::Material() :
    m_LightService(LightService::GetInstance())
{
    OGLR_CORE_INFO("CREATING MATERIAL");
}

void Material::SetShader(std::string fileName)
{
    m_Shader.SetShaderFileName(fileName);
}

void Material::Enable() {
    m_Shader.Bind();
    for (const auto text : m_Textures) {
        text->Enable();
    }

    UploadUniforms();
}

void Material::Disable() {
    m_Shader.Unbind();
    for (const auto text : m_Textures) {
        text->Disable();
    }
}

void Material::AddTexture(std::string fileName) {
    m_Textures.push_back(std::make_shared<Texture>(fileName, m_Textures.size()));
}

void Material::UpdateTransform(glm::mat4& model, glm::mat4& view, glm::mat4& proj) {
    m_Shader.UploadUniformMat4("u_Projection", proj);
    m_Shader.UploadUniformMat4("u_View", view);
    m_Shader.UploadUniformMat4("u_Model", model);
}

void Material::UploadUniforms() {
    if (m_Shader.isLoaded()) {
        auto ambient = m_LightService->GetAmbientLight();
        m_Shader.UploadUniformFloat3("uAmbientLight", ambient.strength * ambient.color);
    }
}
