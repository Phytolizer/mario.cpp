#include "jade/MouseListener.hpp"
#include <algorithm>

MouseListener MouseListener::s_instance;

MouseListener::MouseListener()
    : m_scrollX(0), m_scrollY(0), m_xPos(0), m_yPos(0), m_lastX(0), m_lastY(0), m_isDragging(false)
{
    m_mouseButtonPressed.fill(false);
}

MouseListener& MouseListener::get()
{
    return s_instance;
}

void MouseListener::mousePosCallback(GLFWwindow* window, double xPos, double yPos)
{
    get().m_lastX = get().m_xPos;
    get().m_lastY = get().m_yPos;
    get().m_xPos = xPos;
    get().m_yPos = yPos;
    get().m_isDragging =
        std::any_of(get().m_mouseButtonPressed.begin(), get().m_mouseButtonPressed.end(), [](bool b) { return b; });
}

void MouseListener::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (button < get().m_mouseButtonPressed.size())
        {
            get().m_mouseButtonPressed[button] = true;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        if (button < get().m_mouseButtonPressed.size())
        {
            get().m_mouseButtonPressed[button] = false;
        }
        get().m_isDragging = false;
    }
}

void MouseListener::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    get().m_scrollX = xOffset;
    get().m_scrollY = yOffset;
}

void MouseListener::endFrame()
{
    get().m_scrollX = 0;
    get().m_scrollY = 0;
    get().m_lastX = get().m_xPos;
    get().m_lastY = get().m_yPos;
}

double MouseListener::getX()
{
    return get().m_xPos;
}

double MouseListener::getY()
{
    return get().m_yPos;
}

double MouseListener::getDx()
{
    return get().m_xPos - get().m_lastX;
}

double MouseListener::getDy()
{
    return get().m_yPos - get().m_lastY;
}

double MouseListener::getScrollX()
{
    return get().m_scrollX;
}

double MouseListener::getScrollY()
{
    return get().m_scrollY;
}

bool MouseListener::isDragging()
{
    return get().m_isDragging;
}

bool MouseListener::mouseButtonDown(int button)
{
    if (button < get().m_mouseButtonPressed.size())
    {
        return get().m_mouseButtonPressed[button];
    }
    return false;
}
