#include "components/SpriteRenderer.hpp"
#include <jade/GameObject.hpp>

SpriteRenderer::SpriteRenderer(GameObject* go) : Component(go), m_color{1, 1, 1, 1}
{
}

SpriteRenderer::SpriteRenderer(GameObject* go, glm::vec4 color) : Component(go), m_color(color)
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
