#pragma once

#include "components/Sprite.hpp"

#include <memory>

class IndependentSprite : public Sprite
{
    std::unique_ptr<Texture> m_texture;

  public:
    explicit IndependentSprite(std::unique_ptr<Texture> texture);
    IndependentSprite(std::unique_ptr<Texture> texture, std::vector<glm::vec2> texCoords);

    Texture* getTexture() override;
};
