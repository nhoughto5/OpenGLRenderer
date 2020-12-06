#pragma once
#include "core/Shader.h"

class Material
{
public:
    Material();
    void SetShader(std::string fileName);
    void Enable();
    void Disable();
private:
    Shader m_Shader;
};

