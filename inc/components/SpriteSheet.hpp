#pragma once

#include "components/Sprite.hpp"
#include <memory>
#include <renderer/Texture.hpp>
#include <vector>

class SpriteSheet
{
    std::shared_ptr<Texture> m_texture;
    std::vector<std::shared_ptr<Sprite>> m_sprites;

  public:
    SpriteSheet(std::shared_ptr<Texture> texture, int spriteWidth, int spriteHeight, int numSprites, int spacing);
    std::shared_ptr<Sprite> getSprite(size_t index);
};
