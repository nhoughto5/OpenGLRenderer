#pragma once
#include "Material.h"
#include "util/MaterialData.h"

class Shape
{
public:
    Shape();
    Shape(std::vector<Vertex>& v, std::vector<uint32_t>& i, std::string shader, std::string shapeName, std::shared_ptr<MaterialData> matData);
    void SetData(std::vector<Vertex>& v, std::vector<uint32_t>& i, std::string shader);
    void Draw(GLenum mode, glm::mat4& view, glm::mat4& proj);
    void AddInstance(glm::mat4 mat);
private:
    void Upload();
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;
    unsigned int m_VAO;
    size_t m_NumVerts;
    Material m_Material;
    std::string m_Name;
    unsigned int m_ModelMatrixBuffer;
    std::vector<glm::mat4> m_InstanceModelMatrices;
};

