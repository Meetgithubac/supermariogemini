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

/*  session-5 starts-----------------------
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
    //Player() = default; // changed
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
*/

// we have landed upto session5.



// session-6 starts here
// Source/Player/Player.hpp
/*
#pragma once

#include <SFML/Graphics.hpp>
#include <cmath> // For std::sqrt

class Player
{
public:
    Player(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture);

    // What it does: Overloaded update method. Now takes a vector of Platform pointers for collision.
    // Why it's used: Player needs to know about platforms to check for collisions.
    // How it works: Game will pass its vector of platforms.
    void update(sf::Time deltaTime, sf::Vector2u windowSize, const std::vector<Platform*>& platforms); // Modified signature
    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void setPosition(sf::Vector2f newPos); // NEW: Allow external setting of position (useful for collision response)

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;
    float m_movementSpeed;

    // --- Animation Members ---
    // What it does: Stores the current frame of the animation sequence.
    // Why it's used: To know which part of the sprite sheet to display.
    int m_currentFrame;
    // What it does: Tracks time for animation frame advancement.
    // Why it's used: Ensures animation plays at a consistent speed regardless of frame rate.
    sf::Clock m_animationClock;
    // What it does: Time duration each frame should be displayed.
    // Why it's used: Controls the speed of the animation.
    sf::Time m_timePerFrame;
    // What it does: The width of a single animation frame on the sprite sheet.
    // Why it's used: To calculate the x-coordinate for each frame in the sprite sheet.
    int m_frameWidth;
    // What it does: The height of a single animation frame on the sprite sheet.
    // Why it's used: To calculate the y-coordinate for each frame.
    int m_frameHeight;
    // What it does: Total number of frames in the walking animation sequence.
    // Why it's used: To loop the animation correctly.
    int m_walkFramesCount;

    void handleInput();
    // What it does: Updates the player's animation frame.
    // Why it's used: Controls which part of the sprite sheet is currently displayed.
    // How it works: Increments m_currentFrame based on m_animationClock and m_timePerFrame.
    void updateAnimation(); // NEW: For animation logic
    // What it does: Handles collision response with platforms.
    // Why it's used: To prevent player from moving through platforms.
    // How it works: Checks intersection and adjusts player position.
    void checkCollisions(const std::vector<Platform*>& platforms); // NEW: For collision logic
};

*/

// session-6 starts here
/*
#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class Platform; // forward declaration

class Player
{
public:
    Player(const sf::Vector2f& startPosition, const sf::Vector2f& size, const sf::Texture& texture);

    void update(sf::Time deltaTime, const sf::Vector2u& windowSize, const std::vector<Platform*>& platforms);
    void render(sf::RenderTarget& target);

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void setPosition(const sf::Vector2f& newPos);

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;
    float m_movementSpeed{ 200.f };

    int m_currentFrame{ 0 };
    sf::Clock m_animationClock;
    sf::Time m_timePerFrame{ sf::seconds(0.1f) };
    int m_frameWidth{ 16 }, m_frameHeight{ 32 }, m_walkFramesCount{ 4 };

    void handleInput();
    void updateAnimation();
    void checkCollisions(const std::vector<Platform*>& platforms);
};
*/

// session-6 ends here.


// Source/Player/Player.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include <vector> // Required for std::vector in checkCollisions
#include <cmath>  // For std::sqrt

// Forward declaration to avoid circular dependency if Platform needed Player header
class Platform;

class Player
{
public:
    Player(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture);

    void update(sf::Time deltaTime, sf::Vector2u windowSize, const std::vector<Platform*>& platforms);
    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void setPosition(sf::Vector2f newPos);

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;
    float m_movementSpeed;

    // --- Physics and Jump Members ---
    // What it does: The acceleration due to gravity. Positive value pulls down.
    // Why it's used: To simulate the effect of gravity on the player.
    float m_gravity;
    // What it does: The initial upward velocity given when jumping.
    // Why it's used: Determines how high the player can jump.
    float m_jumpStrength;
    // What it does: Flag to check if the player is currently on a solid surface.
    // Why it's used: To control when the player can jump (only from ground) and to stop gravity application when grounded.
    bool m_onGround;

    // --- Animation Members ---
    int m_currentFrame;
    sf::Clock m_animationClock;
    sf::Time m_timePerFrame;
    int m_frameWidth;
    int m_frameHeight;
    int m_walkFramesCount;

    void handleInput();
    void updateAnimation();
    // What it does: Applies gravity to the player's vertical velocity.
    // Why it's used: To simulate falling when in the air.
    void applyGravity(sf::Time deltaTime); // NEW: Function to apply gravity
    // What it does: Performs the jump action.
    // Why it's used: Initiates an upward movement.
    void jump(); // NEW: Function to handle jumping
    // What it does: Refined collision detection and resolution for platforms.
    // Why it's used: To correctly handle player interaction with solid ground/walls.
    // How it works: Separates horizontal and vertical collision checks.
    void checkCollisions(const std::vector<Platform*>& platforms, sf::Vector2f oldPosition); // Modified signature
};