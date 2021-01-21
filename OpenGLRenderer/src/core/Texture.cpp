#include "pch.h"
#include "Texture.h"

Texture::Texture(std::string fileName, uint32_t programId, std::string uniformId, uint16_t unitId)
{
    m_FileName = ASSET_FOLDER + fileName;
    unsigned char* texData = ImageLoader::loadImage(m_FileName.c_str(), &m_Width, &m_Height, &m_NrChannels);

    m_ProgramId = programId;
    
    glUniform1i(glGetUniformLocation(programId, uniformId.c_str()), unitId);
    glGenTextures(1, &m_TextureId);

    m_TextureUnit = GL_TEXTURE0 + unitId;
    glActiveTexture(m_TextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    if (texData)
    {
        glUniform1i(glGetUniformLocation(programId, (uniformId + UNIFORM_TEXTURE_VALID).c_str()), true);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
        OGLR_CORE_INFO("Loaded Texture: {0}", m_FileName);
    }
    else
    {
        OGLR_CORE_ERROR("Failed to load texture");
        throw std::runtime_error("Failed to load texture: "+ m_FileName);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    ImageLoader::Clear(texData);
    Disable();
}

void Texture::Enable()
{
    glActiveTexture(m_TextureUnit); 
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void Texture::Disable()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
