#pragma once

#include "jade/Camera.hpp"
#include "jade/Component.hpp"
#include "jade/Scene.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"
#include <array>
#include <string>

struct LevelEditorScene : Scene
{
  private:
    static constexpr std::array vertexArray = {
        // position           // color                // UV Coordinates
        100.0F, 0.0F,   0.0F, 1.0F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F, // Bottom right
        0.0F,   100.0F, 0.0F, 0.0F, 1.0F, 0.0F, 1.0F, 0.0F, 0.0F, // Top left
        100.0F, 100.0F, 0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F, 0.0F, // Top right
        0.0F,   0.0F,   0.0F, 1.0F, 1.0F, 0.0F, 1.0F, 0.0F, 1.0F, // Bottom left
    };
    static constexpr std::array elementArray = {
        2, 1, 0, // Top right triangle
        0, 1, 3, // Bottom left triangle
    };
    unsigned int m_vaoId;
    unsigned int m_vboId;
    unsigned int m_eboId;

    Shader m_defaultShader;
    Texture m_testTexture;
    Camera m_camera;
    std::unique_ptr<GameObject> m_testObj;
    bool m_firstTime;

  public:
    LevelEditorScene();

    void init() override;
    void update(float dt) override;
};
