#pragma once

#include "components/Sprite.hpp"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <jade/Component.hpp>
#include <renderer/Texture.hpp>
#include <vector>

class SpriteRenderer : public Component
{
    glm::vec4 m_color;

  protected:
    explicit SpriteRenderer(GameObject* go);
    SpriteRenderer(GameObject* go, glm::vec4 color);

  public:
    bool hasClass(ComponentClass cls) override;
    void start() override;
    void update(float dt) override;
    [[nodiscard]] const glm::vec4& getColor() const;
    [[nodiscard]] virtual Texture* getTexture() = 0;
    [[nodiscard]] const virtual std::vector<glm::vec2>& getTexCoords() const = 0;
};
