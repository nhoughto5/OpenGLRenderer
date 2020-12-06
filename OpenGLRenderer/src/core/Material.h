#pragma once
#include "core/Shader.h"
#include "core/Texture.h"

class Material
{
public:
    Material();
    void SetShader(std::string fileName);
    void Enable();
    void Disable();
    void AddTexture(std::string src);
private:
    Shader m_Shader;
    std::vector<std::shared_ptr<Texture>> m_Textures;
};

