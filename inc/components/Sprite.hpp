#pragma once

#include <memory>
#include <glm/vec2.hpp>
#include <renderer/Texture.hpp>
#include <vector>

class Sprite
{
    // ownership of the texture is complex.
    // either the Sprite owns it or the SpriteSheet does,
    // so it's shared ownership.
    std::shared_ptr<Texture> m_texture;
    std::vector<glm::vec2> m_texCoords;

  public:
    explicit Sprite(std::shared_ptr<Texture> texture);
    Sprite(std::shared_ptr<Texture> texture, std::vector<glm::vec2> texCoords);

    [[nodiscard]] Texture* getTexture();
    [[nodiscard]] const std::vector<glm::vec2>& getTexCoords() const;
};
