#include "pch.h"
#include "Transform.h"

Transform::Transform() :
    Position(0.0),
    Rotation(0.0),
    Scale(1.0)
{

}

glm::quat Transform::GetRotationQuat() {
    return glm::quat(glm::vec3(glm::radians(Rotation.x), glm::radians(Rotation.y), glm::radians(Rotation.z)));
}

glm::mat4 Transform::GetRotationMatrix() {
    return glm::toMat4(GetRotationQuat());
}
