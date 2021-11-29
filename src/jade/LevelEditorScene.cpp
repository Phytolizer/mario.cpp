#include "jade/LevelEditorScene.hpp"
#include "jade/KeyListener.hpp"
#include "jade/Window.hpp"
#include "renderer/Shader.hpp"
#include <components/FontRenderer.hpp>
#include <components/SpriteRenderer.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

LevelEditorScene::LevelEditorScene()
    : m_defaultShader("res/shaders/default.glsl"), m_testTexture("res/images/testImage.png"), m_camera(glm::vec2{}),
      m_testObj(std::make_unique<GameObject>("test object")), m_firstTime(true)
{
}

void LevelEditorScene::init()
{
    std::cout << "Creating 'test object'\n";
    m_testObj->addComponent<SpriteRenderer>(ComponentClass::SPRITE_RENDERER);
    m_testObj->addComponent<FontRenderer>(ComponentClass::FONT_RENDERER);
    addGameObject(std::move(m_testObj));
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
    constexpr size_t uvSize = 2;
    constexpr size_t floatSizeBytes = sizeof(float);
    constexpr size_t vertexSizeBytes = (positionsSize + colorSize + uvSize) * floatSizeBytes;
    glVertexAttribPointer(0, positionsSize, GL_FLOAT, GL_FALSE, vertexSizeBytes, nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, colorSize, GL_FLOAT, GL_FALSE, vertexSizeBytes, (void*)(positionsSize * floatSizeBytes));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, uvSize, GL_FLOAT, GL_FALSE, vertexSizeBytes,
                          (void*)((positionsSize + colorSize) * floatSizeBytes));
    glEnableVertexAttribArray(2);
}

void LevelEditorScene::update(float dt)
{
    // Bind shader program
    m_defaultShader.use();
    m_defaultShader.uploadTexture("TEX_SAMPLER", 0);
    glActiveTexture(GL_TEXTURE0);
    m_testTexture.bind();
    m_defaultShader.uploadMat4("uProjection", m_camera.getProjectionMatrix());
    m_defaultShader.uploadMat4("uView", m_camera.getViewMatrix());

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
    m_testTexture.unbind();
    m_defaultShader.detach();

    if (m_firstTime)
    {
        std::cout << "Creating gameObject!\n";
        auto go = std::make_unique<GameObject>("Game Test 2");
        go->addComponent<SpriteRenderer>(ComponentClass::SPRITE_RENDERER);
        addGameObject(std::move(go));
        m_firstTime = false;
    }

    for (auto& gameObject : m_gameObjects)
    {
        gameObject->update(dt);
    }
}
