#include "jade/components/SpriteSheet.hpp"

SpriteSheet::SpriteSheet(std::unique_ptr<Texture> texture, int spriteWidth, int spriteHeight, int numSprites,
                         int spacing)
    : m_texture(std::move(texture))
{
    int currentX = 0;
    int currentY = m_texture->getHeight() - spriteHeight;
    for (int i = 0; i < numSprites; ++i)
    {
        float topY = (currentY + spriteHeight) / (float)m_texture->getHeight();
        float rightX = (currentX + spriteWidth) / (float)m_texture->getWidth();
        float leftX = currentX / (float)m_texture->getWidth();
        float bottomY = currentY / (float)m_texture->getHeight();

        std::vector texCoords = {
            glm::vec2{rightX, topY},
            glm::vec2{rightX, bottomY},
            glm::vec2{leftX, bottomY},
            glm::vec2{leftX, topY},
        };
        m_sprites.emplace_back(std::make_unique<DependentSprite>(m_texture.get(), texCoords));

        currentX += spriteWidth + spacing;
        if (currentX >= m_texture->getWidth())
        {
            currentX = 0;
            currentY -= spriteHeight + spacing;
        }
    }
}

Sprite* SpriteSheet::getSprite(size_t index)
{
    return m_sprites[index].get();
}
