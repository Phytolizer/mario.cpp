#pragma once

#include <string_view>
class Texture
{
    std::string m_filePath;
    unsigned int m_textureId;

  public:
    explicit Texture(std::string_view filePath);

    void bind();
    void unbind();
};
