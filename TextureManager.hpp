// Source/Resources/TextureManager.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include <map>    // For std::map to store textures
#include <string> // For std::string as map key
#include <iostream> // For error messages

// What it does: A simple class to load and store SFML textures.
// Why it's used: Prevents loading the same texture multiple times, centralizes asset paths.
// How it works: Uses a std::map to store unique_ptr to textures, mapped by string IDs.
// Alternatives: Full-fledged ResourceManager, singleton pattern. We start simple.
class TextureManager
{
public:
    // What it does: Loads a texture from a file and stores it.
    // Why it's used: To make textures available to game objects.
    // How it works: Takes a string ID (key for map) and file path.
    //               Uses std::unique_ptr for automatic memory management.
    // Alternatives: Could return a raw pointer or reference, but unique_ptr is safer for ownership.
    std::unique_ptr<sf::Texture>& loadTexture(const std::string& id, const std::string& filePath);

    // What it does: Returns a reference to a loaded texture.
    // Why it's used: To retrieve textures by their ID for use in sprites.
    // How it works: Looks up the texture in the map by ID. Throws an exception if not found.
    // Alternatives: Could return a pointer and check for nullptr. References are generally safer if existence is guaranteed.
    sf::Texture& getTexture(const std::string& id);

    // What it does: Removes all loaded textures.
    // Why it's used: Cleans up memory, useful when changing levels or shutting down.
    // How it works: Clears the internal map. unique_ptr automatically deallocates.
    void clear();

private:
    // What it does: Stores all loaded textures.
    // Why it's used: Allows efficient lookup and prevents redundant loading.
    // How it works: Maps a string ID to a unique_ptr owning an sf::Texture.
    // Alternatives: Raw pointers, shared_ptr, custom allocators. unique_ptr ensures clear ownership.
    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};