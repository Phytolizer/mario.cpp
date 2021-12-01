#include "renderer/Renderer.hpp"
#include <algorithm>
#include <jade/ComponentClass.hpp>
#include <jade/GameObject.hpp>

void Renderer::add(GameObject* go)
{
    if (auto* spr = go->getComponent<SpriteRenderer>(ComponentClass::SPRITE_RENDERER); spr != nullptr)
    {
        add(spr);
    }
}

void Renderer::add(SpriteRenderer* spr)
{
    bool added = false;
    for (auto& batch : m_batches)
    {
        if (batch.hasRoom() && batch.zIndex() == spr->gameObject->zIndex())
        {
            if (Texture* tex = spr->getTexture(); tex == nullptr || batch.hasTexture(tex) || batch.hasTextureRoom())
            {
                batch.addSprite(spr);
                added = true;
                break;
            }
        }
    }
    if (!added)
    {
        m_batches.emplace_back(RenderBatch{MAX_BATCH_SIZE, spr->gameObject->zIndex()});
        m_batches.back().start();
        m_batches.back().addSprite(spr);
        std::sort(m_batches.begin(), m_batches.end(),
                  [](const RenderBatch& a, const RenderBatch& b) { return a.zIndex() < b.zIndex(); });
    }
}

void Renderer::render()
{
    for (auto& batch : m_batches)
    {
        batch.render();
    }
}
