#include "pch.h"
#include "Camera.h"
#include "Application.h"

Camera::Camera() :
	m_CameraPosition(0.0f, 0.0f, -2.0f),
    m_View(1.0),
    m_Projection(1.0) {
    m_View = glm::translate(m_View, m_CameraPosition);
	auto app = Application::Get();
	
    m_Projection = glm::perspective(glm::radians(45.0f), (float)app.GetWidth() / app.GetHeight(), 0.1f, 100.0f);
	//m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f)
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
}

void Camera::OnUpdate(TimeStep dt) {
	m_DeltaTime = dt;

	//m_View = glm::translate(m_View, m_CameraPosition);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_CameraPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0, 0, 1));

	//m_View = glm::inverse(transform);
	m_View = transform;
	//m_Projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);
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