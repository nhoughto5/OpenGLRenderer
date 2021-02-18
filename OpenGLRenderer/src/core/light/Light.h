#pragma once
#include "glm/glm.hpp"

struct Light {
    float strength, innerAngle, outerAngle;
    glm::vec3 color, position, attenuation, direction;
    bool isSpotLight = false, isPointLight = false, generatesShadows = false;
    unsigned int depthMapFBO, depthMapTexture, shadowMapWidth = 1024, shadowMapHeight = 1024;

    glm::mat4 GetProjectionMatrix() {
        float near_plane = 1.0f, far_plane = 17.5f;
        return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(position, direction, glm::vec3(0.0f, 1.0f, 0.0f));
    }
};