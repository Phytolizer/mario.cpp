#pragma once

#include "jade/Scene.hpp"
#include <components/SpriteSheet.hpp>

class LevelEditorScene : public Scene
{
    std::unique_ptr<SpriteSheet> m_spriteSheet;

  public:
    LevelEditorScene();

    void init() override;
    void update(float dt) override;
};
