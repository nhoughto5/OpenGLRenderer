#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

class Transform {
public:
    Transform();
    glm::quat GetRotationQuat();
    glm::mat4 GetRotationMatrix();
    glm::vec3 Position, Rotation, Scale;
private:
};