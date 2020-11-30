#pragma once
#include "GLFW/glfw3.h"
#include <glad/glad.h>

class Shader {
public:
    Shader(std::string vertPath, std::string fragPath);

    void Bind();
private:
    void Compile();
    uint32_t m_ProgramId;
    std::string m_VertexCode, m_FragmentCode;
};

