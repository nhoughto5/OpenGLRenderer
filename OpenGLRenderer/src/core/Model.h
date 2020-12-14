#pragma once

#include "core\Material.h"

class Model
{
public:
    Model();
    Model(std::string name);
    virtual void Render(glm::mat4 cameraView, glm::mat4 cameraProj);
    void SetMaterial(std::shared_ptr<Material> mat);
protected:
    std::shared_ptr<Material> m_Material;
    std::string m_Name;
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;

    void Upload();
private:
    void UpdateTransform();

    unsigned int m_VAO;

    glm::vec3 m_Position, m_Scale;
    glm::mat4 m_Transform;
};

