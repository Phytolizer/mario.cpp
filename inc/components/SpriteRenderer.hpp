#pragma once

#include "glm/ext/vector_float4.hpp"
#include <glm/vec4.hpp>
#include <jade/Component.hpp>

class SpriteRenderer : public Component
{
    glm::vec4 m_color;

  public:
    explicit SpriteRenderer(GameObject* go, glm::vec4 color);
    bool hasClass(ComponentClass cls) override;
    void start() override;
    void update(float dt) override;
    const glm::vec4& getColor() const;
};
