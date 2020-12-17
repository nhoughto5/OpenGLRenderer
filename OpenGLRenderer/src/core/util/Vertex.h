#pragma once
#include "glm/glm.hpp"

class Vertex {
public:
    Vertex() = default;
    Vertex(glm::vec3 p, int i);
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;
    int id;

    bool operator==(const Vertex& other) const;
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}
