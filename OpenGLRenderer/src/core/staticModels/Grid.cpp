#include "pch.h"
#include "Grid.h"

Grid::Grid(size_t size) {
    std::vector<Vertex> verts;
    std::vector<uint32_t> indices;
    size_t numVert = size + 1;
    float gridSize = 1.0f;
    int id = 0;
    float shift = (gridSize * size) / 2;
    for (uint32_t i = 0; i < numVert; ++i) {
        std::string str;
        for (uint32_t j = 0; j < numVert; ++j) {
            Vertex m = Vertex(glm::vec3((gridSize * i) - shift, 0, shift - (gridSize * j)));
            verts.push_back(m);
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
    m_Shape.AddInstance(glm::mat4(1.0));
}

void Grid::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_Shape.Draw(GL_QUADS, cameraView, cameraProj);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
