// Source/Resources/TextureManager.cpp

#include "TextureManager.hpp"

// What it does: Loads a texture if not already loaded, then returns a reference to it.
// Why it's used: Centralizes texture loading and ensures textures are loaded only once.
// How it works: Checks if ID exists in map; if not, creates a new texture, loads from file, stores in map.
std::unique_ptr<sf::Texture>& TextureManager::loadTexture(const std::string& id, const std::string& filePath)
{
    // What it does: Checks if a texture with the given ID already exists in the map.
    // Why it's used: To prevent redundant loading.
    if (m_textures.find(id) == m_textures.end())
    {
        // What it does: Creates a new unique_ptr for an sf::Texture.
        // Why it's used: Manages the lifetime of the texture object automatically.
        auto newTexture = std::make_unique<sf::Texture>();
        // What it does: Attempts to load the texture from the specified file path.
        // Why it's used: Reads the image data into the texture.
        // How it works: Calls SFML's loadFromFile method.
        if (!newTexture->loadFromFile(filePath))
        {
            // What it does: Prints an error message if texture loading fails.
            // Why it's used: Essential for debugging asset loading issues.
            std::cerr << "Error: Could not load texture from " << filePath << std::endl;
            // What it does: Throws a runtime error.
            // Why it's used: To immediately stop execution if a critical asset is missing.
            // Alternatives: Return a default "missing texture" texture, but crashing is often better for development.
            throw std::runtime_error("Failed to load texture: " + filePath);
        }
        // What it does: Inserts the new texture into the map.
        // Why it's used: To store the loaded texture for future retrieval.
        // How it works: Uses emplace to construct the unique_ptr in place.
        m_textures.emplace(id, std::move(newTexture)); // std::move transfers ownership
    }
    // What it does: Returns a reference to the unique_ptr associated with the given ID.
    // Why it's used: To provide access to the loaded texture.
    return m_textures.at(id);
}

// What it does: Retrieves a reference to a previously loaded texture.
// Why it's used: To get a texture object by its ID without exposing unique_ptr.
// How it works: Uses map.at() to get the unique_ptr, then dereferences it (*).
sf::Texture& TextureManager::getTexture(const std::string& id)
{
    // What it does: Returns a reference to the Texture object itself.
    // Why it's used: This is the actual SFML texture object needed by sf::Sprite.
    // How it works: m_textures.at(id) gets the unique_ptr, then * dereferences it to the sf::Texture object.
    if (m_textures.find(id) != m_textures.end())
    {
        return *m_textures.at(id);
    }
}

// What it does: Clears all textures from the manager.
// Why it's used: For memory cleanup.
// How it works: Clears the std::map; unique_ptr automatically deallocate the textures.
void TextureManager::clear()
{
    m_textures.clear();
}