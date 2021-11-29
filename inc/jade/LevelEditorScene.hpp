#pragma once

#include "jade/Camera.hpp"
#include "jade/Scene.hpp"
#include "renderer/Shader.hpp"
#include <array>
#include <string>

struct LevelEditorScene : Scene
{
  private:
    int m_vertexId;
    int m_fragmentId;
    int m_shaderProgram;
    static constexpr std::array vertexArray = {
        // position           // color
        100.5F, 0.5F,   0.0F, 1.0F, 0.0F, 0.0F, 1.0F, // Bottom right
        0.5F,   100.5F, 0.0F, 0.0F, 1.0F, 0.0F, 1.0F, // Top left
        100.5F, 100.5F, 0.0F, 0.0F, 0.0F, 1.0F, 1.0F, // Top right
        0.5F,   0.5F,   0.0F, 1.0F, 1.0F, 0.0F, 1.0F, // Bottom left
    };
    static constexpr std::array elementArray = {
        2, 1, 0, // Top right triangle
        0, 1, 3, // Bottom left triangle
    };
    unsigned int m_vaoId;
    unsigned int m_vboId;
    unsigned int m_eboId;

    Shader m_defaultShader;
    Camera m_camera;

  public:
    LevelEditorScene();

    void init() override;
    void update(float dt) override;
};
