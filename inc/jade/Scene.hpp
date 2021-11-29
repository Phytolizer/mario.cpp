#pragma once

struct Scene
{
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init();

    virtual void update(float dt) = 0;
};
