#pragma once

#include "Level.pb.h"
#include "jade/Component.hpp"
#include "jade/ComponentClass.hpp"
#include "jade/Transform.hpp"
#include <concepts>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

class GameObject
{
    std::string m_name;
    std::vector<std::unique_ptr<Component>> m_components;
    int m_zIndex;

  public:
    Transform transform;
    explicit GameObject(std::string_view name, int zIndex);
    GameObject(std::string_view name, Transform transform, int zIndex);

    template <typename T> void addComponent(ComponentClass componentClass) requires std::derived_from<T, Component>;
    void emplaceComponent(std::unique_ptr<Component> component);
    template <typename T> T* getComponent(ComponentClass componentClass) requires std::derived_from<T, Component>;
    template <typename T> void removeComponent(ComponentClass componentClass) requires std::derived_from<T, Component>;

    std::string_view getName() const;

    void update(float dt);
    void start();
    void imgui();
    [[nodiscard]] int zIndex() const;
    void saveState(proto::GameObject* serial) const;
};

template <typename T>
void GameObject::addComponent(ComponentClass componentClass) requires std::derived_from<T, Component>
{
    m_components.emplace_back(Component::make(componentClass, this));
}

template <typename T>
T* GameObject::getComponent(ComponentClass componentClass) requires std::derived_from<T, Component>
{
    for (auto& component : m_components)
    {
        if (component->hasClass(componentClass))
        {
            return reinterpret_cast<T*>(component.get());
        }
    }
    return nullptr;
}

template <typename T>
void GameObject::removeComponent(ComponentClass componentClass) requires std::derived_from<T, Component>
{
    for (size_t i = 0; i < m_components.size(); ++i)
    {
        if (m_components[i]->hasClass(componentClass))
        {
            m_components.erase(m_components.begin() + i);
            return;
        }
    }
}
