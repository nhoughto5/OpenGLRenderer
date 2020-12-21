#pragma once

#include "core\Material.h"
#include "core/util/Transform.h"
class Model
{
public:
    Model();
    Model(std::string name);
    virtual void Render(glm::mat4 cameraView, glm::mat4 cameraProj);
    void SetMaterial(std::shared_ptr<Material> mat);
    void SetMesh(std::string meshName);
    void SetTransform(std::shared_ptr<Transform> t);
protected:
    std::shared_ptr<Material> m_Material;
    std::string m_Name;
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;

    void Upload();
    void UpdateTransform();

    unsigned int m_VAO;

    std::shared_ptr<Transform> m_Transform;
    glm::mat4 m_TransformMatrix;
    size_t m_NumVerts;
};

