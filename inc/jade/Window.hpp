#pragma once

#include <glad/glad.h>

#include "jade/ImGuiLayer.hpp"
#include "jade/Scene.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <string>

class Window
{
    int m_width;
    int m_height;
    std::string m_title;
    GLFWwindow* m_glfwWindow;
    ImGuiLayer m_imguiLayer;

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
    static Scene& getScene();
    void run();
    int getWidth() const;
    int getHeight() const;
};
