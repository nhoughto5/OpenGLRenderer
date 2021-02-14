#pragma once
#include "util/Transform.h"
#include "Shape.h"
#include "util/MaterialData.h"

class Model
{
public:
    Model();
    Model(std::string name);
    void RenderShadows();
    virtual void Render(glm::mat4 cameraView, glm::mat4 cameraProj);
    void SetMesh(std::string meshName);
    void AddTransform(std::shared_ptr<Transform> t);
    std::vector<glm::mat4> GetModelMatrices();
protected:
    std::vector<std::shared_ptr<Shape>> m_Shapes;
    std::string m_Name;

    std::vector<std::shared_ptr<Transform>> m_Transforms;
    std::vector<glm::mat4> m_TransformMatrices;
private:
    std::shared_ptr<MaterialData> readMaterial(pugi::xml_node node);
    glm::vec3 readVec3(pugi::xml_node node);
    glm::vec3 float3ToGLM(float* realt);
    std::string m_OverrideDiffuse, m_OverrideNormal;
    std::mutex m_Lock;
};

