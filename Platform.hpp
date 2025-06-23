// Source/Entities/Platform/Platform.hpp

#pragma once

#include <SFML/Graphics.hpp>

// What it does: Represents a static platform or ground in the game.
// Why it's used: Provides a solid surface for the player to stand on and collide with.
// How it works: Essentially a drawable rectangle with a position and size.
class Platform
{
public:
    // What it does: Constructor for the Platform class.
    // Why it's used: Initializes the platform's position, size, and visual properties.
    // How it works: Takes position and size vectors, sets color.
    Platform(sf::Vector2f position, sf::Vector2f size);

    // What it does: Draws the platform onto the provided render window.
    // Why it's used: To make the platform visible in the game.
    // How it works: Draws the internal sf::RectangleShape.
    void render(sf::RenderWindow& window);

    // What it does: Returns the global bounding box of the platform.
    // Why it's used: Essential for collision detection with other game objects (like the player).
    // How it works: Accesses the getGlobalBounds() method of the internal shape.
    sf::FloatRect getGlobalBounds() const;

private:
    // What it does: The visual representation of the platform.
    // Why it's used: What gets drawn on the screen and defines the collision area.
    sf::RectangleShape m_shape;
};