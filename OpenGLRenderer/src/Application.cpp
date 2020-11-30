#include "pch.h"
#include "Application.h"
#include "Renderer.h"

void Application::Run() {
	Renderer::Init(1024, 768);
	m_Running = true;
	while (m_Running) {
		Renderer::Update();
	}
}

