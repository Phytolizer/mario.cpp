#include "renderer/RenderBatch.hpp"

#include <glad/glad.h>

#include <jade/Window.hpp>

std::vector<unsigned int> RenderBatch::generateIndices()
{
    // 6 indices per quad (3 per triangle)
    std::vector<unsigned int> elements(6 * m_maxBatchSize);
    for (size_t i = 0; i < m_maxBatchSize; i++)
    {
        loadElementIndices(&elements, i);
    }
    return elements;
}

void RenderBatch::loadElementIndices(std::vector<unsigned int>* elements, size_t index)
{
    size_t offsetArrayIndex = 6 * index;
    size_t offset = 4 * index;

    // Triangle 1
    elements->at(offsetArrayIndex + 0) = offset + 3;
    elements->at(offsetArrayIndex + 1) = offset + 2;
    elements->at(offsetArrayIndex + 2) = offset + 0;

    // Triangle 2
    elements->at(offsetArrayIndex + 3) = offset + 0;
    elements->at(offsetArrayIndex + 4) = offset + 2;
    elements->at(offsetArrayIndex + 5) = offset + 1;
}

void RenderBatch::loadVertexProperties(size_t index)
{
    SpriteRenderer* sprite = m_sprites.at(index);

    // Find offset within array (4 vertices per sprite)
    size_t offset = 4 * index * VERTEX_SIZE;

    glm::vec4 color = sprite->getColor();
    std::vector<glm::vec2> texCoords = sprite->getTexCoords();
    size_t texId = 0;
    if (sprite->getTexture() != nullptr)
    {
        for (size_t i = 0; i < m_textures.size(); ++i)
        {
            if (m_textures[i] == sprite->getTexture())
            {
                // 0 is reserved
                texId = i + 1;
                break;
            }
        }
    }
    // Add vertices with the appropriate properties
    float xAdd = 1.0F;
    float yAdd = 1.0F;
    for (size_t i = 0; i < 4; ++i)
    {
        switch (i)
        {
        case 1:
            yAdd = 0.0F;
            break;
        case 2:
            xAdd = 0.0F;
            break;
        case 3:
            yAdd = 1.0F;
            break;
        default:
            break;
        }

        // Load position
        m_vertices[offset] = sprite->gameObject->transform.position.x + (xAdd * sprite->gameObject->transform.scale.x);
        m_vertices[offset + 1] =
            sprite->gameObject->transform.position.y + (yAdd * sprite->gameObject->transform.scale.y);

        // Load color
        m_vertices[offset + 2] = color.r;
        m_vertices[offset + 3] = color.g;
        m_vertices[offset + 4] = color.b;
        m_vertices[offset + 5] = color.a;

        // Load texture coordinates
        m_vertices[offset + 6] = texCoords[i].x;
        m_vertices[offset + 7] = texCoords[i].y;

        // Load texture id
        m_vertices[offset + 8] = texId;

        offset += VERTEX_SIZE;
    }
}

RenderBatch::RenderBatch(size_t maxBatchSize)
    : m_numSprites(0), m_hasRoom(true), m_maxBatchSize(maxBatchSize), m_shader("res/shaders/default.glsl")
{
    m_sprites.resize(maxBatchSize);
    m_vertices.resize(maxBatchSize * 4 * VERTEX_SIZE, 0.0F);
    m_shader.compile();
}

void RenderBatch::start()
{
    // Generate and bind VAO
    glGenVertexArrays(1, &m_vaoId);
    glBindVertexArray(m_vaoId);

    // Allocate space for vertices
    glGenBuffers(1, &m_vboId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboId);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_DYNAMIC_DRAW);

    //  Create and upload index buffer
    unsigned int eboId;
    glGenBuffers(1, &eboId);
    std::vector<unsigned int> indices = generateIndices();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)POS_OFFSET);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)COLOR_OFFSET);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, TEX_COORDS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)TEX_COORDS_OFFSET);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, TEX_ID_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE_BYTES, (void*)TEX_ID_OFFSET);
    glEnableVertexAttribArray(3);
}

void RenderBatch::addSprite(SpriteRenderer* sprite)
{
    // Get index and add render object
    size_t index = m_numSprites;
    m_sprites[index] = sprite;
    ++m_numSprites;

    if (sprite->getTexture() != nullptr &&
        std::find(m_textures.begin(), m_textures.end(), sprite->getTexture()) == m_textures.end())
    {
        m_textures.push_back(sprite->getTexture());
    }

    // Add properties to local vertices array
    loadVertexProperties(index);
    if (m_numSprites >= m_maxBatchSize)
    {
        m_hasRoom = false;
    }
}

void RenderBatch::render()
{
    // For now, rebuffer all data each frame
    glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(float), m_vertices.data());

    // Use shader
    m_shader.use();
    m_shader.uploadMat4("uProjection", Window::getScene().getCamera().getProjectionMatrix());
    m_shader.uploadMat4("uView", Window::getScene().getCamera().getViewMatrix());
    for (size_t i = 0; i < m_textures.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i + 1);
        m_textures[i]->bind();
    }
    m_shader.uploadIntArray("uTextures", m_texSlots);

    glBindVertexArray(m_vaoId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, m_numSprites * 6, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    for (const auto& texture : m_textures)
    {
        texture->unbind();
    }
    m_shader.detach();
}

bool RenderBatch::hasRoom() const
{
    return m_hasRoom;
}

bool RenderBatch::hasTextureRoom() const
{
    return m_textures.size() < 8;
}

bool RenderBatch::hasTexture(Texture* tex) const
{
    return std::find(m_textures.begin(), m_textures.end(), tex) != m_textures.end();
}
