#include "jade/components/DependentSpriteRenderer.hpp"
#include <Level.pb.h>

DependentSpriteRenderer::DependentSpriteRenderer(GameObject* go, Sprite* sprite) : SpriteRenderer(go), m_sprite(sprite)
{
}

Texture* DependentSpriteRenderer::getTexture()
{
    return m_sprite->getTexture();
}

const std::vector<glm::vec2>& DependentSpriteRenderer::getTexCoords() const
{
    return m_sprite->getTexCoords();
}

void DependentSpriteRenderer::setSprite(Sprite* sprite)
{
    m_sprite = sprite;
    m_isDirty = true;
}

void DependentSpriteRenderer::saveState(proto::Component* serial) const
{
    serial->set_type("DependentSpriteRenderer");
    proto::ComponentProperties* props = serial->mutable_properties();
    proto::Color* color = props->mutable_color();
    color->set_red(m_color.r);
    color->set_green(m_color.g);
    color->set_blue(m_color.b);
    color->set_alpha(m_color.a);
    proto::Sprite* sprite = props->mutable_sprite();
    for (const auto& texCoord : m_sprite->getTexCoords())
    {
        proto::Vec2* t = sprite->add_texcoords();
        t->set_x(texCoord.x);
        t->set_y(texCoord.y);
    }
}
