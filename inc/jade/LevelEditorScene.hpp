#pragma once

#include "jade/Scene.hpp"

struct LevelEditorScene : Scene
{
  private:
    bool m_changingScene = false;
    float m_timeToChangeScene = 2.0F;

  public:
    LevelEditorScene() = default;

    void update(float dt) override;
};
