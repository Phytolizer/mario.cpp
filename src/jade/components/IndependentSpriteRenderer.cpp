#include "jade/components/IndependentSpriteRenderer.hpp"

IndependentSpriteRenderer::IndependentSpriteRenderer(GameObject* go, glm::vec4 color)
    : SpriteRenderer(go, color), m_sprite(nullptr)
{
}

IndependentSpriteRenderer::IndependentSpriteRenderer(GameObject* go, std::unique_ptr<Sprite> sprite)
    : SpriteRenderer(go), m_sprite(std::move(sprite))
{
}

Texture* IndependentSpriteRenderer::getTexture()
{
    if (m_sprite == nullptr)
    {
        return nullptr;
    }
    return m_sprite->getTexture();
}

const std::vector<glm::vec2>& IndependentSpriteRenderer::getTexCoords() const
{
    if (m_sprite == nullptr)
    {
        static const std::vector<glm::vec2> coords{glm::vec2{1, 1}, glm::vec2{1, 0}, glm::vec2{0, 0}, glm::vec2{0, 1}};
        return coords;
    }
    return m_sprite->getTexCoords();
}

void IndependentSpriteRenderer::saveState(proto::Component* serial) const
{
    serial->set_type("IndependentSpriteRenderer");
    proto::ComponentProperties* props = serial->mutable_properties();
    proto::Color* color = props->mutable_color();
    color->set_red(m_color.r);
    color->set_green(m_color.g);
    color->set_blue(m_color.b);
    color->set_alpha(m_color.a);
    if (m_sprite != nullptr && m_sprite->getTexture() != nullptr)
    {
        proto::Sprite* sprite = props->mutable_sprite();
        proto::Texture* tex = sprite->mutable_texture();
        tex->set_filepath(std::string{m_sprite->getTexture()->getFilePath()});
        for (const auto& texCoord : m_sprite->getTexCoords())
        {
            proto::Vec2* t = sprite->add_texcoords();
            t->set_x(texCoord.x);
            t->set_y(texCoord.y);
        }
    }
}
