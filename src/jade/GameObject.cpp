#include "jade/GameObject.hpp"

GameObject::GameObject(std::string_view name) : m_name(name)
{
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
