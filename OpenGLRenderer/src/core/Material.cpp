#include "pch.h"
#include "Material.h"

Material::Material()
{

}

void Material::SetShader(std::string fileName)
{
    m_Shader.SetShaderFileName(fileName);
}

void Material::Enable()
{
    m_Shader.Bind();
    for (const auto text : m_Textures)
    {
        text->Enable();
    }
}

void Material::Disable()
{
    m_Shader.Unbind();
    for (const auto text : m_Textures)
    {
        text->Disable();
    }
}

void Material::AddTexture(std::string fileName)
{
    m_Textures.push_back(std::make_shared<Texture>(fileName, m_Textures.size()));
}

void Material::UpdateTransform(glm::mat4 trans)
{
    m_Shader.UploadUniformMat4("uTransform", trans);
}
