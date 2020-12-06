#include "pch.h"
#include "Vertex.h"

bool Vertex::operator==(const Vertex& other) const
{
    return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
}