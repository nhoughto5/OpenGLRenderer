#pragma once
class Texture
{
public:
    Texture(std::string fileName, uint32_t programId, std::string uniformId);

    void Enable();
    void Disable();
private:
    uint32_t m_TextureId, m_TextureUnit;
    std::string m_FileName;
    int m_Width, m_Height, m_NrChannels;
    uint32_t m_ProgramId;
    uint16_t m_UniformId;
};

