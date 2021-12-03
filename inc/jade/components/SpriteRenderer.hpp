#pragma once

#include "Sprite.hpp"
#include "jade/Component.hpp"
#include "jade/Transform.hpp"
#include "jade/renderer/Texture.hpp"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <vector>

class SpriteRenderer : public Component
{
    Transform m_lastTransform;

  protected:
    glm::vec4 m_color;
    bool m_isDirty;

    explicit SpriteRenderer(GameObject* go);
    SpriteRenderer(GameObject* go, glm::vec4 color);

  public:
    bool hasClass(ComponentClass cls) override;
    void start() override;
    void update(float dt) override;
    [[nodiscard]] const glm::vec4& getColor() const;
    [[nodiscard]] virtual Texture* getTexture() = 0;
    [[nodiscard]] const virtual std::vector<glm::vec2>& getTexCoords() const = 0;
    void setColor(glm::vec4 color);
    [[nodiscard]] bool isDirty() const;
    void setClean();
    void imgui() override;
};
