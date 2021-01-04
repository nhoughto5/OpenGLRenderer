#pragma once
#include "core/light/Light.h"

class LightService {
public:
    static LightService* GetInstance();

    Light GetAmbientLight();
    void SetAmbientLight(glm::vec3 color, float strength);
    void AddLight(std::shared_ptr<Light> light);
private:
    static LightService* s_Instance;
    Light m_AmbienLight;
    std::vector<std::shared_ptr<Light>> m_Lights;
};

