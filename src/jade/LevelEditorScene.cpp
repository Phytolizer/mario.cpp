#include "jade/LevelEditorScene.hpp"

#include "jade/Camera.hpp"
#include "jade/Window.hpp"
#include <components/DependentSpriteRenderer.hpp>
#include <components/SpriteSheet.hpp>
#include <fmt/format.h>
#include <iostream>
#include <renderer/Shader.hpp>
#include <vector>

LevelEditorScene::LevelEditorScene() = default;

void LevelEditorScene::init()
{
    m_camera = Camera{glm::vec2{-250, 0}};

    m_spriteSheet =
        std::make_unique<SpriteSheet>(std::make_unique<Texture>("res/images/spritesheet.png"), 16, 16, 26, 0);

    auto obj1 = std::make_unique<GameObject>("Object 1", Transform{glm::vec2{100, 100}, glm::vec2{256, 256}});
    obj1->emplaceComponent(std::make_unique<DependentSpriteRenderer>(obj1.get(), m_spriteSheet->getSprite(0)));
    m_obj1 = obj1.get();
    addGameObject(std::move(obj1));

    auto obj2 = std::make_unique<GameObject>("Object 2", Transform{glm::vec2{400, 100}, glm::vec2{256, 256}});
    obj2->emplaceComponent(std::make_unique<DependentSpriteRenderer>(obj2.get(), m_spriteSheet->getSprite(10)));
    addGameObject(std::move(obj2));
}

void LevelEditorScene::update(float dt)
{
    m_obj1->transform.position.x += dt * 10;
    std::cout << (1.0F / dt) << " FPS" << std::endl;
    for (const auto& gameObject : m_gameObjects)
    {
        gameObject->update(dt);
    }

    m_renderer.render();
}
