#pragma once
#include "core/Shader.h"

class Material
{
public:
    Material();
    void SetShader(std::string fileName);
private:
    Shader m_Shader;
};

