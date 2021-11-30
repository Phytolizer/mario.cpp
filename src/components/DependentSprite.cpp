#include "components/DependentSprite.hpp"

DependentSprite::DependentSprite(Texture* texture) : Sprite(), m_texture(texture)
{
}

DependentSprite::DependentSprite(Texture* texture, std::vector<glm::vec2> texCoords)
    : Sprite(std::move(texCoords)), m_texture(texture)
{
}

Texture* DependentSprite::getTexture()
{
    return m_texture;
}
