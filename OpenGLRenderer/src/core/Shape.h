#pragma once
#include "Material.h"

class Shape
{
public:
    Shape();
    Shape(std::vector<Vertex>& v, std::vector<uint32_t>& i, std::string shader);
    void SetData(std::vector<Vertex>& v, std::vector<uint32_t>& i, std::string shader);
    //void SetShader(std::string fileName);
    void Draw(GLenum mode, glm::mat4& model, glm::mat4& view, glm::mat4& proj);
private:
    void Upload();
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;
    unsigned int m_VAO;
    size_t m_NumVerts;
    Material m_Material;
};

