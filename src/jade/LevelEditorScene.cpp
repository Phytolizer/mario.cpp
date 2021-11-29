#include "jade/LevelEditorScene.hpp"
#include "jade/KeyListener.hpp"
#include "jade/Window.hpp"
#include "renderer/Shader.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

LevelEditorScene::LevelEditorScene()
{
    Shader testShader{"res/shaders/default.glsl"};
}

void LevelEditorScene::init()
{
    // Compile and link shaders

    // Load and compile the vertex shader
    m_vertexId = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = m_vertexShaderSource.c_str();
    glShaderSource(m_vertexId, 1, &vertexShaderSource, nullptr);
    glCompileShader(m_vertexId);
    // Check for errors in compilation
    int success;
    glGetShaderiv(m_vertexId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int infoLogLength;
        glGetShaderiv(m_vertexId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(m_vertexId, infoLogLength, nullptr, infoLog.data());
        std::string infoLogString(infoLog.begin(), infoLog.end());
        std::cerr << "ERROR: 'defaultShader.glsl'\n\nVertex shader compilation failed.\n";
        std::cerr << infoLogString << std::endl;
        throw std::runtime_error{"Failed to compile the vertex shader"};
    }

    // Load and compile the fragment shader
    m_fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = m_fragmentShaderSource.c_str();
    glShaderSource(m_fragmentId, 1, &fragmentShaderSource, nullptr);
    glCompileShader(m_fragmentId);
    // Check for errors in compilation
    glGetShaderiv(m_fragmentId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int infoLogLength;
        glGetShaderiv(m_fragmentId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(m_fragmentId, infoLogLength, nullptr, infoLog.data());
        std::string infoLogString(infoLog.begin(), infoLog.end());
        std::cerr << "ERROR: 'defaultShader.glsl'\n\nFragment shader compilation failed.\n";
        std::cerr << infoLogString << std::endl;
        throw std::runtime_error{"Failed to compile the fragment shader"};
    }

    // Link shaders
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexId);
    glAttachShader(m_shaderProgram, m_fragmentId);
    glLinkProgram(m_shaderProgram);

    // Check for errors in linking
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        int infoLogLength;
        glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetProgramInfoLog(m_shaderProgram, infoLogLength, nullptr, infoLog.data());
        std::string infoLogString(infoLog.begin(), infoLog.end());
        std::cerr << "ERROR: 'defaultShader.glsl'\n\nLinking shaders failed.\n";
        std::cerr << infoLogString << std::endl;
        throw std::runtime_error{"Failed to link the shaders"};
    }

    // Clean up shaders
    glDeleteShader(m_vertexId);
    glDeleteShader(m_fragmentId);

    // Generate VAO, VBO, EBO, send to GPU

    // Create float buffer of vertices
    glGenVertexArrays(1, &m_vaoId);
    glBindVertexArray(m_vaoId);

    // Create VBO
    glGenBuffers(1, &m_vboId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
    glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(float), vertexArray.data(), GL_STATIC_DRAW);

    // Create indices
    glGenBuffers(1, &m_eboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementArray.size() * sizeof(int), elementArray.data(), GL_STATIC_DRAW);

    // Add vertex attribute pointers
    constexpr size_t positionsSize = 3;
    constexpr size_t colorSize = 4;
    constexpr size_t floatSizeBytes = sizeof(float);
    constexpr size_t vertexSizeBytes = (positionsSize + colorSize) * floatSizeBytes;
    glVertexAttribPointer(0, positionsSize, GL_FLOAT, GL_FALSE, vertexSizeBytes, nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, colorSize, GL_FLOAT, GL_FALSE, vertexSizeBytes, (void*)(positionsSize * floatSizeBytes));
    glEnableVertexAttribArray(1);
}

void LevelEditorScene::update(float dt)
{
    // Bind shader program
    glUseProgram(m_shaderProgram);

    // Bind VAO
    glBindVertexArray(m_vaoId);

    // Enable vertex attribute pointers
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Draw
    glDrawElements(GL_TRIANGLES, elementArray.size(), GL_UNSIGNED_INT, nullptr);

    // Unbind everything
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
    glUseProgram(0);
}
