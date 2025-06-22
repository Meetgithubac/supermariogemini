// Source/Player/Player.cpp

#include "Player.hpp" // Always include your own header first

// What it does: Player class constructor implementation.
// Why it's used: Sets up initial properties of the player object.
// How it works: Initializes member variables using initializer list.
//               Sets shape size, position, color, and defines movement speed.
Player::Player(sf::Vector2f startPosition, sf::Vector2f size)
    : m_shape(size), // Initialize the shape with given size
    m_velocity(0.f, 0.f), // Player starts with no velocity
    m_movementSpeed(200.f) // Define the player's max speed
{
    // What it does: Sets the visual color of the player shape.
    // Why it's used: Makes the player visible on screen.
    // How it works: Calls setFillColor on m_shape.
    m_shape.setFillColor(sf::Color::Green);
    // What it does: Sets the initial position of the player.
    // Why it's used: Places the player at the desired starting point in the game world.
    // How it works: Calls setPosition on m_shape.
    m_shape.setPosition(startPosition);
}

// What it does: Updates the player's game logic each frame.
// Why it's used: Processes input, updates position based on velocity and delta time.
// How it works: Calls handleInput() to determine velocity, then updates shape position.
void Player::update(sf::Time deltaTime)
{
    // What it does: Determines the player's desired velocity based on current input.
    // Why it's used: Separates input reading logic from movement application.
    handleInput();

    // What it does: Calculates the distance to move this frame.
    // Why it's used: Ensures movement is consistent regardless of frame rate.
    // How it works: Multiplies velocity (normalized direction) by speed and delta time.
    // Alternatives: Could apply a direct force for more complex physics.
    m_shape.move(m_velocity * m_movementSpeed * deltaTime.asSeconds());
}

// What it does: Draws the player's visual representation to the window.
// Why it's used: To display the player on the screen.
// How it works: Calls the draw() method of the SFML window, passing the player's shape.
void Player::render(sf::RenderWindow& window)
{
    window.draw(m_shape);
}

// What it does: Returns the current position of the player's shape.
// Why it's used: Allows other parts of the game (e.g., camera, collision) to query player position.
// How it works: Accesses the position property of m_shape.
sf::Vector2f Player::getPosition() const
{
    return m_shape.getPosition();
}

// What it does: Returns the global bounding box of the player's shape.
// Why it's used: Crucial for accurate collision detection.
// How it works: Accesses the global bounds property of m_shape.
sf::FloatRect Player::getGlobalBounds() const
{
    return m_shape.getGlobalBounds();
}

// What it does: Implements the player's specific input handling.
// Why it's used: Determines the desired movement direction based on keyboard presses.
// How it works: Reads keyboard state and sets m_velocity (a normalized vector).
void Player::handleInput()
{
    // What it does: Resets velocity each frame.
    // Why it's used: Ensures that if no keys are pressed, player stops.
    // How it works: Sets both x and y components to 0.
    m_velocity = sf::Vector2f(0.f, 0.f);

    // What it does: Checks for 'A' key press for left movement.
    // Why it's used: To set the X component of velocity for left movement.
    // How it works: If key is pressed, sets x velocity to -1.f.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    {
        m_velocity.x -= 1.f;
    }
    // What it does: Checks for 'D' key press for right movement.
    // Why it's used: To set the X component of velocity for right movement.
    // How it works: If key is pressed, sets x velocity to +1.f.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    {
        m_velocity.x += 1.f;
    }
    // What it does: Checks for 'W' key press for up movement.
    // Why it's used: To set the Y component of velocity for up movement.
    // How it works: If key is pressed, sets y velocity to -1.f (SFML Y-axis is inverted).
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
    {
        m_velocity.y -= 1.f;
    }
    // What it does: Checks for 'S' key press for down movement.
    // Why it's used: To set the Y component of velocity for down movement.
    // How it works: If key is pressed, sets y velocity to +1.f.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
    {
        m_velocity.y += 1.f;
    }

    // What it does: Normalizes the velocity vector if there's any diagonal movement.
    // Why it's used: Ensures consistent movement speed in all directions (prevents faster diagonal movement).
    // How it works: If the vector has a length greater than 0, it divides each component by its length.
    if (m_velocity.x != 0.f || m_velocity.y != 0.f)
    {
        float length = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
        if (length > 0.f) // Avoid division by zero
        {
            m_velocity.x /= length;
            m_velocity.y /= length;
        }
    }
}