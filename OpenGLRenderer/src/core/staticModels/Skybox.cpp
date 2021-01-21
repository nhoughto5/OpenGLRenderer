#include "pch.h"
#include "Skybox.h"

Skybox::Skybox(std::string src) :
    m_Shader("skybox.glsl")
{
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    m_Shader.Bind();

    m_TextureCube.loadTexture(src);

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    m_Shader.Unbind();
    glBindVertexArray(0);
}

void Skybox::Render(glm::mat4 cameraView, glm::mat4 cameraProj) {
    glDepthFunc(GL_LEQUAL);
    m_Shader.Bind();
    m_Shader.UploadUniformMat4("u_Projection", cameraProj);
    m_Shader.UploadUniformMat4("u_View", cameraView);
    m_TextureCube.Enable();
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_TextureCube.Disable();
    m_Shader.Unbind();
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

void Skybox::SetTransform(std::shared_ptr<Transform> t) {
    m_Shader.Bind();
    auto transformMatrix = glm::mat4(1.0);
    transformMatrix = glm::translate(transformMatrix, t->Position);
    transformMatrix = glm::scale(transformMatrix * t->GetRotationMatrix(), t->Scale);
    m_Shader.UploadUniformMat4("u_Model", transformMatrix);
    m_Shader.Unbind();
}
