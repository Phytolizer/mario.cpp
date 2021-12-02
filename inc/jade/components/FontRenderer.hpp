#pragma once

#include "jade/Component.hpp"

class FontRenderer : public Component
{
  public:
    explicit FontRenderer(GameObject* go);
    bool hasClass(ComponentClass cls) override;
    void start() override;
    void update(float dt) override;
};
