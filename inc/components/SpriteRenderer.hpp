#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <jade/Component.hpp>
#include <memory>
#include <renderer/Texture.hpp>
#include <vector>

class SpriteRenderer : public Component
{
    glm::vec4 m_color;
    std::vector<glm::vec2> m_texCoords;
    std::unique_ptr<Texture> m_texture;

  public:
    SpriteRenderer(GameObject* go, glm::vec4 color);
    SpriteRenderer(GameObject* go, std::unique_ptr<Texture> texture);
    bool hasClass(ComponentClass cls) override;
    void start() override;
    void update(float dt) override;
    const glm::vec4& getColor() const;
    Texture* getTexture();
    std::vector<glm::vec2> getTexCoords();
};
