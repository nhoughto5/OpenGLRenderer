#pragma once

#include "core\Material.h"

class Model
{
public:
    Model(std::string name);
    void Update();
    void SetMaterial(std::shared_ptr<Material> mat);
private:
    std::shared_ptr<Material> m_Material;
    std::string m_Name;
};

