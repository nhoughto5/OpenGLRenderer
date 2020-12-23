#pragma once
#include "core/Shader.h"
#include "core/Texture.h"
#include "core/light/LightService.h"

class Material
{
public:
    Material();
    void SetShader(std::string fileName);
    void Enable();
    void Disable();
    void AddTexture(std::string src);
    void UpdateTransform(glm::mat4 trans);
    void UploadUniforms();
private:
    Shader m_Shader;
    std::vector<std::shared_ptr<Texture>> m_Textures;
    LightService* m_LightService;
};

