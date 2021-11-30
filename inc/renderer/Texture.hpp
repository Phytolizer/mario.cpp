#pragma once

#include <string_view>
class Texture
{
    std::string m_filePath;
    unsigned int m_textureId;
    int m_width;
    int m_height;

  public:
    explicit Texture(std::string_view filePath);

    void bind();
    void unbind();
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
};
