#include "jade/Window.hpp"
#include "jade/KeyListener.hpp"
#include "jade/LevelEditorScene.hpp"
#include "jade/LevelScene.hpp"
#include "jade/MouseListener.hpp"
#include "util/Time.hpp"
#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <stdexcept>

static void error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

Window Window::s_window;
std::unique_ptr<Scene> Window::s_currentScene;

Window::Window() : m_width(1920), m_height(1080), m_title("Mario"), r(1.0F), g(1.0F), b(1.0F)
{
}

Window& Window::get()
{
    return s_window;
}

void Window::run()
{
    init();
    loop();
    glfwDestroyWindow(m_glfwWindow);
    glfwTerminate();
}

void Window::init()
{
    // Set error callback
    glfwSetErrorCallback(error_callback);

    // Init GLFW
    if (glfwInit() != GLFW_TRUE)
    {
        throw std::runtime_error{"Failed to initialize GLFW"};
    }

    // Configure GLFW
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // Create the window
    m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (m_glfwWindow == nullptr)
    {
        throw std::runtime_error{"Failed to create the GLFW window"};
    }

    glfwSetCursorPosCallback(m_glfwWindow, MouseListener::mousePosCallback);
    glfwSetMouseButtonCallback(m_glfwWindow, MouseListener::mouseButtonCallback);
    glfwSetScrollCallback(m_glfwWindow, MouseListener::mouseScrollCallback);
    glfwSetKeyCallback(m_glfwWindow, KeyListener::keyCallback);

    // Make the OpenGL context current
    glfwMakeContextCurrent(m_glfwWindow);
    // Enable VSync
    glfwSwapInterval(1);

    // Make the window visible
    glfwShowWindow(m_glfwWindow);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    changeScene(0);
}

void Window::loop()
{
    float beginTime = Time::getTime();
    float endTime = Time::getTime();
    float dt = -1.0F;

    while (!glfwWindowShouldClose(m_glfwWindow))
    {
        glfwPollEvents();

        glClearColor(r, g, b, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        if (dt == 0)
        {
            dt = FLT_EPSILON;
        }
        if (dt > 0)
        {
            s_currentScene->update(dt);
        }

        glfwSwapBuffers(m_glfwWindow);

        endTime = Time::getTime();
        dt = endTime - beginTime;
        beginTime = endTime;
    }
}

void Window::changeScene(int scene)
{
    switch (scene)
    {
    case 0:
        s_currentScene = std::make_unique<LevelEditorScene>();
        s_currentScene->init();
        break;
    case 1:
        s_currentScene = std::make_unique<LevelScene>();
        s_currentScene->init();
        break;
    default:
        throw std::runtime_error{fmt::format("Unknown scene '{}'", scene)};
    }
}
