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
}

void Material::Disable()
{
    m_Shader.Unbind();
}
