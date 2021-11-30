#pragma once

#include <glm/vec2.hpp>
#include <renderer/Texture.hpp>
#include <vector>

class Sprite
{
    // ownership of the texture is complex.
    // either the Sprite owns it or the SpriteSheet does,
    // so it's shared ownership.
    std::vector<glm::vec2> m_texCoords;

  protected:
    Sprite();
    explicit Sprite(std::vector<glm::vec2> texCoords);

  public:
    virtual ~Sprite() = default;

    [[nodiscard]] virtual Texture* getTexture() = 0;
    [[nodiscard]] const std::vector<glm::vec2>& getTexCoords() const;
};
