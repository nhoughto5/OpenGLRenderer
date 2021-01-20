#pragma once
class TextureCube {
public:
    void loadTexture(std::string src);
    void Enable();
    void Disable();
private:
    GLuint m_TextureId{ 0 };
};

