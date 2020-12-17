#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(glm::vec3 p,int i) {
    pos = p;
    id = i;
}

bool Vertex::operator==(const Vertex& other) const
{
    return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
}