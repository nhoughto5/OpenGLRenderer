#include "pch.h"
#include "LightService.h"

LightService* LightService::s_Instance = 0;

LightService* LightService::GetInstance() {
    if (!s_Instance) {
        s_Instance = new LightService();
    }
    return s_Instance;
}

AmbientLight LightService::GetAmbientLight() {
    return m_AmbienLight;
}

void LightService::SetAmbientLight(glm::vec3 color, float strength) {
    m_AmbienLight.color = color;
    m_AmbienLight.strength = strength;
}
