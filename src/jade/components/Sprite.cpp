#include "jade/components/Sprite.hpp"

#include "jade/components/DependentSprite.hpp"
#include "jade/components/IndependentSprite.hpp"

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

std::unique_ptr<Sprite> Sprite::fromSerial(const proto::Sprite& serial)
{
    if (serial.has_texture())
    {
        std::vector<glm::vec2> texcoords;
        for (int i = 0; i < serial.texcoords_size(); ++i)
        {
            texcoords.emplace_back(serial.texcoords()[i].x(), serial.texcoords()[i].y());
        }
        return std::make_unique<IndependentSprite>(Texture::fromSerial(serial.texture()), texcoords);
    }

    throw std::runtime_error{"Not sure how to deserialize DependentSprite"};
}
