#pragma once
#include "core/light/Light.h"
#include "core/Shader.h"

class LightService {
public:
    static LightService* GetInstance();

    Light GetAmbientLight();
    std::vector<std::shared_ptr<Light>>& GetLights();
    void SetAmbientLight(glm::vec3 color, float strength);
    void AddLight(std::shared_ptr<Light> light);
    void CreateShadowmaps();
    void StartShadowRender();
    void EndShadowRender();
private:
    static LightService* s_Instance;
    Light m_AmbienLight;
    std::vector<std::shared_ptr<Light>> m_Lights;
    Shader m_ShadowShader;
};

