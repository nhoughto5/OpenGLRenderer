#pragma once
#include "core/Model.h"
#include "core/TextureCube.h"

class Skybox {
public:
    Skybox(std::string src);
    void Render(glm::mat4 cameraView, glm::mat4 cameraProj);
    void SetTransform(std::shared_ptr<Transform> t);
private:
    unsigned int m_VAO;
    size_t m_NumVerts;
    Shader m_Shader;
    TextureCube m_TextureCube;
};

