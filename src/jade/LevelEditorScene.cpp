#include "jade/LevelEditorScene.hpp"
#include "fmt/core.h"
#include "jade/Camera.hpp"
#include "jade/KeyListener.hpp"
#include "jade/Window.hpp"
#include "renderer/Shader.hpp"
#include <components/FontRenderer.hpp>
#include <components/SpriteRenderer.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

LevelEditorScene::LevelEditorScene()
{
}

void LevelEditorScene::init()
{
    size_t xOffset = 10;
    size_t yOffset = 10;

    float totalWidth = (float)(600 - xOffset * 2);
    float totalHeight = (float)(300 - yOffset * 2);
    float sizeX = totalWidth / 100.0F;
    float sizeY = totalHeight / 100.0F;

    for (size_t x = 0; x < 100; ++x)
    {
        for (size_t y = 0; y < 100; ++y)
        {
            float xPos = (float)x * sizeX + xOffset;
            float yPos = (float)y * sizeY + yOffset;

            auto go = std::make_unique<GameObject>(fmt::format("Obj{}{}", x, y),
                                                   Transform{glm::vec2{xPos, yPos}, glm::vec2{sizeX, sizeY}});
            go->emplaceComponent(std::make_unique<SpriteRenderer>(
                go.get(), glm::vec4{xPos / totalWidth, yPos / totalHeight, 1.0F, 1.0F}));
            addGameObject(std::move(go));
        }
    }
}

void LevelEditorScene::update(float dt)
{
    std::cout << (1.0F / dt) << " FPS" << std::endl;
    for (auto& gameObject : m_gameObjects)
    {
        gameObject->update(dt);
    }

    m_renderer.render();
}
