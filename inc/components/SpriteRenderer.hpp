#pragma once

#include <jade/Component.hpp>

class SpriteRenderer : public Component
{
    bool m_firstTime;

  public:
    explicit SpriteRenderer(GameObject* go);
    bool hasClass(ComponentClass cls) override;
    void start() override;
    void update(float dt) override;
};
