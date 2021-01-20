#pragma once
#include "core/Model.h"
#include "core/TextureCube.h"

class Skybox : public Model {
public:
    Skybox(std::string src);
    //void SetTexture(std::string src);
    virtual void Render(glm::mat4 cameraView, glm::mat4 cameraProj) override;
private:
    unsigned int m_VAO;
    size_t m_NumVerts;
    Shader m_Shader;
    TextureCube m_TextureCube;
};

