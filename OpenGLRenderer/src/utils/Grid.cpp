#include "pch.h"
#include "Grid.h"

Grid::Grid(size_t size) {
    m_Material = std::make_shared<Material>();
    m_Material->SetShader("grid.glsl");
    m_Vertices.reserve(size * size);
    uint32_t gridSize = 1.0f;

    for (uint32_t i = 0; i < size; ++i) {
        for (uint32_t j = 0; j < size; ++j) {
            m_Vertices.push_back(Vertex(glm::vec3(gridSize * i, 0, gridSize * j)));
        }
    }

    for (uint32_t i = 0; i < size - 1; ++i) {
        for (uint32_t j = 0; j < size - 1; ++j) {

            m_Indices.push_back((size * i) + j); //0
            m_Indices.push_back((size * i) + j + 1); //1
            m_Indices.push_back((size * i) + j + size + 1); //5
            m_Indices.push_back((size * i) + j); //0
            m_Indices.push_back((size * i) + j + size + 1); //5
            m_Indices.push_back((size * i) + j + size); //4
            //OGLR_CORE_INFO("Triangle: {0}, {1}, {2}    {3}, {4}, {5}", (size * i) + j, (size * i) + j + 1, (size * i) + j + size + 1, (size * i) + j, (size * i) + j + size + 1, (size * i) + j + size);
        }
        //OGLR_CORE_INFO("=====");
    }

    Upload();
}

void Grid::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Model::Render(cameraView, cameraProj);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
