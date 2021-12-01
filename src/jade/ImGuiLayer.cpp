#include "jade/ImGuiLayer.hpp"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

ImGuiLayer::ImGuiLayer(GLFWwindow* window) : m_window(nullptr)
{
    m_context = ImGui::CreateContext();
    setWindow(window);
}

ImGuiLayer::~ImGuiLayer()
{
    ImGui::DestroyContext(m_context);
}

void ImGuiLayer::setWindow(GLFWwindow* window)
{
    m_window = window;
    if (m_window)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
        io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\CONSOLA.TTF)", 20.0F);
    }
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
