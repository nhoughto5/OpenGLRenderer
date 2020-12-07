#include "pch.h"
#include "Model.h"
#include <tiny_obj_loader.h>
Model::Model(std::string name) :
    m_Name(name),
    m_Position(0.0f),
    m_Scale(1.0f),
    m_Transform(1.0)
{
    const std::string MODEL_PATH = "assets/models/triangle.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) {
        throw std::runtime_error(warn + err);
    }
    std::unordered_map<Vertex, uint32_t> uniqueVertices = {};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex = {};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.normal = {
                attrib.normals[3 * index.normal_index + 0],
                attrib.normals[3 * index.normal_index + 1],
                attrib.normals[3 * index.normal_index + 2]
            };

            if (attrib.texcoords.size() > 0)
            {
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1],
                };
            }

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(m_Vertices.size());
                m_Vertices.push_back(vertex);
            }

            m_Indices.push_back(uniqueVertices[vertex]);
        }
    }

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices[0]) * m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);
}

void Model::Update(glm::mat4 cameraView, glm::mat4 cameraProj)
{
    m_Material->Enable();
    UpdateTransform();
    m_Material->UpdateTransform(cameraProj * cameraView * m_Transform);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_Vertices.size(), GL_UNSIGNED_INT, 0);
    m_Material->Disable();
}


void Model::SetMaterial(std::shared_ptr<Material> mat)
{
    m_Material = mat;
}

void Model::UpdateTransform()
{
    m_Transform = glm::mat4(1.0);
    m_Transform = glm::rotate(m_Transform, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
    //m_Transform = glm::scale(m_Transform, glm::vec3(0.5, 0.5, 0.5));
}
