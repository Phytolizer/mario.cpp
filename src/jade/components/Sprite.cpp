#include "jade/components/Sprite.hpp"

Sprite::Sprite() : m_texCoords{glm::vec2{1, 1}, glm::vec2{1, 0}, glm::vec2{0, 0}, glm::vec2{0, 1}}
{
}

Sprite::Sprite(std::vector<glm::vec2> texCoords) : m_texCoords(std::move(texCoords))
{
}

const std::vector<glm::vec2>& Sprite::getTexCoords() const
{
    return m_texCoords;
}
