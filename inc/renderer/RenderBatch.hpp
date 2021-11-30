#pragma once

#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"
#include <components/SpriteRenderer.hpp>
#include <vector>

class RenderBatch
{
    static constexpr size_t POS_SIZE = 2;
    static constexpr size_t COLOR_SIZE = 4;
    static constexpr size_t TEX_COORDS_SIZE = 2;
    static constexpr size_t TEX_ID_SIZE = 1;
    static constexpr size_t POS_OFFSET = 0;
    static constexpr size_t COLOR_OFFSET = POS_OFFSET + POS_SIZE * sizeof(float);
    static constexpr size_t TEX_COORDS_OFFSET = COLOR_OFFSET + COLOR_SIZE * sizeof(float);
    static constexpr size_t TEX_ID_OFFSET = TEX_COORDS_OFFSET + TEX_COORDS_SIZE * sizeof(float);
    static constexpr size_t VERTEX_SIZE = POS_SIZE + COLOR_SIZE + TEX_COORDS_SIZE + TEX_ID_SIZE;
    static constexpr size_t VERTEX_SIZE_BYTES = VERTEX_SIZE * sizeof(float);

    std::vector<SpriteRenderer*> m_sprites;
    size_t m_numSprites;
    bool m_hasRoom;
    std::vector<float> m_vertices;
    std::vector<int> m_texSlots = {0, 1, 2, 3, 4, 5, 6, 7};

    std::vector<Texture*> m_textures;
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
    [[nodiscard]] bool hasRoom() const;
    [[nodiscard]] bool hasTextureRoom() const;
    [[nodiscard]] bool hasTexture(Texture* tex) const;
};
