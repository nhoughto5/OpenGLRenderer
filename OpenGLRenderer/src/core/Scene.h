#pragma once
#include <core\Model.h>
class Scene
{
public:
    void AddModel(Model* m);
    void Activate();
    void Deactivate();
    bool IsActive();
    void Update();
private:
    bool m_Active{ false };
    std::vector<Model*> m_Models;
};

