#pragma once

#include "Level.pb.h"
#include "jade/renderer/Texture.hpp"
#include <glm/vec2.hpp>
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
    static std::unique_ptr<Sprite> fromSerial(const proto::Sprite& serial);
};
