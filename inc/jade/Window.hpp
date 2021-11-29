#pragma once

#include "jade/Scene.hpp"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <memory>
#include <string>

class Window
{
    int m_width;
    int m_height;
    std::string m_title;
    GLFWwindow* m_glfwWindow;

    static Window s_window;
    static std::unique_ptr<Scene> s_currentScene;

    Window();

    void init();
    void loop();

  public:
    float r;
    float g;
    float b;

    static void changeScene(int scene);
    static Window& get();
    void run();
};
