#include "components/IndependentSprite.hpp"

IndependentSprite::IndependentSprite(std::unique_ptr<Texture> texture) : Sprite(), m_texture(std::move(texture))
{
}

IndependentSprite::IndependentSprite(std::unique_ptr<Texture> texture, std::vector<glm::vec2> texCoords)
    : Sprite(std::move(texCoords)), m_texture(std::move(texture))
{
}

Texture* IndependentSprite::getTexture()
{
    return m_texture.get();
}
