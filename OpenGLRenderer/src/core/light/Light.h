#pragma once
#include "glm/glm.hpp"
#include "core/Model.h"

class Light {
public:
    Light();
    float strength;
    glm::vec3 color;
    void SetPosition(glm::vec3 pos);
    glm::vec3 GetPosition() { return m_Position; }
private:
    //std::shared_ptr<Model> m_LightModel;
    glm::vec3 m_Position;
};