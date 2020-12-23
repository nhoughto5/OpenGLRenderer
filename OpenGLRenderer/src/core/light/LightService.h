#pragma once
#include "core/light/AmbientLight.h"

class LightService {
public:
    static LightService* GetInstance();

    AmbientLight GetAmbientLight();
    void SetAmbientLight(glm::vec3 color, float strength);
private:
    static LightService* s_Instance;
    AmbientLight m_AmbienLight;
};

