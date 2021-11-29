#pragma once

#include "renderer/Shader.hpp"
#include <components/SpriteRenderer.hpp>
#include <vector>

class RenderBatch
{
    static constexpr size_t POS_SIZE = 2;
    static constexpr size_t COLOR_SIZE = 4;
    static constexpr size_t POS_OFFSET = 0;
    static constexpr size_t COLOR_OFFSET = POS_OFFSET + POS_SIZE * sizeof(float);
    static constexpr size_t VERTEX_SIZE = POS_SIZE + COLOR_SIZE;
    static constexpr size_t VERTEX_SIZE_BYTES = VERTEX_SIZE * sizeof(float);

    std::vector<SpriteRenderer*> m_sprites;
    size_t m_numSprites;
    bool m_hasRoom;
    std::vector<float> m_vertices;

    unsigned int m_vaoId;
    unsigned int m_vboId;
    size_t m_maxBatchSize;
    Shader m_shader;

    std::vector<unsigned int> generateIndices();
    void loadElementIndices(std::vector<unsigned int>* elements, size_t index);
    void loadVertexProperties(size_t index);

  public:
    explicit RenderBatch(size_t maxBatchSize);

    void start();
    void addSprite(SpriteRenderer* sprite);
    void render();
    bool hasRoom() const;
};
