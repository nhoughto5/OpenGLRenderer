#include "pch.h"
#include "Model.h"
#include <tiny_obj_loader.h>

Model::Model() :
    m_TransformMatrix(1.0) {
    m_Transform = std::make_shared<Transform>();
}

Model::Model(std::string name) :
    m_Name(name),
    m_TransformMatrix(1.0) {
    m_Transform = std::make_shared<Transform>();
}

void Model::SetMesh(std::string meshName) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, (MODEL_FOLDER + meshName).c_str(), MATERIAL_FOLDER.c_str())) {
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

            if (index.normal_index > 0) {
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            }

            if (attrib.texcoords.size() > 0 && index.texcoord_index >= 0) {
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1],
                };
            }

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(m_Vertices.size());
                m_Vertices.push_back(vertex);
            }

            m_Indices.push_back(uniqueVertices[vertex]);
        }
    }

    m_NumVerts = m_Indices.size();

    Upload();
    m_Indices.clear();
    m_Vertices.clear();
}

void Model::SetTransform(std::shared_ptr<Transform> t) {
    m_Transform = t;
}

void Model::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    m_Material->Enable();
    UpdateTransform();
    m_Material->UpdateTransform(cameraProj * cameraView * m_TransformMatrix);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_NumVerts, GL_UNSIGNED_INT, 0);
    m_Material->Disable();
}


void Model::SetMaterial(std::shared_ptr<Material> mat) {
    m_Material = mat;
}

void Model::Upload() {
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

void Model::UpdateTransform() {
    m_TransformMatrix = glm::mat4(1.0);
    m_TransformMatrix = glm::translate(m_TransformMatrix, m_Transform->Position);
    m_TransformMatrix = glm::scale(m_TransformMatrix * m_Transform->GetRotationMatrix(), m_Transform->Scale);
}
