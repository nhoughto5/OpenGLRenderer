#include "pch.h"
#include "Skybox.h"

Skybox::Skybox(std::string src) :
    m_Shader("skybox.glsl")
{
    std::vector<Vertex> skyboxVertices =
    {
        Vertex(-1.0f,  1.0f, -1.0f), // 0
        Vertex(-1.0f, -1.0f, -1.0f), // 1
        Vertex(1.0f, -1.0f, -1.0f), // 2
        Vertex(1.0f,  1.0f, -1.0f), // 3
        Vertex(-1.0f, -1.0f,  1.0f), // 4
        Vertex(-1.0f,  1.0f,  1.0f), // 5
        Vertex(1.0f, -1.0f,  1.0f), // 6
        Vertex(1.0f,  1.0f,  1.0f), // 7
    };

    std::vector<uint32_t> indicies = {
        0,1,2,
        2,3,0,
        4,1,0,
        0,5,4,
        2,6,7,
        7,3,2,
        4,5,7,
        7,6,4,
        0,3,7,
        7,5,0,
        1,4,2,
        2,4,6
    };

    m_NumVerts = skyboxVertices.size();
    m_Shader.Bind();

    m_TextureCube.loadTexture(src);

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * skyboxVertices.size(), skyboxVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies[0]) * indicies.size(), indicies.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    m_Shader.Unbind();
}

void Skybox::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    glDepthMask(GL_FALSE);
    m_Shader.Bind();
    m_Shader.UploadUniformMat4("u_Projection", cameraProj);
    m_Shader.UploadUniformMat4("u_View", cameraView);
    m_TextureCube.Enable();
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_NumVerts, GL_UNSIGNED_INT, 0);
    m_TextureCube.Disable();
    m_Shader.Unbind();
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}
