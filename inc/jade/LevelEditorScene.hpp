#pragma once

#include "jade/Camera.hpp"
#include "jade/Scene.hpp"
#include "renderer/Shader.hpp"
#include <array>
#include <string>

struct LevelEditorScene : Scene
{
  private:
    std::string m_vertexShaderSource = "#version 330 core\n"
                                       "layout (location = 0) in vec3 aPos;\n"
                                       "layout (location = 1) in vec4 aColor;\n"
                                       "\n"
                                       "out vec4 fColor;\n"
                                       "\n"
                                       "void main()\n"
                                       "{\n"
                                       "    fColor = aColor;\n"
                                       "    gl_Position = vec4(aPos, 1.0);\n"
                                       "}\n";
    std::string m_fragmentShaderSource = "#version 330 core\n"
                                         "in vec4 fColor;\n"
                                         "out vec4 color;\n"
                                         "\n"
                                         "void main()\n"
                                         "{\n"
                                         "    color = fColor;\n"
                                         "}\n";

    int m_vertexId;
    int m_fragmentId;
    int m_shaderProgram;
    static constexpr std::array vertexArray = {
        // position           // color
        50.5F,  -50.5F, 0.0F, 1.0F, 0.0F, 0.0F, 1.0F, // Bottom right
        -50.5F, 50.5F,  0.0F, 0.0F, 1.0F, 0.0F, 1.0F, // Top left
        50.5F,  50.5F,  0.0F, 0.0F, 0.0F, 1.0F, 1.0F, // Top right
        -50.5F, -50.5F, 0.0F, 1.0F, 1.0F, 0.0F, 1.0F, // Bottom left
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
