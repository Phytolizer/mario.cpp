#include "jade/Component.hpp"
#include "jade/ComponentClass.hpp"
#include <components/FontRenderer.hpp>
#include <components/SpriteRenderer.hpp>

Component::Component(GameObject* go) : gameObject(go)
{
}

std::unique_ptr<Component> Component::make(ComponentClass componentClass, GameObject* go)
{
    switch (componentClass)
    {
    case ComponentClass::SPRITE_RENDERER:
        return std::make_unique<SpriteRenderer>(go, glm::vec4{});
    case ComponentClass::FONT_RENDERER:
        return std::make_unique<FontRenderer>(go);
    }
}

void Component::start()
{
}
