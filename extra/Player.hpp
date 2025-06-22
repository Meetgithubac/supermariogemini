// Source/Player/Player.hpp
/*
#pragma once

#include <SFML/Graphics.hpp> // For sf::RectangleShape, sf::Sprite, sf::Texture, sf::RenderWindow, sf::Vector2f
#include <cmath>             // For std::sqrt (for vector normalization)

class Player
{
public:
    // What it does: Constructor for the Player class.
    // Why it's used: To initialize a new player object with its starting properties.
    // How it works: Takes initial position and size as arguments.
    // Alternatives: Could have a default constructor and separate initialization function.
    Player(sf::Vector2f startPosition, sf::Vector2f size);

    // What it does: Updates the player's state (movement, animation, physics).
    // Why it's used: Called every frame to advance the player's game logic.
    // How it works: Takes deltaTime to ensure frame-rate independent updates.
    // Alternatives: Could take an Input object or event list if input wasn't handled internally.
    void update(sf::Time deltaTime);

    // What it does: Draws the player onto the provided render window.
    // Why it's used: To visually represent the player on screen.
    // How it works: Takes a reference to sf::RenderWindow as it doesn't own the window.
    // Alternatives: Could return a drawable object if the Game class was responsible for actual drawing.
    void render(sf::RenderWindow& window);

    // What it does: Returns the current position of the player.
    // Why it's used: Other objects (like the camera or collision system) will need to know the player's location.
    // How it works: Accesses the position of the underlying sf::RectangleShape.
    sf::Vector2f getPosition() const; // 'const' means this method does not modify the object's state.

    // What it does: Returns the global bounds of the player shape.
    // Why it's used: Essential for collision detection with platforms, enemies, etc.
    // How it works: Accesses the global bounds of the underlying sf::RectangleShape.
    sf::FloatRect getGlobalBounds() const;

private:
    // What it does: The visual representation of the player.
    // Why it's used: This is what gets drawn on the screen.
    // How it works: An sf::RectangleShape object. Will become sf::Sprite later.
    sf::RectangleShape m_shape;

    // What it does: The player's current velocity (direction and magnitude).
    // Why it's used: Used to calculate how far the player moves each frame.
    // How it works: A 2D vector (x, y components).
    sf::Vector2f m_velocity;

    // What it does: The maximum speed the player can move at.
    // Why it's used: A constant to control player movement speed.
    // How it works: A float value.
    float m_movementSpeed;

    // What it does: Handles reading player-specific input (e.g., keyboard presses).
    // Why it's used: Separates input processing logic from the general update logic.
    // How it works: Reads sf::Keyboard::isKeyPressed and sets m_velocity accordingly.
    void handleInput();
};
*/


// Source/Player/Player.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class Player
{
public:
    // What it does: Constructor, now takes a texture reference for the sprite.
    // Why it's used: To initialize the player with its visual texture.
    // How it works: The Game class will pass a texture from its TextureManager.
    // Alternatives: Player could load its own texture, but passing it is more flexible.
    Player(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture);

    void update(sf::Time deltaTime, sf::Vector2u windowSize);
    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

private:
    // REMOVED: sf::RectangleShape m_shape;

    // What it does: The visual representation of the player using an image.
    // Why it's used: To display actual Mario graphics instead of a rectangle.
    // How it works: An sf::Sprite object.
    sf::Sprite m_sprite; // NEW: Replaced sf::RectangleShape

    sf::Vector2f m_velocity;
    float m_movementSpeed;

    void handleInput();
};