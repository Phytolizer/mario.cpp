#pragma once

#include "Sprite.hpp"

class DependentSprite : public Sprite
{
    Texture* m_texture;

  public:
    explicit DependentSprite(Texture* texture);
    DependentSprite(Texture* texture, std::vector<glm::vec2> texCoords);

    Texture* getTexture() override;
};
