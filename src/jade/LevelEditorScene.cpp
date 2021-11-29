#include "jade/LevelEditorScene.hpp"
#include "jade/KeyListener.hpp"
#include "jade/Window.hpp"
#include <iostream>

void LevelEditorScene::update(float dt)
{
    std::cout << (1.0F / dt) << " FPS\n";

    if (!m_changingScene && KeyListener::isKeyPressed(GLFW_KEY_SPACE))
    {
        m_changingScene = true;
    }

    if (m_changingScene && m_timeToChangeScene > 0.0F)
    {
        m_timeToChangeScene -= dt;
        Window::get().r -= dt * 5.0F;
        Window::get().g -= dt * 5.0F;
        Window::get().b -= dt * 5.0F;
    }
    else if (m_changingScene)
    {
        m_changingScene = false;
        m_timeToChangeScene = 2.0F;
        Window::changeScene(1);
    }
}
