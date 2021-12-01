#pragma once

#include "Scene.hpp"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <vector>

class ImGuiLayer
{
    GLFWwindow* m_window;
    ImGuiContext* m_context;
    std::vector<GLFWcursor*> m_mouseCursors;

  public:
    explicit ImGuiLayer(GLFWwindow* window);
    ~ImGuiLayer();

    void setWindow(GLFWwindow* window);
    void update(float deltaTime, Scene* scene);
};
