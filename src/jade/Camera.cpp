#include "jade/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec2 position) : m_projectionMatrix(0), m_viewMatrix(0), m_position(position)
{
    adjustProjection();
}

void Camera::adjustProjection()
{
    m_projectionMatrix = glm::ortho(0.0F, 32.0F * 40.0F, 0.0F, 32.0F * 21.0F, 0.0F, 100.0F);
}

glm::mat4 Camera::getViewMatrix()
{
    constexpr glm::vec3 cameraFront{0.0F, 0.0F, -1.0F};
    constexpr glm::vec3 cameraUp{0.0F, 1.0F, 0.0F};
    m_viewMatrix = glm::lookAt(glm::vec3{m_position.x, m_position.y, 20.0F},
                               cameraFront + glm::vec3{m_position.x, m_position.y, 0.0F}, cameraUp);
    return m_viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}
