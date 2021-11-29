#pragma once

#include <glm/glm.hpp>

class Camera
{
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::vec2 m_position;

  public:
    explicit Camera(glm::vec2 position);

    void adjustProjection();
    glm::mat4 getViewMatrix();
    const glm::mat4& getProjectionMatrix() const;
};
