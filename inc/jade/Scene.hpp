#pragma once

struct Scene
{
    Scene() = default;

    virtual void update(float dt) = 0;
};
