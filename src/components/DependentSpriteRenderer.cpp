#include "components/DependentSpriteRenderer.hpp"

DependentSpriteRenderer::DependentSpriteRenderer(GameObject* go, Sprite* sprite) : SpriteRenderer(go), m_sprite(sprite)
{
}

Texture* DependentSpriteRenderer::getTexture()
{
    return m_sprite->getTexture();
}

const std::vector<glm::vec2>& DependentSpriteRenderer::getTexCoords() const
{
    return m_sprite->getTexCoords();
}

void DependentSpriteRenderer::setSprite(Sprite* sprite)
{
    m_sprite = sprite;
    m_isDirty = true;
}
