#include "pch.h"
#include "Grid.h"

Grid::Grid(size_t size) {
    std::vector<Vertex> verts;
    std::vector<uint32_t> indices;
    size_t numVert = size + 1;
    float gridSize = 0.50f;
    int id = 0;
    float shift = (gridSize * size) / 2;
    for (uint32_t i = 0; i < numVert; ++i) {
        std::string str;
        for (uint32_t j = 0; j < numVert; ++j) {
            Vertex m = Vertex(glm::vec3((gridSize * i) - shift, 0, shift - (gridSize * j)), id);
            verts.push_back(m);
            id++;
        }
    }

    for (uint32_t i = 0; i < numVert - 1; ++i) {
        for (uint32_t j = 0; j < numVert - 1; ++j) {
            indices.push_back((numVert * i) + j); //0
            indices.push_back((numVert * i) + j + 1); //1
            indices.push_back((numVert * i) + j + numVert + 1); //4
            indices.push_back((numVert * i) + j + numVert); //3
        }
    }

    m_Shape.SetData(verts, indices, "grid.glsl");
}

void Grid::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    UpdateTransform();
    m_Shape.Draw(GL_QUADS, m_TransformMatrix, cameraView, cameraProj);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
