#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <string>

class Window
{
    int m_width;
    int m_height;
    std::string m_title;
    GLFWwindow* m_glfwWindow;

    static Window s_window;

    Window();

    void init();
    void loop();

  public:
    static Window& get();
    void run();
};
