#pragma once

#include "jade/Camera.hpp"
#include "jade/GameObject.hpp"
#include <memory>
#include <renderer/Renderer.hpp>
#include <vector>

struct Scene
{
    bool m_isRunning;

  protected:
    Camera m_camera;
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    Renderer m_renderer;
    GameObject* activeGameObject = nullptr;

  public:
    Scene();
    virtual ~Scene() = default;

    virtual void init();

    void start();
    void addGameObject(std::unique_ptr<GameObject> gameObject);

    virtual void update(float dt) = 0;

    Camera& getCamera();
    void sceneImgui();
    virtual void imgui();
};
