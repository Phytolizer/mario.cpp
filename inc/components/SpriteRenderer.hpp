#pragma once

#include "components/Sprite.hpp"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <jade/Component.hpp>
#include <memory>
#include <renderer/Texture.hpp>
#include <vector>

class SpriteRenderer : public Component
{
    glm::vec4 m_color;
    std::unique_ptr<Sprite> m_sprite;

  public:
    SpriteRenderer(GameObject* go, glm::vec4 color);
    SpriteRenderer(GameObject* go, std::unique_ptr<Sprite> sprite);
    bool hasClass(ComponentClass cls) override;
    void start() override;
    void update(float dt) override;
    [[nodiscard]] const glm::vec4& getColor() const;
    [[nodiscard]] Texture* getTexture();
    [[nodiscard]] const std::vector<glm::vec2>& getTexCoords() const;
};
