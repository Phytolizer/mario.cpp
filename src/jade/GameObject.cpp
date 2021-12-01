#include "jade/GameObject.hpp"
#include "jade/Transform.hpp"

GameObject::GameObject(std::string_view name, int zIndex) : m_name(name), m_zIndex(zIndex)
{
}

GameObject::GameObject(std::string_view name, Transform transform, int zIndex)
    : m_name(name), m_zIndex(zIndex), transform(transform)
{
}

void GameObject::emplaceComponent(std::unique_ptr<Component> component)
{
    m_components.emplace_back(std::move(component));
}

std::string_view GameObject::getName() const
{
    return m_name;
}

void GameObject::update(float dt)
{
    for (size_t i = 0; i < m_components.size(); ++i)
    {
        m_components[i]->update(dt);
    }
}

void GameObject::start()
{
    for (size_t i = 0; i < m_components.size(); ++i)
    {
        m_components[i]->start();
    }
}

int GameObject::zIndex() const
{
    return m_zIndex;
}

void GameObject::imgui()
{
    for (auto& c : m_components)
    {
        c->imgui();
    }
}
