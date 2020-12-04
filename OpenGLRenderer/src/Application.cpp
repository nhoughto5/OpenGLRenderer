#include "pch.h"
#include "Application.h"
#include "core/Renderer.h"

void Application::Run() {
	Log::Init();
	Renderer::Init(1024, 768);
	m_Running = true;
	while (m_Running) {
		Renderer::Update();
	}
}

