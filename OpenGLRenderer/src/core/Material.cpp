#include "pch.h"
#include "Material.h"

Material::Material()
{

}

void Material::SetShader(std::string fileName)
{
    m_Shader.SetShaderFileName(fileName);
    m_Shader.Bind();
}
