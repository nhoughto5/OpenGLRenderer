#pragma once
#include "core/Model.h"

class Grid : public Model {
public:
    Grid(size_t size);

    virtual void Render(glm::mat4 cameraView, glm::mat4 cameraProj) override;
private:
};

