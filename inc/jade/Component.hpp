#pragma once

#include "Level.pb.h"
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
    static std::unique_ptr<Component> fromSerial(const proto::Component& serial, GameObject* go);
    static std::unique_ptr<Component> make(ComponentClass componentClass, GameObject* go);
    virtual void start();
    virtual void update(float dt);
    virtual bool hasClass(ComponentClass cls) = 0;
    virtual void imgui();
    virtual void saveState(proto::Component* serial) const = 0;
};
