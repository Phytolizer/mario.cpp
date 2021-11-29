#pragma once

#include "jade/Scene.hpp"

struct LevelScene : Scene
{
    LevelScene();

    void update(float dt) override;
};
