#pragma once

#include <pugixml.hpp>
#include "core/Model.h"
#include "core/Camera.h"
#include "Constants.h"
#include "utils/Grid.h"
#include "core/util/Transform.h"

class Scene
{
public:
    Scene() = default;
    Scene(std::string scenePath);
    void loadGrid(pugi::xml_node modelNode);
    void AddModel(std::shared_ptr<Model> m);
    void Activate();
    void Deactivate();
    bool IsActive();
    void Update();
private:
    void loadModel(pugi::xml_node modelNode);
    void loadLight(pugi::xml_node node);
    std::shared_ptr<Transform> ReadTransform(pugi::xml_node transData);
    std::shared_ptr<Material> ReadMaterial(pugi::xml_node matData);
    glm::vec3 ReadVector(pugi::xml_node matData);
    bool m_Active{ false };
    std::vector<std::shared_ptr<Model>> m_Models;
    Camera m_Camera;
    bool m_Loaded{false};
};

