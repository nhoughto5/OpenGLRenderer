#pragma once
#include "util/Transform.h"
#include "Shape.h"
#include "util/MaterialData.h"

class Model
{
public:
    Model();
    Model(std::string name);
    virtual void Render(glm::mat4 cameraView, glm::mat4 cameraProj);
    void SetMesh(std::string meshName, bool hasMTLFile);
    void SetTransform(std::shared_ptr<Transform> t);
    void SetOverrideDiffuse(std::string t);
    void SetOverrideNormal(std::string t);
protected:
    std::vector<std::shared_ptr<Shape>> m_Shapes;
    std::string m_Name;

    void UpdateTransform();

    std::shared_ptr<Transform> m_Transform;
    glm::mat4 m_TransformMatrix;
private:
    glm::vec3 float3ToGLM(float* realt);
    std::string m_OverrideDiffuse, m_OverrideNormal;
};

