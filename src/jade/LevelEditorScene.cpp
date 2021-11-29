#include "jade/LevelEditorScene.hpp"
#include "jade/KeyListener.hpp"
#include "jade/Window.hpp"
#include "renderer/Shader.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

LevelEditorScene::LevelEditorScene() : m_defaultShader("res/shaders/default.glsl")
{
}

void LevelEditorScene::init()
{
    // Compile and link shaders
    m_defaultShader.compile();

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
    m_defaultShader.use();

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
    m_defaultShader.detach();
}
