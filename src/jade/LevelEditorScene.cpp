#include "jade/LevelEditorScene.hpp"

#include "jade/Window.hpp"
#include "jade/components/IndependentSprite.hpp"
#include "jade/components/IndependentSpriteRenderer.hpp"
#include <iostream>
#include <vector>

LevelEditorScene::LevelEditorScene() = default;

void LevelEditorScene::init()
{
    m_camera = Camera{glm::vec2{-250, 0}};

    m_spriteSheet =
        std::make_unique<SpriteSheet>(std::make_unique<Texture>("res/images/spritesheet.png"), 16, 16, 26, 0);

    auto obj2 = std::make_unique<GameObject>("Object 2", Transform{glm::vec2{400, 100}, glm::vec2{256, 256}}, 1);
    obj2->emplaceComponent(std::make_unique<IndependentSpriteRenderer>(
        obj2.get(), std::make_unique<IndependentSprite>(std::make_unique<Texture>("res/images/blendImage2.png"))));
    addGameObject(std::move(obj2));

    auto obj1 = std::make_unique<GameObject>("Object 1", Transform{glm::vec2{200, 100}, glm::vec2{256, 256}}, 0);
    obj1->emplaceComponent(std::make_unique<IndependentSpriteRenderer>(obj1.get(), glm::vec4{1, 1, 1, 1}));
    activeGameObject = obj1.get();
    addGameObject(std::move(obj1));
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
void LevelEditorScene::imgui()
{
    ImGui::Begin("Test Window");
    ImGui::Text("Some random text");
    ImGui::End();
}
