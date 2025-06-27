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
    //sf::Texture texture;
    // Create a new texture on the heap using a smart pointer
    auto texture = std::make_unique<sf::Texture>();

    if (!texture->loadFromFile(filename))
    {
        std::string error_msg = "Failed to load texture: " + filename;
        std::cerr << error_msg << std::endl;
        throw std::runtime_error(error_msg);
    }
    m_textures[name] = std::move(texture);
}

sf::Texture& TextureManager::getTexture(const std::string& name)
{
    try
    {
        //return m_textures.at(name);
        // Get the unique_ptr and then dereference it to return a reference
        return *m_textures.at(name);
    }
    catch (const std::out_of_range& e)
    {
        std::string error_msg = "Texture not found: " + name + ". Error: " + e.what();
        std::cerr << error_msg << std::endl;
        throw std::runtime_error(error_msg);
    }
}