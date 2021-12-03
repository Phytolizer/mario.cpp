#include "jade/components/FontRenderer.hpp"
#include "jade/GameObject.hpp"
#include "jade/components/SpriteRenderer.hpp"
#include <iostream>

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

void FontRenderer::saveState(proto::Component* serial) const
{
}
