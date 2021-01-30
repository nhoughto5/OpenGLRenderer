#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(glm::vec3 p) {
    pos = p;
}

Vertex::Vertex(float x, float y, float z) {
    pos = glm::vec3(x, y, z);
}

bool Vertex::operator==(const Vertex& other) const {
    return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
}