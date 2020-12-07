#pragma once
#include "IListener.h"

class Camera : public IListener
{
public:
    Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    virtual void OnEvent(Event& e) override;
private:
    glm::mat4 m_View, m_Projection;
};

