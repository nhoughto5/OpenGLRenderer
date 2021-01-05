#include "pch.h"
#include "LightService.h"

LightService* LightService::s_Instance = 0;

LightService* LightService::GetInstance() {
    if (!s_Instance) {
        s_Instance = new LightService();
    }
    return s_Instance;
}

Light LightService::GetAmbientLight() {
    return m_AmbienLight;
}

std::vector<std::shared_ptr<Light>>& LightService::GetLights() {
    return m_Lights;
}

void LightService::SetAmbientLight(glm::vec3 color, float strength) {
    m_AmbienLight.color = color;
    m_AmbienLight.strength = strength;
}

void LightService::AddLight(std::shared_ptr<Light> light) {
    m_Lights.push_back(light);
}
