#include "jade/LevelScene.hpp"
#include "jade/Window.hpp"

LevelScene::LevelScene()
{
    Window::get().r = 1.0F;
    Window::get().g = 1.0F;
    Window::get().b = 1.0F;
}

void LevelScene::update(float dt)
{
}
