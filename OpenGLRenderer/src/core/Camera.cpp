#include "pch.h"
#include "Camera.h"

Camera::Camera():
    m_View(1.0),
    m_Projection(1.0)
{
    m_View = glm::translate(m_View, glm::vec3(0.0f, 0.0f, -2.0f));
    m_Projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
    return m_View;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return m_Projection;
}

