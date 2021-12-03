#include "jade/Scene.hpp"
#include <Level.pb.h>
#include <fstream>
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

void Scene::loadState()
{
    std::ifstream in{"level.pb", std::ios::in | std::ios::binary};
    if (in)
    {
        proto::Level level;
        level.ParseFromIstream(&in);
        for (int i = 0; i < level.gameobjects_size(); ++i)
        {
            m_gameObjects.emplace_back(GameObject::fromSerial(level.gameobjects()[i]));
        }
        m_levelLoaded = true;
    }
}

void Scene::saveState()
{
    proto::Level level;
    for (const auto& go : m_gameObjects)
    {
        proto::GameObject* serial = level.add_gameobjects();
        go->saveState(serial);
    }
    std::ofstream out{"level.pb", std::ios::out | std::ios::trunc | std::ios::binary};
    level.SerializeToOstream(&out);
}
