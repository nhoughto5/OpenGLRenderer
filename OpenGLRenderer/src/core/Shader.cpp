#include "pch.h"
#include "Shader.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath) 
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        m_VertexCode = vShaderStream.str();
        m_FragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    Compile();
}

void Shader::Bind() {
    glUseProgram(m_ProgramId);
}

void Shader::Compile() {
    const char* vShaderCode = m_VertexCode.c_str();
    const char* fShaderCode = m_FragmentCode.c_str();
    uint32_t vertShaderId, fragShaderId;
    int success;
    char infoLog[512];

    vertShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShaderId, 1, &vShaderCode, NULL);
    glCompileShader(vertShaderId);
    glGetShaderiv(vertShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderId, 1, &fShaderCode, NULL);
    glCompileShader(fragShaderId);
    if (!success) {
        glGetShaderInfoLog(fragShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    m_ProgramId = glCreateProgram();
    glAttachShader(m_ProgramId, vertShaderId);
    glAttachShader(m_ProgramId, fragShaderId);
    glLinkProgram(m_ProgramId);

    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ProgramId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertShaderId);
    glDeleteShader(fragShaderId);
}
