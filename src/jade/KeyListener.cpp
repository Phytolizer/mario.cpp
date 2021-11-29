#include "jade/KeyListener.hpp"

KeyListener KeyListener::s_instance;

KeyListener::KeyListener()
{
    m_keyPressed.fill(false);
}

void KeyListener::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        get().m_keyPressed[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        get().m_keyPressed[key] = false;
    }
}

KeyListener& KeyListener::get()
{
    return s_instance;
}

bool KeyListener::isKeyPressed(int keycode)
{
    return get().m_keyPressed.at(keycode);
}
