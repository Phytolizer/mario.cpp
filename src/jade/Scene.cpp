#include "jade/Scene.hpp"
#include <imgui.h>

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
        m_renderer.add(go.get());
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
        m_renderer.add(m_gameObjects.back().get());
    }
}

Camera& Scene::getCamera()
{
    return m_camera;
}

void Scene::sceneImgui()
{
    if (activeGameObject != nullptr)
    {
        ImGui::Begin("Inspector");
        activeGameObject->imgui();
        ImGui::End();
    }

    imgui();
}

void Scene::imgui()
{
}
