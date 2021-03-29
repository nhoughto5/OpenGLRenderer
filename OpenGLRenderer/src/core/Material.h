#pragma once
#include "core/Shader.h"
#include "core/Texture.h"
#include "core/light/LightService.h"
#include "util/MaterialData.h"

class Material
{
public:
    Material();
    void SetShader(std::string fileName);
    void Enable();
    void Disable();
    void UpdateTransform(glm::mat4& view, glm::mat4& proj);
    void UploadUniforms();
    void SetMaterialData(std::shared_ptr<MaterialData> matData);
    void SetShadowMap();
    std::vector<std::shared_ptr<Texture>> Textures() { return m_Textures; }
private:
    void AddTexture(std::string src, std::string typeName);

    Shader m_Shader;
    std::vector<std::shared_ptr<Texture>> m_Textures;
    LightService* m_LightService;
};

