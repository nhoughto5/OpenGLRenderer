#pragma once
#include "glm/glm.hpp"

struct Light {
    float strength;
    glm::vec3 color, position;
};