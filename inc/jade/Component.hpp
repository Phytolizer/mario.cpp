#pragma once

#include "jade/ComponentClass.hpp"
#include <memory>
#include <stdexcept>

class GameObject;

class Component
{
  public:
    GameObject* gameObject;

    explicit Component(GameObject* go);
    virtual ~Component() = default;
    static std::unique_ptr<Component> make(ComponentClass componentClass, GameObject* go);
    virtual void start();
    virtual void update(float dt) = 0;
    virtual bool hasClass(ComponentClass cls) = 0;
};
