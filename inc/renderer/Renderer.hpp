#pragma once

#include "components/SpriteRenderer.hpp"
#include "renderer/RenderBatch.hpp"
#include <vector>
class Renderer
{
    static constexpr size_t MAX_BATCH_SIZE = 1000;

    std::vector<RenderBatch> m_batches;

  public:
    Renderer() = default;

    void add(GameObject* go);
    void add(SpriteRenderer* spr);
    void render();
};
