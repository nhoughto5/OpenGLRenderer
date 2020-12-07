#pragma once

#include <pugixml.hpp>
#include "core/Model.h"
#include "core/Camera.h"
#include "Constants.h"

class Scene
{
public:
    Scene() = default;
    Scene(std::string scenePath);
    void AddModel(std::shared_ptr<Model> m);
    void Activate();
    void Deactivate();
    bool IsActive();
    void Update();
private:
    void loadModel(pugi::xml_node modelNode);

    bool m_Active{ false };
    std::vector<std::shared_ptr<Model>> m_Models;
    Camera m_Camera;
};

