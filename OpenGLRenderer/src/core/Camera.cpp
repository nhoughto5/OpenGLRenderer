#include "pch.h"
#include "Camera.h"
#include "Application.h"

Camera::Camera() :
    m_CameraPosition(6.0f, 1.50f, 5.0f),
    m_View(1.0),
    m_CameraFront(-0.5f, 0.0f, -1.0f),
    firstMouse(true),
    m_Projection(1.0),
    m_CameraUp(0.0f, 1.0f, 0.0f),
    lastScreenX((float)INIT_WIDTH / 2),
    lastScreenY((float)INIT_HEIGHT / 2),
    m_ScreenWidth(INIT_WIDTH),
    m_ScreenHeight(INIT_HEIGHT),
    m_Dragging(false)
{
    m_AspectRatio = (float)m_ScreenWidth / (float)m_ScreenHeight;
    m_Projection = glm::perspective(glm::radians(45.0f), m_AspectRatio, 0.1f, 200.0f);
}

glm::mat4 Camera::GetViewMatrix() {
    return m_View;
}

glm::mat4 Camera::GetProjectionMatrix() {
    return m_Projection;
}

void Camera::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<KeyPressedEvent>(OGLR_BIND_EVENT_FN(Camera::ProcessKeyEvent));
    dispatcher.Dispatch<MouseMovedEvent>(OGLR_BIND_EVENT_FN(Camera::OnMouseEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(OGLR_BIND_EVENT_FN(Camera::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(OGLR_BIND_EVENT_FN(Camera::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<WindowResizeEvent>(OGLR_BIND_EVENT_FN(Camera::OnWindowResized));
}

void Camera::OnUpdate(TimeStep dt) {
    m_DeltaTime = dt;

    m_View = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
}

bool Camera::ProcessKeyEvent(KeyPressedEvent& e) {
    if (e.GetKeyCode() == GLFW_KEY_A) {
        m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraTranslationSpeed;
    }
    else if (e.GetKeyCode() == GLFW_KEY_D) {
        m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_CameraTranslationSpeed;
    }

    if (e.GetKeyCode() == GLFW_KEY_W) {
        m_CameraPosition += m_CameraTranslationSpeed * m_CameraFront;
    }
    else if (e.GetKeyCode() == GLFW_KEY_S) {

        m_CameraPosition -= m_CameraTranslationSpeed * m_CameraFront;
    }

    if (e.GetKeyCode() == GLFW_KEY_X) {
        m_CameraPosition += m_CameraUp * m_CameraTranslationSpeed;
    }
    else if (e.GetKeyCode() == GLFW_KEY_Z) {
        m_CameraPosition -= m_CameraUp * m_CameraTranslationSpeed;
    }

    if (e.GetKeyCode() == GLFW_KEY_Q) {
        m_Yaw -= m_CameraRotationSpeed;
    }
    else if (e.GetKeyCode() == GLFW_KEY_E) {
        m_Yaw += m_CameraRotationSpeed;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_CameraFront = glm::normalize(direction);

    OGLR_CORE_INFO("Camera Position: {0}, {1}, {2}", m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z);

    return true;
}

bool Camera::OnMouseEvent(MouseMovedEvent& e) {
    if (!m_Dragging)
    {
        return true;
    }

    if (firstMouse) // initially set to true
    {
        lastScreenX = e.GetX();
        lastScreenY = e.GetY();
        firstMouse = false;
    }

    float xoffset = e.GetX() - lastScreenX;
    float yoffset = lastScreenY - e.GetY();
    lastScreenX = e.GetX();
    lastScreenY = e.GetY();

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_Yaw += xoffset;
    m_Pitch += yoffset;

    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_CameraFront = glm::normalize(direction);

    return true;
}

bool Camera::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
    if (e.GetMouseButton() != MOUSE_BUTTON_1)
    {
        return true;
    }

    m_Dragging = false;
    return true;
}

bool Camera::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
    if (e.GetMouseButton() != MOUSE_BUTTON_1)
    {
        return true;
    }
    firstMouse = true;
    m_Dragging = true;

    return true;
}

bool Camera::OnWindowResized(WindowResizeEvent& e) {
    m_ScreenWidth = e.GetWidth();
    m_ScreenHeight = e.GetHeight();
    m_AspectRatio = (float)m_ScreenWidth / (float)m_ScreenHeight;
    m_Projection = glm::perspective(glm::radians(45.0f), m_AspectRatio, 0.1f, 200.0f);
    return true;
}
