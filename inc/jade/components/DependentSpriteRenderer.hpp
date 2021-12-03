#pragma once

#include "SpriteRenderer.hpp"
#include <Level.pb.h>

class DependentSpriteRenderer : public SpriteRenderer
{
    Sprite* m_sprite;

  public:
    DependentSpriteRenderer(GameObject* go, Sprite* sprite);
    [[nodiscard]] Texture* getTexture() override;
    [[nodiscard]] const std::vector<glm::vec2>& getTexCoords() const override;
    void setSprite(Sprite* sprite);
    void saveState(proto::Component* serial) const override;
};

static_assert(std::is_constructible_v<DependentSpriteRenderer, GameObject*, Sprite*>,
              "DependentSpriteRenderer is not constructible");
