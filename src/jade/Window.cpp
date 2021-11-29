#include "jade/Window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

static void error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

Window Window::s_window;

Window::Window() : m_width(1920), m_height(1080), m_title("Mario")
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

    // Make the OpenGL context current
    glfwMakeContextCurrent(m_glfwWindow);
    // Enable VSync
    glfwSwapInterval(1);

    // Make the window visible
    glfwShowWindow(m_glfwWindow);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Window::loop()
{
    while (!glfwWindowShouldClose(m_glfwWindow))
    {
        glfwPollEvents();

        glClearColor(1.0F, 0.0F, 0.0F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_glfwWindow);
    }
}
