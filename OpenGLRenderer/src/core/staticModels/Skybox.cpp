#include "pch.h"
#include "Skybox.h"

Skybox::Skybox() {

    std::vector<Vertex> skyboxVertices =
    {
        Vertex(-1.0f,  1.0f, -1.0f), // 0
        Vertex(-1.0f, -1.0f, -1.0f), // 1
        Vertex(1.0f, -1.0f, -1.0f), // 2
        Vertex(1.0f,  1.0f, -1.0f), // 3
        Vertex(-1.0f, -1.0f,  1.0f), // 4
        Vertex(-1.0f,  1.0f,  1.0f), // 5
        Vertex(1.0f, -1.0f,  1.0f), // 6
        Vertex(1.0f,  1.0f,  1.0f), // 7
    };

    std::vector<uint32_t> indicies = {
        0,1,2,
        2,3,0,
        4,1,0,
        0,5,4,
        2,6,7,
        7,3,2,
        4,5,7,
        7,6,4,
        0,3,7,
        7,5,0,
        1,4,2,
        2,4,6
    };

    m_Shape.SetData(skyboxVertices, indicies, "skybox.glsl");
    m_Shape.AddInstance(glm::mat4(1.0));
}

void Skybox::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
}
