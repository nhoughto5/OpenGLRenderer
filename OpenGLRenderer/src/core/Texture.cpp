#include "pch.h"
#include "Texture.h"
#include <stb_image.h>

Texture::Texture(std::string fileName, uint32_t textureUnit)
{
    m_FileName = ASSET_FOLDER + fileName;
    m_TextureUnit = GL_TEXTURE0 + textureUnit;
    unsigned char* texData = stbi_load(m_FileName.c_str(), &m_Width, &m_Height, &m_NrChannels, 0);

    glActiveTexture(m_TextureUnit);
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (texData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        OGLR_CORE_ERROR("Failed to load texture");
        throw std::runtime_error("Failed to load texture: "+ m_FileName);
    }

    stbi_image_free(texData);
}

void Texture::Enable()
{
    glActiveTexture(m_TextureUnit); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

void Texture::Disable()
{
    glActiveTexture(m_TextureUnit); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, 0);
}
