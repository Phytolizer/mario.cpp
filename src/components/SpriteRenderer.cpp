#include "components/SpriteRenderer.hpp"
#include <fmt/core.h>
#include <iostream>
#include <jade/GameObject.hpp>

SpriteRenderer::SpriteRenderer(GameObject* go, glm::vec4 color) : Component(go), m_color(color), m_texture(nullptr)
{
}

bool SpriteRenderer::hasClass(ComponentClass cls)
{
    return cls == ComponentClass::SPRITE_RENDERER;
}

void SpriteRenderer::start()
{
}

void SpriteRenderer::update(float dt)
{
}

const glm::vec4& SpriteRenderer::getColor() const
{
    return m_color;
}

SpriteRenderer::SpriteRenderer(GameObject* go, std::unique_ptr<Texture> texture)
    : Component(go), m_color(1, 1, 1, 1), m_texture(std::move(texture))
{
}

Texture* SpriteRenderer::getTexture()
{
    return m_texture.get();
}

std::vector<glm::vec2> SpriteRenderer::getTexCoords()
{
    std::vector<glm::vec2> texCoords = {
        glm::vec2{1, 1},
        glm::vec2{1, 0},
        glm::vec2{0, 0},
        glm::vec2{0, 1},
    };
    return texCoords;
}
