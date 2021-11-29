#pragma once

#include "jade/Camera.hpp"
#include "jade/Component.hpp"
#include "jade/Scene.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"
#include <array>
#include <string>

class LevelEditorScene : public Scene
{
  public:
    LevelEditorScene();

    void init() override;
    void update(float dt) override;
};
