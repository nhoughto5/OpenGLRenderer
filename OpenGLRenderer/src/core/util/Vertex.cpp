#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(glm::vec3 p) {
    pos = p;
}

bool Vertex::operator==(const Vertex& other) const
{
    return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
}