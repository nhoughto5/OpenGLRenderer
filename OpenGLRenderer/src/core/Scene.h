#pragma once
#include "core/Model.h"
#include "core/Camera.h"
#include "Constants.h"
#include "core/staticModels/Grid.h"
#include "core/light/Light.h"
#include "core/util/Transform.h"
#include "core/light/LightService.h"
#include "core/staticModels/Skybox.h"

class Scene
{
public:
    Scene() = default;
    Scene(std::string scenePath);
    void loadGrid(pugi::xml_node modelNode);
    void AddModel(std::string modelName, std::shared_ptr<Model> m);
    void Activate();
    void Deactivate();
    bool IsActive();
    void Update();
private:
    void loadModel(pugi::xml_node modelNode);
    void loadLight(pugi::xml_node node);
    std::shared_ptr<Transform> ReadTransform(pugi::xml_node transData);
    glm::vec3 ReadVector(pugi::xml_node matData);
    std::string ReadAttributeByName(pugi::xml_node node, std::string attrName);
    bool m_Active{ false };
    //std::vector<std::shared_ptr<Model>> m_Models;
    std::unordered_map<std::string, std::shared_ptr<Model>> m_Models;
    Camera m_Camera;
    LightService* m_LightService;
    bool m_Loaded{false};
    std::shared_ptr<Skybox> m_Skybox;

    // Debug
    GLuint d_VAO, d_VBO;
    Shader d_Shader;
    void setupDebugTexture();
    void renderDebugTexture();
    std::shared_ptr<Texture> d_Texture;
};

