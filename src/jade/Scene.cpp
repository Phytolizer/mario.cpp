#include "jade/Scene.hpp"

Scene::Scene() : m_isRunning(false), m_camera(glm::vec2{})
{
}

void Scene::init()
{
}

void Scene::start()
{
    m_isRunning = true;
    for (auto& go : m_gameObjects)
    {
        go->start();
    }
}

void Scene::addGameObject(std::unique_ptr<GameObject> gameObject)
{
    if (!m_isRunning)
    {
        m_gameObjects.emplace_back(std::move(gameObject));
    }
    else
    {
        m_gameObjects.emplace_back(std::move(gameObject));
        m_gameObjects.back()->start();
    }
}
