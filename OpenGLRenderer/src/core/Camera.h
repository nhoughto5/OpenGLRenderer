#pragma once
class Camera
{
public:
    Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
private:
    glm::mat4 m_View, m_Projection;
};

