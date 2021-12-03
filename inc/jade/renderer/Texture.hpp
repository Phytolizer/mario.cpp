#pragma once

#include "Level.pb.h"

#include <string>
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
    [[nodiscard]] std::string_view getFilePath() const;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    static std::unique_ptr<Texture> fromSerial(const proto::Texture& serial);
};
