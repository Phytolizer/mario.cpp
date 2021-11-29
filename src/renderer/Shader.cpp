#include "renderer/Shader.hpp"
#include "fmt/core.h"
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <util/Regex.hpp>

Shader::Shader(std::string_view filePath) : m_filePath(filePath)
{
    std::ifstream shaderFile{std::string{filePath.begin(), filePath.end()}};
    if (!shaderFile)
    {
        throw std::runtime_error{fmt::format("Error: Could not open file for shader: '{}'", filePath)};
    }
    std::string source{std::istreambuf_iterator<char>{shaderFile}, std::istreambuf_iterator<char>{}};
    Regex typeRegex{R"(#type\s+(vertex|fragment))"};
    std::vector<RegexMatchData> matches = typeRegex.findAll(source);
    std::cout << "=============== MATCHES ================" << std::endl;
    for (size_t i = 0; i < matches.size(); i++)
    {
        auto& match = matches[i];
        std::cout << "========================================" << std::endl;
        std::cout << match.get(1).getStart() << std::endl;
        std::cout << match.get(1).getEnd() << std::endl;
        std::cout << match.get(1).getText() << std::endl;
        auto slice = [&]() {
            PCRE2_SIZE start = match.get(1).getEnd();
            PCRE2_SIZE end;
            if (i < matches.size() - 1)
            {
                end = matches[i + 1].get(0).getStart();
            }
            else
            {
                end = source.size();
            }
            return std::string{source.begin() + start, source.begin() + end};
        };
        if (match.get(1).getText() == "vertex")
        {
            m_vertexSource = slice();
        }
        else if (match.get(1).getText() == "fragment")
        {
            m_fragmentSource = slice();
        }
        else
        {
            std::string message = fmt::format("Error: Unknown shader type '{}'", match.get(1).getText());
            throw std::runtime_error{message};
        }
    }

    std::cout << "=============== VERTEX ================" << std::endl;
    std::cout << m_vertexSource << std::endl;
    std::cout << "=============== FRAGMENT ================" << std::endl;
    std::cout << m_fragmentSource << std::endl;
}

void Shader::compile()
{
    // Load and compile the vertex shader
    int vertexId = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = m_vertexSource.c_str();
    glShaderSource(vertexId, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexId);
    // Check for errors in compilation
    int success;
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int infoLogLength;
        glGetShaderiv(vertexId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(vertexId, infoLogLength, nullptr, infoLog.data());
        std::string infoLogString(infoLog.begin(), infoLog.end());
        std::cerr << "ERROR: '" << m_filePath << "'\n\nVertex shader compilation failed.\n";
        std::cerr << infoLogString << std::endl;
        throw std::runtime_error{"Failed to compile the vertex shader"};
    }

    // Load and compile the fragment shader
    int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = m_fragmentSource.c_str();
    glShaderSource(fragmentId, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentId);
    // Check for errors in compilation
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int infoLogLength;
        glGetShaderiv(fragmentId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(fragmentId, infoLogLength, nullptr, infoLog.data());
        std::string infoLogString(infoLog.begin(), infoLog.end());
        std::cerr << "ERROR: '" << m_filePath << "'\n\nFragment shader compilation failed.\n";
        std::cerr << infoLogString << std::endl;
        throw std::runtime_error{"Failed to compile the fragment shader"};
    }

    // Link shaders
    m_shaderProgramId = glCreateProgram();
    glAttachShader(m_shaderProgramId, vertexId);
    glAttachShader(m_shaderProgramId, fragmentId);
    glLinkProgram(m_shaderProgramId);

    // Check for errors in linking
    glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        int infoLogLength;
        glGetProgramiv(m_shaderProgramId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetProgramInfoLog(m_shaderProgramId, infoLogLength, nullptr, infoLog.data());
        std::string infoLogString(infoLog.begin(), infoLog.end());
        std::cerr << "ERROR: '" << m_filePath << "'\n\nLinking shaders failed.\n";
        std::cerr << infoLogString << std::endl;
        throw std::runtime_error{"Failed to link the shaders"};
    }

    // Clean up shaders
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

void Shader::use()
{
    glUseProgram(m_shaderProgramId);
}

void Shader::detach()
{
    glUseProgram(0);
}

void Shader::uploadMat4(std::string_view uniformName, glm::mat4 matrix)
{
    int uniformLocation = glGetUniformLocation(m_shaderProgramId, uniformName.data());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}
