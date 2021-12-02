#pragma once

#include "jade/GameObject.hpp"
#include "jade/Scene.hpp"
#include "jade/components/SpriteSheet.hpp"

class LevelEditorScene : public Scene
{
    std::unique_ptr<SpriteSheet> m_spriteSheet;

  public:
    LevelEditorScene();

    void init() override;
    void update(float dt) override;
    void imgui() override;
};
