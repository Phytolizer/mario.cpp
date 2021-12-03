#include "jade/Component.hpp"
#include "jade/ComponentClass.hpp"
#include "jade/components/DependentSpriteRenderer.hpp"
#include "jade/components/FontRenderer.hpp"
#include "jade/components/IndependentSpriteRenderer.hpp"

Component::Component(GameObject* go) : gameObject(go)
{
}

std::unique_ptr<Component> Component::fromSerial(const proto::Component& serial, GameObject* go)
{
    std::string_view type = serial.type();
    if (type == "DependentSpriteRenderer")
    {
        throw std::runtime_error{"Not sure how to deserialize DependentSpriteRenderer"};
    }
    if (type == "IndependentSpriteRenderer")
    {
        if (serial.properties().has_sprite())
        {
            auto result =
                std::make_unique<IndependentSpriteRenderer>(go, Sprite::fromSerial(serial.properties().sprite()));
            result->setColor(glm::vec4{serial.properties().color().red(), serial.properties().color().green(),
                                       serial.properties().color().blue(), serial.properties().color().alpha()});
            return result;
        }

        return std::make_unique<IndependentSpriteRenderer>(
            go, glm::vec4{serial.properties().color().red(), serial.properties().color().green(),
                          serial.properties().color().blue(), serial.properties().color().alpha()});
    }

    throw std::runtime_error{"Corrupt Component while deserializing!"};
}

std::unique_ptr<Component> Component::make(ComponentClass componentClass, GameObject* go)
{
    switch (componentClass)
    {
    case ComponentClass::SPRITE_RENDERER:
        return std::make_unique<IndependentSpriteRenderer>(go, glm::vec4{});
    case ComponentClass::FONT_RENDERER:
        return std::make_unique<FontRenderer>(go);
    }

    throw std::runtime_error{"Corrupt component class!"};
}

void Component::start()
{
}

void Component::imgui()
{
}

void Component::update(float dt)
{
}
