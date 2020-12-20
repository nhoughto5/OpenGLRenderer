#include "pch.h"
#include "Grid.h"

Grid::Grid(size_t size) {
    size_t numVert = size + 1;
    m_Material = std::make_shared<Material>();
    m_Material->SetShader("grid.glsl");
    float gridSize = 1.0f;
    int id = 0;
    for (uint32_t i = 0; i < numVert; ++i) {
        std::string str;
        for (uint32_t j = 0; j < numVert; ++j) {
            Vertex m = Vertex(glm::vec3(gridSize * i, 0, -gridSize * j), id);
            m_Vertices.push_back(m);
            str += std::to_string(id) + ": " + " " + std::to_string(m.pos.x) + "," + std::to_string(m.pos.z) + "  ";
            id++;
        }
        OGLR_CORE_INFO(str);
    }

    for (uint32_t i = 0; i < numVert - 1; ++i) {
        for (uint32_t j = 0; j < numVert - 1; ++j) {
            m_Indices.push_back((numVert * i) + j); //0
            m_Indices.push_back((numVert * i) + j + 1); //1
            m_Indices.push_back((numVert * i) + j + numVert + 1); //4
            m_Indices.push_back((numVert * i) + j + numVert); //3
            OGLR_CORE_INFO("Quad: {0}, {1}, {2}, {3}", (numVert * i) + j, (numVert * i) + j + 1, (numVert * i) + j + numVert + 1, (numVert * i) + j + numVert);
        }
    }

    Upload();
}

void Grid::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_Material->Enable();
    UpdateTransform();
    m_Material->UpdateTransform(cameraProj * cameraView * m_Transform);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_QUADS, m_Vertices.size(), GL_UNSIGNED_INT, 0);
    m_Material->Disable();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
