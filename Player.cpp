// Source/Player/Player.cpp
/*
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
*/


/*          Session-5 starts here.         ------------------ 
// Source/Player/Player.cpp

#include "Player.hpp"

// What it does: Player class constructor implementation. Now takes a texture.
// Why it's used: Initializes player with its visual texture and other properties.
// How it works: Sets the texture for m_sprite, sets its position, and scale.
Player::Player(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture)
    :m_sprite(texture), // Initialize m_sprite                                                      // error occured.
    m_velocity(0.f, 0.f),
    m_movementSpeed(200.f)
{
    // What it does: Associates the loaded texture with the sprite.
    // Why it's used: The sprite needs to know what image data to draw.
    // How it works: Calls setTexture() on the m_sprite object.
    m_sprite.setTexture(texture);
    
    // What it does: Sets the source rectangle for the sprite.
    // Why it's used: If the texture is a sprite sheet, this specifies which part of the image to display.
    //               For a single image, it just shows the whole image. For Mario, this will be crucial for animation.
    // How it works: sf::IntRect(left, top, width, height). Assuming 16x32 pixel Mario.
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 32 })); // Adjust based on your actual sprite size

    // What it does: Scales the sprite to match the desired visual size.
    // Why it's used: Original NES sprites might be too small for modern screens.
    //               We want our 16x32 sprite to appear as 50x50 on screen for now.
    // How it works: Divides target size by original texture rect size.
    float scaleX = size.x / m_sprite.getGlobalBounds().size.x;
    float scaleY = size.y / m_sprite.getGlobalBounds().size.y;
    m_sprite.setScale({ scaleX, scaleY });

    // What it does: Sets the initial position of the player's sprite.
    // Why it's used: Places the player at its starting point.
    // How it works: Calls setPosition() on m_sprite.
    m_sprite.setPosition(startPosition);
}

void Player::update(sf::Time deltaTime, sf::Vector2u windowSize)
{
    handleInput();
    // What it does: Moves the sprite based on calculated velocity and delta time.
    // Why it's used: Updates the visual position of the player.
    // How it works: Calls move() on m_sprite.
    m_sprite.move(m_velocity * m_movementSpeed * deltaTime.asSeconds());

    // --- Boundary Checks (modified to use m_sprite's properties) ---
    sf::Vector2f playerPos = m_sprite.getPosition();
    sf::Vector2f playerSize = sf::Vector2f(m_sprite.getGlobalBounds().size.x, m_sprite.getGlobalBounds().size.y); // Get actual scaled size

    if (playerPos.x < 0) { m_sprite.setPosition({ 0, playerPos.y }); }
    else if (playerPos.x + playerSize.x > windowSize.x) { m_sprite.setPosition({ windowSize.x - playerSize.x, playerPos.y }); }

    if (playerPos.y < 0) { m_sprite.setPosition({playerPos.x, 0}); }
    else if (playerPos.y + playerSize.y > windowSize.y) { m_sprite.setPosition({ playerPos.x, windowSize.y - playerSize.y }); }
}

void Player::render(sf::RenderWindow& window)
{
    // What it does: Draws the player's sprite onto the window.
    // Why it's used: To display the textured player.
    // How it works: Calls window.draw() with m_sprite.
    window.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const
{
    // What it does: Returns the current position of the sprite.
    // Why it's used: Other objects need player's location.
    return m_sprite.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const
{
    // What it does: Returns the global bounding box of the sprite (after scale).
    // Why it's used: For accurate collision detection.
    return m_sprite.getGlobalBounds();
}

void Player::handleInput()
{
    m_velocity = sf::Vector2f(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) { m_velocity.x -= 1.f; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) { m_velocity.x += 1.f; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) { m_velocity.y -= 1.f; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) { m_velocity.y += 1.f; }

    if (m_velocity.x != 0.f || m_velocity.y != 0.f)
    {
        float length = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
        if (length > 0.f)
        {
            m_velocity.x /= length;
            m_velocity.y /= length;
        }
    }
}

*/
// we have landed upto session5.


// session-6 starts here.----------------


// Source/Player/Player.hpp
/*
// Source/Player/Player.cpp

#include "Player.hpp"
#include <iostream> // For debugging collision

// What it does: Player constructor. Initializes animation variables.
// Why it's used: Sets up the sprite with its texture, scale, and initial animation state.
Player::Player(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture)
    : m_sprite(),
    m_velocity(0.f, 0.f),
    m_movementSpeed(200.f),
    m_currentFrame(0), // Start at the first frame
    m_timePerFrame(sf::seconds(0.1f)), // Each frame lasts 0.1 seconds (10 frames per second)
    m_frameWidth(16), // Assuming your sprite frames are 16 pixels wide
    m_frameHeight(32), // Assuming your sprite frames are 32 pixels high
    m_walkFramesCount(4) // Assuming 4 frames for walking animation
{
    m_sprite.setTexture(texture);
    // What it does: Sets the initial texture rect to the first frame.
    // Why it's used: To display the correct starting animation frame.
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameWidth, m_frameHeight }));

    float scaleX = size.x / m_sprite.getGlobalBounds().size.x;
    float scaleY = size.y / m_sprite.getGlobalBounds().size.y;
    m_sprite.setScale({ scaleX, scaleY });
    m_sprite.setPosition(startPosition);
}

// What it does: Sets the player's position directly.
// Why it's used: Necessary for collision response to "push back" the player.
void Player::setPosition(sf::Vector2f newPos)
{
    m_sprite.setPosition({ newPos });
}

// What it does: Updates player logic, including input, movement, animation, and collisions.
// Why it's used: The main update function called by the Game loop.
// How it works: Orchestrates the various player-specific updates.
void Player::update(sf::Time deltaTime, sf::Vector2u windowSize, const std::vector<Platform*>& platforms) // Modified signature
{
    handleInput();

    // Store old position for collision response
    sf::Vector2f oldPos = m_sprite.getPosition();

    // Apply movement
    m_sprite.move({ m_velocity * m_movementSpeed * deltaTime.asSeconds() });

    // What it does: Updates the animation frame only if the player is moving.
    // Why it's used: To play walking animation.
    // How it works: Checks if velocity is non-zero, then calls updateAnimation().
    if (m_velocity.x != 0.f || m_velocity.y != 0.f)
    {
        updateAnimation();
    }
    else // If not moving, reset to idle frame (first frame)
    {
        m_currentFrame = 0;
        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth, 0 }, { m_frameWidth, m_frameHeight }));
    }


    // --- Boundary Checks ---
    sf::Vector2f playerPos = m_sprite.getPosition();
    sf::Vector2f playerSize = sf::Vector2f(m_sprite.getGlobalBounds().size.x, m_sprite.getGlobalBounds().size.y);

    if (playerPos.x < 0) { m_sprite.setPosition({ 0, playerPos.y }); }
    else if (playerPos.x + playerSize.x > windowSize.x) { m_sprite.setPosition({ windowSize.x - playerSize.x, playerPos.y }); }

    if (playerPos.y < 0) { m_sprite.setPosition({ playerPos.x, 0 }); }
    else if (playerPos.y + playerSize.y > windowSize.y) { m_sprite.setPosition({ playerPos.x, windowSize.y - playerSize.y }); }

    // --- Collision Detection ---
    checkCollisions(platforms); // NEW: Check for platform collisions
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const
{
    return m_sprite.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Player::handleInput()
{
    m_velocity = sf::Vector2f(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode:: A))
    {
        m_velocity.x -= 1.f;
        m_sprite.setOrigin({ m_sprite.getGlobalBounds().size.x, 0.f }); // Flip horizontally for left movement
        m_sprite.setScale({-m_sprite.getScale().x, m_sprite.getScale().y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    {
        m_velocity.x += 1.f;
        m_sprite.setOrigin({ 0.f, 0.f }); // Reset origin
        m_sprite.setScale({ std::abs(m_sprite.getScale().x), m_sprite.getScale().y }); // Ensure scale is positive
    }
    // Vertical movement will be removed when proper gravity and jumping are implemented
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) { m_velocity.y -= 1.f; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) { m_velocity.y += 1.f; }

    if (m_velocity.x != 0.f || m_velocity.y != 0.f)
    {
        float length = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
        if (length > 0.f)
        {
            m_velocity.x /= length;
            m_velocity.y /= length;
        }
    }
}

// What it does: Advances the animation frame based on time.
// Why it's used: To create the illusion of movement/life for the player.
void Player::updateAnimation()
{
    // What it does: Checks if enough time has passed to switch to the next frame.
    // Why it's used: Controls animation speed consistently.
    if (m_animationClock.getElapsedTime() >= m_timePerFrame)
    {
        // What it does: Moves to the next frame.
        m_currentFrame++;
        // What it does: Resets to the first frame if animation sequence ends.
        if (m_currentFrame >= m_walkFramesCount) // If it's the last frame of walk cycle
        {
            m_currentFrame = 0; // Loop back to the first frame
        }
        // What it does: Updates the sprite's texture rectangle to display the new frame.
        // How it works: Calculates the x-offset on the sprite sheet based on currentFrame and frameWidth.
        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth, 0 }, { m_frameWidth, m_frameHeight }));
        // What it does: Resets the animation timer for the next frame.
        m_animationClock.restart();
    }
}

// What it does: Checks for collisions with provided platforms and resolves them.
// Why it's used: To ensure the player stays on platforms and doesn't pass through them.
// How it works: Iterates through platforms, checks intersection, and adjusts player position.
void Player::checkCollisions(const std::vector<Platform*>& platforms)
{
    // What it does: Gets the player's current bounding box.
    // Why it's used: The area to check against platforms.
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();

    // What it does: Iterates through each platform in the provided list.
    // Why it's used: To check for collision with every potential solid surface.
    for (const auto& platform : platforms)
    {
        // What it does: Gets the platform's bounding box.
        // Why it's used: The area to compare with the player's.
        sf::FloatRect platformBounds = platform->getGlobalBounds();

        // What it does: Checks if the player's bounding box intersects with the current platform's bounding box.
        // Why it's used: The core of AABB collision detection.
        if (playerBounds->intersects(platformBounds))
        {
            // What it does: Prints a debug message when a collision occurs.
            // Why it's used: Helpful for verifying collision logic.
            std::cout << "Collision Detected!" << std::endl;

            // Simple collision response: "push back" the player to just outside the platform.
            // This is a very basic response and will be improved with proper physics.

            // Determine which side the collision occurred
            float playerBottom = playerBounds->top + playerBounds.size.y;
            float platformBottom = platformBounds->top + platformBounds.size.y;
            float playerRight = playerBounds.left + playerBounds.size.x;
            float platformRight = platformBounds.left + platformBounds.size.x;

            // Calculate overlap
            float overlapX = std::min({ playerRight, platformRight }) - std::max({ playerBounds->left, platformBounds->left });
            float overlapY = std::min({ playerBottom, platformBottom }) - std::max({ playerBounds->top, platformBounds->top });

            // What it does: Responds to collision based on which axis has the smallest overlap.
            // Why it's used: To determine the primary direction of collision (e.g., hit side vs. hit top).
            // How it works: If X overlap is smaller, it's a horizontal collision; if Y, it's vertical.
            if (overlapX < overlapY) // Horizontal collision (colliding from left/right)
            {
                if (playerRight > platformRight && m_velocity.x < 0) // Moving left, hit platform from right
                {
                    m_sprite.setPosition({ platformBounds.left + platformBounds.size.x, playerBounds.top });
                }
                else if (playerBounds.left < platformBounds.left && m_velocity.x > 0) // Moving right, hit platform from left
                {
                    m_sprite.setPosition({ platformBounds.left - playerBounds.size.y, playerBounds.top });
                }
                m_velocity.x = 0; // Stop horizontal movement
            }
            else // Vertical collision (colliding from top/bottom)
            {
                if (playerBottom > platformBottom && m_velocity.y < 0) // Moving up, hit platform from bottom
                {
                    m_sprite.setPosition({playerBounds.left, platformBounds.top + platformBounds.size.y});
                }
                else if (playerBounds.top < platformBounds.top && m_velocity.y > 0) // Moving down, hit platform from top
                {
                    m_sprite.setPosition({ playerBounds.left, platformBounds.top - playerBounds.size.y });
                    // m_onGround = true; // Will be used for jumping later
                }
                m_velocity.y = 0; // Stop vertical movement
            }
        }
    }
}
*/


//  session-6 starts here--------------------
/*

#include "Player.hpp"
#include "Platform.hpp"
#include <iostream>

Player::Player(const sf::Vector2f& startPosition, const sf::Vector2f& size, const sf::Texture& texture)
    : m_sprite(texture)
{
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameWidth, m_frameHeight }));

    auto bounds = m_sprite.getGlobalBounds();
    m_sprite.setScale({ size.x / bounds.size.x, size.y / bounds.size.y });
    m_sprite.setPosition(startPosition);
}

void Player::setPosition(const sf::Vector2f& newPos)
{
    m_sprite.setPosition(newPos);
}

void Player::update(sf::Time deltaTime, const sf::Vector2u& windowSize, const std::vector<Platform*>& platforms)
{
    handleInput();
    m_sprite.move(m_velocity * m_movementSpeed * deltaTime.asSeconds());

    if (m_velocity.x != 0.f || m_velocity.y != 0.f) {
        updateAnimation();
    }
    else {
        m_currentFrame = 0;
        m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameWidth, m_frameHeight }));
    }

    auto pos = m_sprite.getPosition();
    auto bounds = m_sprite.getGlobalBounds();

    if (pos.x < 0) m_sprite.setPosition({ 0, pos.y });
    if (pos.x + bounds.size.x > windowSize.x) m_sprite.setPosition({ windowSize.x - bounds.size.x, pos.y });
    if (pos.y < 0) m_sprite.setPosition({ pos.x, 0 });
    if (pos.y + bounds.size.y > windowSize.y) m_sprite.setPosition({ pos.x, windowSize.y - bounds.size.y});

    checkCollisions(platforms);
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const { return m_sprite.getPosition(); }
sf::FloatRect Player::getGlobalBounds() const { return m_sprite.getGlobalBounds(); }

void Player::handleInput()
{
    m_velocity = {};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
        m_velocity.x = -1.f;
        m_sprite.setScale({ -std::abs(m_sprite.getScale().x), m_sprite.getScale().y });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
        m_velocity.x = 1.f;
        m_sprite.setScale({std::abs(m_sprite.getScale().x), m_sprite.getScale().y});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
        m_velocity.y = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
        m_velocity.y = 1.f;

    if (m_velocity != sf::Vector2f{ 0.f, 0.f }) {
        float len = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
        m_velocity /= len;
    }
}

void Player::updateAnimation()
{
    if (m_animationClock.getElapsedTime() >= m_timePerFrame) {
        m_currentFrame = (m_currentFrame + 1) % m_walkFramesCount;
        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth, 0 }, { m_frameWidth, m_frameHeight }));
        m_animationClock.restart();
    }
}

void Player::checkCollisions(const std::vector<Platform*>& platforms)
{
    auto pBounds = m_sprite.getGlobalBounds();

    for (auto* plat : platforms) {
        auto lBounds = plat->getGlobalBounds();
        if (pBounds.findIntersection(lBounds)) {
            std::cout << "Collision detected\n";

            float overlapX = std::min({ pBounds.position.x + pBounds.size.x, lBounds.position.x + lBounds.size.x })
                - std::max( pBounds.position.x, lBounds.position.x);
            float overlapY = std::min(pBounds.position.y + pBounds.size.y, lBounds.position.y + lBounds.size.y)
                - std::max(pBounds.position.y, lBounds.position.y);

            if (overlapX < overlapY) {
                if (m_velocity.x > 0) m_sprite.setPosition({ lBounds.position.x - pBounds.size.x, pBounds.position.y});
                else if (m_velocity.x < 0) m_sprite.setPosition({lBounds.position.x + lBounds.size.x, pBounds.position.y});
                m_velocity.x = 0;
            }
            else {
                if (m_velocity.y > 0) m_sprite.setPosition({ pBounds.position.x, lBounds.position.y- pBounds.size.y });
                else if (m_velocity.y < 0) m_sprite.setPosition({ pBounds.position.x , lBounds.position.y+ lBounds.size.y });
                m_velocity.y = 0;
            }
        }
    }
}
*/

// session -6 ends here.--------------------


// Source/Player/Player.cpp

#include "Player.hpp"
#include "Platform.hpp" // Now needed here for Platform type
#include <iostream>

// What it does: Player constructor. Initializes physics variables.
Player::Player(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture)
    : m_sprite(texture),
    m_velocity(0.f, 0.f),
    m_movementSpeed(200.f),
    m_gravity(500.f), // Gravitational acceleration (pixels/second^2)
    m_jumpStrength(-350.f), // Initial jump velocity (negative because Y-axis is inverted for 'up')
    m_onGround(false), // Player starts in the air (or assumes so until collision)
    m_currentFrame(0),
    m_timePerFrame(sf::seconds(0.1f)),
    m_frameWidth(16),
    m_frameHeight(32),
    m_walkFramesCount(4)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameWidth, m_frameHeight }));

    float scaleX = size.x / m_sprite.getGlobalBounds().size.x;
    float scaleY = size.y / m_sprite.getGlobalBounds().size.y;
    m_sprite.setScale({ scaleX, scaleY });
    m_sprite.setPosition(startPosition);
}

void Player::setPosition(sf::Vector2f newPos)
{
    m_sprite.setPosition(newPos);
}

// What it does: Main update loop for the player, incorporating physics.
// Why it's used: Advances player's state each frame.
// How it works: Applies gravity, processes input, moves player, and checks collisions.
void Player::update(sf::Time deltaTime, sf::Vector2u windowSize, const std::vector<Platform*>& platforms)
{
    sf::Vector2f oldPosition = m_sprite.getPosition(); // Store position before any movement

    // What it does: Apply gravity only if the player is not on the ground.
    // Why it's used: Prevents player from continuously accelerating downwards when grounded.
    if (!m_onGround)
    {
        applyGravity(deltaTime);
    }
    // What it does: Reset horizontal velocity, vertical is handled by physics.
    // Why it's used: Ensures player stops moving horizontally when keys are released.
    m_velocity.x = 0.f; // Reset horizontal velocity each frame
    handleInput();      // Update m_velocity based on current input

    // --- Apply Movement (Separate X and Y application for better collision) ---
    // Apply horizontal movement
    m_sprite.move({ m_velocity.x * m_movementSpeed * deltaTime.asSeconds(), 0.f });
    checkCollisions(platforms, oldPosition); // Check and resolve horizontal collisions

    // Apply vertical movement
    m_sprite.move({ 0.f, m_velocity.y * deltaTime.asSeconds() });
    checkCollisions(platforms, oldPosition); // Check and resolve vertical collisions


    // --- Boundary Checks (Still needed after movement and collision) ---
    sf::Vector2f playerPos = m_sprite.getPosition();
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds(); // Use global bounds for accurate scaled size

    if (playerPos.x < 0) { m_sprite.setPosition({ 0, playerPos.y }); m_velocity.x = 0; }
    else if (playerPos.x + playerBounds.size.x > windowSize.x) { m_sprite.setPosition({ windowSize.x - playerBounds.size.x, playerPos.y }); m_velocity.x = 0; }

    if (playerPos.y < 0) { m_sprite.setPosition({ playerPos.x, 0 }); m_velocity.y = 0; } // Ceiling collision
    else if (playerPos.y + playerBounds.size.y > windowSize.y) { // Bottom of window (acting as a giant platform)
        m_sprite.setPosition({ playerPos.x, windowSize.y - playerBounds.size.y });
        m_velocity.y = 0; // Stop falling
        m_onGround = true; // Mark as on ground
    }
    else // If not colliding with window bottom, assume not on ground
    {
        // IMPORTANT: Only set m_onGround to false here IF it's not set true by a platform collision.
        // This is a subtle point. We assume not on ground, but a checkCollisions() might override this.
        // A better approach is to reset m_onGround to false at the start of update(), and only set true during specific *bottom* collisions.
    }


    // --- Animation Update ---
    // What it does: Update animation based on horizontal movement only.
    // Why it's used: To ensure walking animation plays when moving left/right.
    // How it works: If m_velocity.x is non-zero, call updateAnimation(), else reset to idle frame.
    if (m_velocity.x != 0.f)
    {
        updateAnimation();
    }
    else // If not moving horizontally, reset to idle frame
    {
        m_currentFrame = 0; // Assuming frame 0 is idle
        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth, 0 }, { m_frameWidth, m_frameHeight }));
    }
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const
{
    return m_sprite.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Player::handleInput()
{
    // What it does: Sets horizontal velocity based on 'A' and 'D' keys.
    // Why it's used: Controls left/right movement.
    // How it works: Modifies m_velocity.x.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    {
        m_velocity.x = -1.f;
        // Flip sprite for left movement
        m_sprite.setScale({ -std::abs(m_sprite.getScale().x), m_sprite.getScale().y });
        m_sprite.setOrigin({m_sprite.getGlobalBounds().size.x / m_sprite.getScale().x, 0.f}); // Adjust origin for scaling
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    {
        m_velocity.x = 1.f;
        // Reset scale and origin for right movement
        m_sprite.setScale({ std::abs(m_sprite.getScale().x), m_sprite.getScale().y });
        m_sprite.setOrigin({ 0.f, 0.f });
    }
    // REMOVED: Direct vertical control (W/S keys)

    // What it does: Checks for jump input (Spacebar).
    // Why it's used: To initiate a jump.
    // How it works: Calls jump() if 'Space' is pressed and player is on ground.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
    {
        jump();
    }
}

// What it does: Applies gravitational force to the player's vertical velocity.
// Why it's used: Simulates falling.
void Player::applyGravity(sf::Time deltaTime)
{
    // What it does: Increases vertical velocity by gravity * deltaTime.
    // Why it's used: Simulates constant acceleration.
    m_velocity.y += m_gravity * deltaTime.asSeconds();

    // Optional: Implement terminal velocity to cap max fall speed
    // const float TERMINAL_VELOCITY = 500.f;
    // if (m_velocity.y > TERMINAL_VELOCITY) {
    //     m_velocity.y = TERMINAL_VELOCITY;
    // }
}

// What it does: Makes the player jump.
// Why it's used: Initiates an upward movement.
// How it works: Sets vertical velocity to m_jumpStrength and sets m_onGround to false.
void Player::jump()
{
    // What it does: Allows jump only if on ground.
    // Why it's used: Prevents mid-air jumps.
    if (m_onGround)
    {
        m_velocity.y = m_jumpStrength; // Set initial upward velocity
        m_onGround = false; // Player is now in the air
        // std::cout << "Jump!" << std::endl; // Debug
    }
}


// What it does: Advances the animation frame based on time.
void Player::updateAnimation()
{
    if (m_animationClock.getElapsedTime() >= m_timePerFrame)
    {
        m_currentFrame++;
        if (m_currentFrame >= m_walkFramesCount)
        {
            m_currentFrame = 0;
        }
        // What it does: Updates the sprite's texture rectangle.
        // How it works: x-offset based on m_currentFrame, y-offset is 0 for the first row of frames.
        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth , 0 }, { m_frameWidth, m_frameHeight }));
        m_animationClock.restart();
    }
}

// What it does: Checks for collisions with provided platforms and resolves them axis-by-axis.
// Why it's used: To prevent player from passing through platforms.
// How it works: Checks intersections for X and Y separately and adjusts position/velocity.
void Player::checkCollisions(const std::vector<Platform*>& platforms, sf::Vector2f oldPosition)
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();
    m_onGround = false; // Assume not on ground at start of collision check, set true if specific bottom collision occurs.

    for (const auto& platform : platforms)
    {
        sf::FloatRect platformBounds = getGlobalBounds();
        //sf::FloatRect platformBounds = sf::rect::getGlobalBounds(*platform);

        if (playerBounds.findIntersection(platformBounds))
        {
            // std::cout << "Collision Detected!" << std::endl; // Debug

            // Determine previous player position's bounds
            sf::FloatRect oldPlayerBounds(oldPosition, sf::Vector2f(playerBounds.size.x, playerBounds.size.y));

            // Collision from TOP (Player landing on platform)
            // What it does: Checks if player was above platform and is now intersecting from top.
            // Why it's used: To land on platforms.
            // How it works: oldPlayerBounds.top + height was above platform.top, current is below.
            if (oldPlayerBounds.position.y + oldPlayerBounds.size.y <= platformBounds.position.y && m_velocity.y > 0)
            {
                m_sprite.setPosition({ playerBounds.position.x, platformBounds.position.y - playerBounds.size.y }); // Place on top
                m_velocity.y = 0; // Stop vertical movement
                m_onGround = true; // Player is now on the ground
            }
            // Collision from BOTTOM (Player hitting head on platform from below)
            // What it does: Checks if player was below platform and is now intersecting from bottom.
            // Why it's used: To stop player from passing through platforms when jumping.
            // How it works: oldPlayerBounds.top was below platform.top+height, current is above.
            else if (oldPlayerBounds.position.y >= platformBounds.position.y + platformBounds.size.y && m_velocity.y < 0)
            {
                m_sprite.setPosition({ playerBounds.position.x, platformBounds.position.y + platformBounds.size.y }); // Place below
                m_velocity.y = 0; // Stop vertical movement
            }
            // Collision from LEFT/RIGHT (Side collision)
            // What it does: Checks for horizontal collision if not a vertical one.
            // Why it's used: To stop horizontal movement against walls.
            // How it works: oldPlayerBounds.left was to the left/right, now intersecting.
            else
            {
                // If the player's previous right edge was less than or equal to the platform's left edge,
                // and player is moving right, it's a collision from left.
                if (oldPlayerBounds.position.x + oldPlayerBounds.size.x <= platformBounds.position.x && m_velocity.x > 0)
                {
                    m_sprite.setPosition({ platformBounds.position.x - playerBounds.size.x, playerBounds.position.y }); // Push back left
                    m_velocity.x = 0; // Stop horizontal movement
                }
                // If the player's previous left edge was greater than or equal to the platform's right edge,
                // and player is moving left, it's a collision from right.
                else if (oldPlayerBounds.position.x >= platformBounds.position.x + platformBounds.size.x && m_velocity.x < 0)
                {
                    m_sprite.setPosition({ platformBounds.position.x + platformBounds.size.x, playerBounds.position.y }); // Push back right
                    m_velocity.x = 0; // Stop horizontal movement
                }
            }
        }
    }
}