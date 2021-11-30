#pragma once

#include <memory>
#include <glm/vec2.hpp>
#include <renderer/Texture.hpp>
#include <vector>

class Sprite
{
    std::unique_ptr<Texture> m_texture;
    std::vector<glm::vec2> m_texCoords;

  public:
    explicit Sprite(std::unique_ptr<Texture> texture);
    Sprite(std::unique_ptr<Texture> texture, std::vector<glm::vec2> texCoords);

    [[nodiscard]] Texture* getTexture();
    [[nodiscard]] const std::vector<glm::vec2>& getTexCoords() const;
};
