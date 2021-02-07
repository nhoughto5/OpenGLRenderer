#pragma once
#include "glm/glm.hpp"

struct Light {
    float strength, innerAngle, outerAngle;
    glm::vec3 color, position, attenuation, direction;
    bool isSpotLight = false, isPointLight = false;
    float tempAngle = 0.0f;
};