#include "components/SpriteRenderer.hpp"
#include <fmt/core.h>
#include <iostream>
#include <jade/GameObject.hpp>

SpriteRenderer::SpriteRenderer(GameObject* go) : Component(go), m_firstTime(true)
{
}

bool SpriteRenderer::hasClass(ComponentClass cls)
{
    return cls == ComponentClass::SPRITE_RENDERER;
}

void SpriteRenderer::start()
{
    fmt::print("<SpriteRenderer@{}: {}> start\n", (void*)this, gameObject->getName());
}

void SpriteRenderer::update(float dt)
{
    if (m_firstTime)
    {
        fmt::print("<SpriteRenderer@{}: {}> update\n", (void*)this, gameObject->getName());
        m_firstTime = false;
    }
}
