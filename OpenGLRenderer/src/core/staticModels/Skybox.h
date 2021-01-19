#pragma once
#include "core/Model.h"
class Skybox : public Model {
public:
    Skybox();
    virtual void Render(glm::mat4 cameraView, glm::mat4 cameraProj) override;
private:
    Shape m_Shape;
};

