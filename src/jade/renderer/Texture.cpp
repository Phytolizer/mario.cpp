#include "jade/renderer/Texture.hpp"
#include <fmt/format.h>
#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>
#include <stdexcept>

Texture::Texture(std::string_view filePath) : m_filePath(filePath)
{
    // Generate texture on GPU
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    // Set texture parameters
    // Repeat image in both directions
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // When stretching the image, pixelate
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // When shrinking the image, pixelate
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load image data
    int width;
    int height;
    int nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(m_filePath.c_str(), &width, &height, &nrChannels, 0);
    if (image == nullptr)
    {
        std::string message = fmt::format("Error: Failed to load image '{}'", m_filePath);
        throw std::runtime_error{message};
    }
    m_width = width;
    m_height = height;

    // Set texture data
    GLenum format;
    switch (nrChannels)
    {
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        std::cerr << "ERROR: '" << m_filePath << "'\n\nUnsupported image format.\n";
        return;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::string_view Texture::getFilePath() const
{
    return m_filePath;
}

int Texture::getWidth() const
{
    return m_width;
}

int Texture::getHeight() const
{
    return m_height;
}
