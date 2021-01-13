#include "pch.h"
#include "Light.h"

Light::Light() {
    //m_LightModel = std::make_shared<Model>("light/light.obj");
}

void Light::SetPosition(glm::vec3 pos) {
    std::shared_ptr<Transform> transform(new Transform());
    transform->Position = pos;
    transform->Scale = glm::vec3(0.1, 0.1, 0.1);
    //m_LightModel->SetTransform(transform);
}
