#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <array>

class MouseListener
{
    static MouseListener s_instance;
    double m_scrollX;
    double m_scrollY;
    double m_xPos;
    double m_yPos;
    double m_lastX;
    double m_lastY;
    std::array<bool, 3> m_mouseButtonPressed;
    bool m_isDragging;

    MouseListener();

  public:
    static MouseListener& get();
    static void mousePosCallback(GLFWwindow* window, double xPos, double yPos);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void endFrame();
    static double getX();
    static double getY();
    static double getDx();
    static double getDy();
    static double getScrollX();
    static double getScrollY();
    static bool isDragging();
    static bool mouseButtonDown(int button);
};
