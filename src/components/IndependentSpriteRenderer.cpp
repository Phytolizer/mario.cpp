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
    if (m_sprite == nullptr)
    {
        return nullptr;
    }
    return m_sprite->getTexture();
}

const std::vector<glm::vec2>& IndependentSpriteRenderer::getTexCoords() const
{
    if (m_sprite == nullptr)
    {
        static const std::vector<glm::vec2> coords{glm::vec2{1, 1}, glm::vec2{1, 0}, glm::vec2{0, 0}, glm::vec2{0, 1}};
        return coords;
    }
    return m_sprite->getTexCoords();
}
