#include "components/SpriteRenderer.hpp"
#include <imgui.h>
#include <jade/GameObject.hpp>

SpriteRenderer::SpriteRenderer(GameObject* go) : Component(go), m_color{1, 1, 1, 1}, m_isDirty(true)
{
}

SpriteRenderer::SpriteRenderer(GameObject* go, glm::vec4 color) : Component(go), m_color(color), m_isDirty(true)
{
}

bool SpriteRenderer::hasClass(ComponentClass cls)
{
    return cls == ComponentClass::SPRITE_RENDERER;
}

void SpriteRenderer::start()
{
    m_lastTransform = gameObject->transform;
}

void SpriteRenderer::update(float dt)
{
    if (m_lastTransform != gameObject->transform)
    {
        m_lastTransform = gameObject->transform;
        m_isDirty = true;
    }
}

const glm::vec4& SpriteRenderer::getColor() const
{
    return m_color;
}

void SpriteRenderer::setColor(glm::vec4 color)
{
    if (m_color != color)
    {
        m_color = color;
        m_isDirty = true;
    }
}

bool SpriteRenderer::isDirty() const
{
    return m_isDirty;
}

void SpriteRenderer::setClean()
{
    m_isDirty = false;
}

void SpriteRenderer::imgui()
{
    float imColor[] = {m_color.r, m_color.g, m_color.b, m_color.a};
    if (ImGui::ColorPicker4("Color Picker: ", imColor))
    {
        m_color.r = imColor[0];
        m_color.g = imColor[1];
        m_color.b = imColor[2];
        m_color.a = imColor[3];
        m_isDirty = true;
    }
}
