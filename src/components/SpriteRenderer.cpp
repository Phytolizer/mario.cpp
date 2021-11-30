#include "components/SpriteRenderer.hpp"
#include <fmt/core.h>
#include <iostream>
#include <jade/GameObject.hpp>

SpriteRenderer::SpriteRenderer(GameObject* go, glm::vec4 color) : Component(go), m_color(color), m_sprite(nullptr)
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

SpriteRenderer::SpriteRenderer(GameObject* go, std::unique_ptr<Sprite> sprite)
    : Component(go), m_color(1, 1, 1, 1), m_sprite(std::move(sprite))
{
}

Texture* SpriteRenderer::getTexture()
{
    return m_sprite->getTexture();
}

const std::vector<glm::vec2>& SpriteRenderer::getTexCoords() const
{
    return m_sprite->getTexCoords();
}
