#include "pch.h"
#include "Shape.h"

Shape::Shape(): m_NumVerts(0), m_VAO(-1) {
}

void Shape::SetData(std::vector<Vertex>& v, std::vector<uint32_t>& i, std::string shader) {
    m_Material.SetShader(shader.c_str());
    m_Vertices = v;
    m_Indices = i;
    m_NumVerts = m_Indices.size();

    Upload();
}

void Shape::SetMaterial(std::shared_ptr<MaterialData> data)
{
    if (data != nullptr) {
        m_Material.SetMaterialData(data);
    }
}

void Shape::Draw(GLenum mode, glm::mat4& view, glm::mat4& proj) {
    glBindVertexArray(m_VAO);
    m_Material.Enable();
    m_Material.UpdateTransform(view, proj);
    glDrawElementsInstanced(mode, m_NumVerts, GL_UNSIGNED_INT, 0, m_InstanceModelMatrices.size());
    m_Material.Disable();
    glBindVertexArray(0);
}

void Shape::DrawShadow(GLenum mode, glm::mat4& view, glm::mat4& proj)
{
    glBindVertexArray(m_VAO);
    glDrawElementsInstanced(mode, m_NumVerts, GL_UNSIGNED_INT, 0, m_InstanceModelMatrices.size());
    glBindVertexArray(0);
}

void Shape::AddInstance(glm::mat4 mat)
{
    glBindVertexArray(m_VAO);
    m_InstanceModelMatrices.push_back(mat);
    glBindBuffer(GL_ARRAY_BUFFER, m_ModelMatrixBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_InstanceModelMatrices.size() * sizeof(glm::mat4), m_InstanceModelMatrices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Shape::Upload() {
    glGenBuffers(1, &m_ModelMatrixBuffer);
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

    glBindBuffer(GL_ARRAY_BUFFER, m_ModelMatrixBuffer);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);
}
