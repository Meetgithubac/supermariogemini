#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <stdexcept>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    void loadTexture(const std::string& name, const std::string& filename);
    sf::Texture& getTexture(const std::string& name);

private:
    //std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};