#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <array>

class KeyListener
{
    static KeyListener s_instance;

    std::array<bool, 350> m_keyPressed;

    KeyListener();

  public:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static KeyListener& get();
    static bool isKeyPressed(int keycode);
};
