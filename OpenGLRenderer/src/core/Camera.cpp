#include "pch.h"
#include "Camera.h"
#include "Application.h"

Camera::Camera() :
	m_CameraPosition(0.0f, 0.0f, 2.0f),
    m_View(1.0),
    m_CameraFront(0.0, 0.0, -1.0),
    firstMouse(true),
    m_Projection(1.0) {
    //m_CameraFront = glm::normalize(m_CameraPosition - glm::vec3(0,0,0));
	m_Projection = glm::perspective(glm::radians(45.0f), (float)INIT_WIDTH / INIT_HEIGHT, 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewMatrix() {
    return m_View;
}

glm::mat4 Camera::GetProjectionMatrix() {
    return m_Projection;
}

void Camera::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<KeyPressedEvent>(NEATO_BIND_EVENT_FN(Camera::ProcessKeyEvent));
    //dispatcher.Dispatch<MouseMovedEvent>(NEATO_BIND_EVENT_FN(Camera::OnMouseEvent));
}

void Camera::OnUpdate(TimeStep dt) {
	m_DeltaTime = dt;

    //m_CameraFront = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_View = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, cameraUp);

    //OGLR_CORE_INFO("Pos: {0}, {1}, {2}   LookAt: {3}, {4}, {5}", m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z, m_CameraFront.x, m_CameraFront.y, m_CameraFront.z);
}

bool Camera::ProcessKeyEvent(KeyPressedEvent& e) {
	if (e.GetKeyCode() == GLFW_KEY_A) {
		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * m_DeltaTime;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * m_DeltaTime;
	}
	else if (e.GetKeyCode() == GLFW_KEY_D) {
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * m_DeltaTime;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * m_DeltaTime;
	}

	if (e.GetKeyCode() == GLFW_KEY_W) {
		m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * m_DeltaTime;
		m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * m_DeltaTime;
	}
	else if (e.GetKeyCode() == GLFW_KEY_S) {
		m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * m_DeltaTime;
		m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * m_DeltaTime;
	}

	return true;
}

bool Camera::OnMouseEvent(MouseMovedEvent& e) {
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

    float sensitivity = 0.01f;
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
    
	return false;
}
