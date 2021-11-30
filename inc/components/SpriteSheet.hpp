#pragma once

#include "components/DependentSprite.hpp"
#include "components/Sprite.hpp"
#include <memory>
#include <renderer/Texture.hpp>
#include <vector>

class SpriteSheet
{
    std::unique_ptr<Texture> m_texture;
    std::vector<std::unique_ptr<DependentSprite>> m_sprites;

  public:
    SpriteSheet(std::unique_ptr<Texture> texture, int spriteWidth, int spriteHeight, int numSprites, int spacing);
    Sprite* getSprite(size_t index);
};
