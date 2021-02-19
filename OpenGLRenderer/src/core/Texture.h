#pragma once
class Texture
{
public:
    Texture(std::string fileName, uint32_t programId, std::string uniformId, uint16_t unitId);

    void Enable();
    void Disable();

    GLuint Id() { return m_TextureId; }
private:
    uint32_t m_ProgramId;
    std::string m_FileName;
    int m_Width, m_Height, m_NrChannels;
    GLenum m_TextureUnit{ GL_TEXTURE0 };
    GLuint m_TextureId{ 0 };
};

