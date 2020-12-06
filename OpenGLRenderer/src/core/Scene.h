#pragma once
#include <core\Model.h>
#include <pugixml.hpp>
#include "Constants.h"

class Scene
{
public:
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
};

