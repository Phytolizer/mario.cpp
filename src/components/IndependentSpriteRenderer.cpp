#include "components/IndependentSpriteRenderer.hpp"

IndependentSpriteRenderer::IndependentSpriteRenderer(GameObject* go, glm::vec4 color)
    : SpriteRenderer(go, color), m_sprite(nullptr)
{
}

IndependentSpriteRenderer::IndependentSpriteRenderer(GameObject* go, std::unique_ptr<Sprite> sprite)
    : SpriteRenderer(go), m_sprite(std::move(sprite))
{
}

Texture* IndependentSpriteRenderer::getTexture()
{
    return m_sprite->getTexture();
}

const std::vector<glm::vec2>& IndependentSpriteRenderer::getTexCoords() const
{
    return m_sprite->getTexCoords();
}
