#pragma once
#include "core/TextureCube.h"
#include "core/util/Transform.h"
#include "core/Shader.h"

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

