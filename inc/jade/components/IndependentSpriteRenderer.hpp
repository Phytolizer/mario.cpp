#pragma once

#include "SpriteRenderer.hpp"

class IndependentSpriteRenderer : public SpriteRenderer
{
    std::unique_ptr<Sprite> m_sprite;

  public:
    IndependentSpriteRenderer(GameObject* go, glm::vec4 color);
    IndependentSpriteRenderer(GameObject* go, std::unique_ptr<Sprite> sprite);
    [[nodiscard]] Texture* getTexture() override;
    [[nodiscard]] const std::vector<glm::vec2>& getTexCoords() const override;
};

static_assert(std::is_constructible_v<IndependentSpriteRenderer, GameObject*, std::unique_ptr<Sprite>>, "IndependentSpriteRenderer is not constructible");
