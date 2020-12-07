#pragma once

#include "core\Material.h"

class Model
{
public:
    Model(std::string name);
    void Update(glm::mat4 cameraView, glm::mat4 cameraProj);
    void SetMaterial(std::shared_ptr<Material> mat);
private:
    void UpdateTransform();

    std::shared_ptr<Material> m_Material;
    std::string m_Name;
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;
    unsigned int m_VAO;

    glm::vec3 m_Position, m_Scale;
    glm::mat4 m_Transform;
};

