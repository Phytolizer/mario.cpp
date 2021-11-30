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
    m_camera = Camera{glm::vec2{-250, 0}};

    auto obj1 = std::make_unique<GameObject>("Object 1", Transform{glm::vec2{100, 100}, glm::vec2{256, 256}});
    obj1->emplaceComponent(
        std::make_unique<SpriteRenderer>(obj1.get(), std::make_unique<Texture>("res/images/testImage.png")));
    addGameObject(std::move(obj1));

    auto obj2 = std::make_unique<GameObject>("Object 2", Transform{glm::vec2{400, 100}, glm::vec2{256, 256}});
    obj2->emplaceComponent(
        std::make_unique<SpriteRenderer>(obj2.get(), std::make_unique<Texture>("res/images/testImage2.png")));
    addGameObject(std::move(obj2));
}

void LevelEditorScene::update(float dt)
{
    std::cout << (1.0F / dt) << " FPS" << std::endl;
    for (const auto& gameObject : m_gameObjects)
    {
        gameObject->update(dt);
    }

    m_renderer.render();
}
