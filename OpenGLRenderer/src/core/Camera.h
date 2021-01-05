#pragma once
#include "IListener.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "core/Core.h"

class Camera : public IListener
{
public:
    Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    virtual void OnEvent(Event& e) override;
    virtual void OnUpdate(TimeStep ts) override;
    bool ProcessKeyEvent(KeyPressedEvent& e);
    bool OnMouseEvent(MouseMovedEvent& e);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool OnWindowResized(WindowResizeEvent& e);
private:
    glm::mat4 m_View, m_Projection;
    glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f }, m_CameraUp;
    float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
    float m_CameraTranslationSpeed = 0.20f, m_CameraRotationSpeed = 2.0f;
    TimeStep m_DeltaTime;
    glm::vec3 m_CameraFront;
    bool firstMouse;
    float m_AspectRatio;
    float m_ZoomLevel = 1.0f;
    float m_ScreenWidth, m_ScreenHeight;
    float lastScreenX = 0.0f, lastScreenY = 0.0f, m_Pitch = 0.0f, m_Yaw = -90.0f;
    bool m_Dragging;
};

