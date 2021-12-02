#pragma once

#include "jade/components/DependentSprite.hpp"
#include "jade/components/Sprite.hpp"
#include "jade/renderer/Texture.hpp"
#include <memory>
#include <vector>

class SpriteSheet
{
    std::unique_ptr<Texture> m_texture;
    std::vector<std::unique_ptr<DependentSprite>> m_sprites;

  public:
    SpriteSheet(std::unique_ptr<Texture> texture, int spriteWidth, int spriteHeight, int numSprites, int spacing);
    Sprite* getSprite(size_t index);
};
