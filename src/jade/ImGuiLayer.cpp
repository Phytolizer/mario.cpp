#include "jade/ImGuiLayer.hpp"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

ImGuiLayer::ImGuiLayer(GLFWwindow* window) : m_window(window)
{
    m_context = ImGui::CreateContext();
}

ImGuiLayer::~ImGuiLayer()
{
    ImGui::DestroyContext(m_context);
}

void ImGuiLayer::setWindow(GLFWwindow* window)
{
    m_window = window;
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void ImGuiLayer::update(float deltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
