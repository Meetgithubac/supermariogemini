#include "TextureManager.hpp"
#include <iostream>

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename))
    {
        std::string error_msg = "Failed to load texture: " + filename;
        std::cerr << error_msg << std::endl;
        throw std::runtime_error(error_msg);
    }
    m_textures[name] = texture;
}

sf::Texture& TextureManager::getTexture(const std::string& name)
{
    try
    {
        return m_textures.at(name);
    }
    catch (const std::out_of_range& e)
    {
        std::string error_msg = "Texture not found: " + name + ". Error: " + e.what();
        std::cerr << error_msg << std::endl;
        throw std::runtime_error(error_msg);
    }
}