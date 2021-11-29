#include "components/FontRenderer.hpp"
#include "components/SpriteRenderer.hpp"
#include <iostream>
#include <jade/GameObject.hpp>

FontRenderer::FontRenderer(GameObject* go) : Component(go)
{
}

bool FontRenderer::hasClass(ComponentClass cls)
{
    return cls == ComponentClass::FONT_RENDERER;
}

void FontRenderer::start()
{
    if (gameObject->getComponent<SpriteRenderer>(ComponentClass::SPRITE_RENDERER) != nullptr)
    {
        std::cout << "Found a SpriteRenderer" << std::endl;
    }
}

void FontRenderer::update(float dt)
{
}
