#include "pch.h"
#include "Shape.h"


Shape::Shape()
{
}

Shape::Shape(std::vector<Vertex>& v, std::vector<uint32_t>& i, std::string shader = "default.glsl")
{
    SetData(v, i, shader);
}

void Shape::SetData(std::vector<Vertex>& v, std::vector<uint32_t>& i, std::string shader = "default.glsl")
{
    m_Material.SetShader(shader.c_str());
    m_Vertices = v;
    m_Indices = i;
    m_NumVerts = m_Indices.size();

    Upload();
}

void Shape::Draw(GLenum mode, glm::mat4& model, glm::mat4& view, glm::mat4& proj)
{
    m_Material.Enable();
    m_Material.UpdateTransform(model, view, proj);
    glBindVertexArray(m_VAO);
    glDrawElements(mode, m_NumVerts, GL_UNSIGNED_INT, 0);
    m_Material.Disable();
}

void Shape::Upload()
{
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
