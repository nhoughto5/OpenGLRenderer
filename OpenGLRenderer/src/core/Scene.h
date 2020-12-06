#pragma once
#include <core\Model.h>
#include <pugixml.hpp>

class Scene
{
public:
    Scene(std::string scenePath);
    void AddModel(Model* m);
    void Activate();
    void Deactivate();
    bool IsActive();
    void Update();
private:
    bool m_Active{ false };
    std::vector<Model*> m_Models;
};

