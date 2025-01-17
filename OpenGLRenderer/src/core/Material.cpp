#include "pch.h"
#include "Material.h"

Material::Material() :
    m_LightService(LightService::GetInstance()) {
    OGLR_CORE_INFO("CREATING MATERIAL");
}

void Material::SetShader(std::string fileName) {
    m_Shader.SetShaderFileName(fileName);
}

void Material::Enable() {
    m_Shader.Bind();
    for (const auto text : m_Textures) {
        text->Enable();
    }

    UploadUniforms();
}

void Material::UploadUniforms() {
    if (m_Shader.isLoaded()) {
        auto ambient = m_LightService->GetAmbientLight();
        m_Shader.UploadUniformFloat4("uAmbientLight", glm::vec4(ambient.color, ambient.strength));
        for (const auto& light : m_LightService->GetLights()) {
            m_Shader.UploadUniformFloat3("u_LightPosition", light->position);
            m_Shader.UploadUniformFloat3("u_LightAttenuation", light->attenuation);
            m_Shader.UploadUniformFloat3("u_SpotDirection", light->direction);
            m_Shader.UploadUniformBool("u_isPointLight", light->isPointLight);
            m_Shader.UploadUniformBool("u_isSpotLight", light->isSpotLight && light->isPointLight);
            m_Shader.UploadUniformFloat4("u_LightParams", glm::vec4(light->color, light->strength));
            m_Shader.UploadUniformFloat("u_SpotInnerAngle", glm::cos(glm::radians(light->innerAngle)));
            m_Shader.UploadUniformFloat("u_SpotOuterAngle", glm::cos(glm::radians(light->outerAngle)));
            SetShadowMap();

            auto light = m_LightService->GetLights()[0];
            m_Shader.UploadUniformMat4("u_LightSpaceMatrix", light->GetProjectionMatrix() * light->GetViewMatrix());
        }
    }
}

void Material::SetShadowMap() {
    if (m_Textures.size() == 0) return;
    glUniform1i(glGetUniformLocation(m_Shader.ShaderId(), "shadowMap"), m_Textures.size());

    auto light = m_LightService->GetLights()[0];
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, light->depthMapTexture);
}

void Material::Disable() {
    m_Shader.Unbind();
    for (const auto text : m_Textures) {
        text->Disable();
    }
}

void Material::AddTexture(std::string fileName, std::string typeName) {
    m_Textures.push_back(std::make_shared<Texture>(fileName, m_Shader.ShaderId(), typeName, m_Textures.size()));
}

void Material::UpdateTransform(glm::mat4& view, glm::mat4& proj) {
    m_Shader.UploadUniformMat4("u_Projection", proj);
    m_Shader.UploadUniformMat4("u_View", view);
}

void Material::SetMaterialData(std::shared_ptr<MaterialData> matData) {
    m_Shader.Bind();
    if (!matData->diffuse_texname.empty()) AddTexture(matData->diffuse_texname, "u_DiffuseTexture");
    if (!matData->ambient_texname.empty()) AddTexture(matData->ambient_texname, "u_AmbientTexture");
    if (!matData->ambient_texname.empty()) AddTexture(matData->ambient_texname, "u_SpecularTexture");
    if (!matData->bump_texname.empty()) AddTexture(matData->bump_texname, "u_BumpTexture");
    m_Shader.UploadUniformFloat3("u_DiffuseColour", matData->diffuse);
    m_Shader.UploadUniformFloat4("u_Specular", glm::vec4(matData->specular, matData->shininess));
    m_Shader.UploadUniformFloat("u_MaterialAlpha", matData->dissolve);

    m_Shader.Unbind();
}
