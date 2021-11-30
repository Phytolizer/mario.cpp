#include <utility>

#include "components/Sprite.hpp"

Sprite::Sprite(std::shared_ptr<Texture> texture)
    : m_texture(std::move(texture)), m_texCoords{glm::vec2{1, 1}, glm::vec2{1, 0}, glm::vec2{0, 0}, glm::vec2{0, 1}}
{
}

Sprite::Sprite(std::shared_ptr<Texture> texture, std::vector<glm::vec2> texCoords)
    : m_texture(std::move(texture)), m_texCoords(std::move(texCoords))
{
}

Texture* Sprite::getTexture()
{
    return m_texture.get();
}

const std::vector<glm::vec2>& Sprite::getTexCoords() const
{
    return m_texCoords;
}
