//#include "Game.hpp"
// Source/Game/Game.cpp


/*
// What it does: Includes the Game class declaration.
// Why it's used: Every .cpp file that implements a class must include its own .hpp file first.
// How it works: Brings the declarations from Game.hpp into this source file.
#include "Game.hpp" // Note: Use quotes for local includes, angle brackets for system/library includes.

// What it does: Constructor implementation for the Game class.
// Why it's used: Initializes member variables when a Game object is created.
// How it works: Uses an initializer list for member variables (more efficient than assignment in constructor body).
//               Sets up the window, player shape, and speed.
Game::Game()
    : m_window(sf::VideoMode({ 800, 600 }), "Super Mario Clone - Session 3", sf::Style::Close | sf::Style::Resize), // Initialize m_window
    m_player(sf::Vector2f(50.f, 50.f)), // Initialize m_player size
    m_playerSpeed(200.f) // Initialize m_playerSpeed
{
    // What it does: Disable vertical synchronization.
    // Why it's used: Allows us to control framerate precisely with setFramerateLimit and rely on delta time.
    // How it works: Calls a method on the m_window object.
    m_window.setVerticalSyncEnabled(false);
    // What it does: Sets the maximum frame rate for the window.
    // Why it's used: To prevent excessive CPU usage and manage rendering speed.
    // How it works: Calls a method on the m_window object.
    m_window.setFramerateLimit(60);

    // What it does: Sets the initial color of the player.
    // Why it's used: To make the player visible.
    // How it works: Calls setFillColor() on the m_player object.
    m_player.setFillColor(sf::Color::Green);
    // What it does: Sets the initial position of the player.
    // Why it's used: Places the player at a starting point on the screen.
    // How it works: Calls setPosition() on the m_player object.
    m_player.setPosition({100.f, 100.f});

    // m_clock doesn't need explicit initialization here; its default constructor is fine.
}

// What it does: Implements the main game loop.
// Why it's used: This function is called to start the game's execution.
// How it works: Contains the while loop that repeatedly calls processEvents(), update(), and render().
void Game::run()
{
    // What it does: Runs as long as the window is open.
    // Why it's used: The core of the game's execution.
    while (m_window.isOpen())
    {
        // What it does: Measures the time elapsed since the last frame and restarts the clock.
        // Why it's used: To obtain delta time for frame-rate independent updates.
        sf::Time deltaTime = m_clock.restart();

        // What it does: Handles all window and input events.
        // Why it's used: Keeps the game responsive to user input and system events.
        // How it works: Calls the private member function processEvents().
        processEvents();
        // What it does: Updates the game state based on delta time.
        // Why it's used: Moves game objects, performs physics, handles AI, etc.
        // How it works: Calls the private member function update(), passing deltaTime.
        update(deltaTime);
        // What it does: Draws all game objects to the screen.
        // Why it's used: Renders the current game state to the user.
        // How it works: Calls the private member function render().
        render();
    }
}

// What it does: Implements the event processing logic.
// Why it's used: To separate event handling from the main loop.
// How it works: Polls SFML events and reacts to them (e.g., window close, resize).
void Game::processEvents()
{
    // What it does: Loops through all pending events.
    // Why it's used: Ensures all events (e.g., multiple key presses, clicks) are processed in one frame.
    while (std::optional event = m_window.pollEvent())
    {
        if (event->is< sf::Event::Closed>())
        {
            m_window.close();
        }
        if (const auto* resized = event->getIf<sf::Event::Resized>())
        {
            // What it does: Adjusts the window's view when resized to prevent distortion.
            // Why it's used: Maintains the correct aspect ratio and scaling of game content.
            // How it works: Creates a new sf::View and applies it to the window.
            sf::FloatRect visibleArea({0, 0}, { static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) });
            m_window.setView(sf::View(visibleArea));
        }
    }
}

// What it does: Implements the game state update logic.
// Why it's used: To change the positions, states, and behaviors of game objects.
// How it works: Takes deltaTime to ensure movement is frame-rate independent.
void Game::update(sf::Time deltaTime)
{
    // --- Player Movement (from Session 2, now inside Game::update) ---
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    {
        movement.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    {
        movement.x += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
    {
        movement.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
    {
        movement.y += 1.f;
    }

    if (movement.x != 0.f || movement.y != 0.f)
    {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        if (length > 0.f)
        {
            movement.x /= length;
            movement.y /= length;
        }
    }
    // What it does: Moves the player object.
    // Why it's used: Applies the calculated movement based on input and delta time.
    // How it works: Calls the move() method of the m_player sf::RectangleShape.
    m_player.move(movement * m_playerSpeed * deltaTime.asSeconds());

    // What it does: Prints the delta time for debugging purposes.
    // Why it's used: To observe frame timing and confirm delta time is working.
    // How it works: Accesses deltaTime's asMilliseconds() method.
    std::cout << "Delta Time (ms): " << deltaTime.asMilliseconds() << std::endl;
}

// What it does: Implements the rendering logic.
// Why it's used: To draw all game objects to the screen.
// How it works: Clears the window, draws objects, and displays the frame.
void Game::render()
{
    // What it does: Clears the window with a specific color.
    // Why it's used: Prepares the window for drawing the new frame.
    // How it works: Calls clear() on the m_window object.
    m_window.clear(sf::Color(0, 100, 200));

    // What it does: Draws the player rectangle to the window.
    // Why it's used: Makes the player visible on screen.
    // How it works: Calls draw() on the m_window object, passing the drawable m_player.
    m_window.draw(m_player);

    // What it does: Presents the drawn frame to the user.
    // Why it's used: Updates the visual display.
    // How it works: Calls display() on the m_window object.
    m_window.display();
}

*/


// updated one

// Source/Game/Game.cpp

#include "Game.hpp" // Always include your own header first

Game::Game()
    : m_window(sf::VideoMode({ 800, 600 }), "Super Mario Clone - Session 4", sf::Style::Close | sf::Style::Resize),
    m_player(sf::Vector2f(100.f, 100.f), sf::Vector2f(50.f, 50.f)), // NEW: Initialize player with start position and size
    m_backgroundColorValue(200.f),
    m_colorIncreasing(false),
    m_isPaused(false)
{
    m_window.setVerticalSyncEnabled(false);
    m_window.setFramerateLimit(60);

    // REMOVED: m_player.setFillColor(sf::Color::Green);
    // REMOVED: m_player.setPosition(100.f, 100.f);
    // REMOVED: m_playerSpeed(200.f); // This is now inside Player class
}

void Game::run()
{
    while (m_window.isOpen())
    {
        sf::Time deltaTime = m_clock.restart();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    while (std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
        if (const auto* resized = event->getIf<sf::Event::Resized>())
        {

            std::cout << "new width: " << resized->size.x << std::endl;
            std::cout << "new height: " << resized->size.y << std::endl;
            sf::FloatRect visibleArea({ 0, 0 }, { static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) });
            m_window.setView(sf::View(visibleArea));
        }
        if (const auto key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->scancode == sf::Keyboard::Scancode::P)
            {
                m_isPaused = !m_isPaused;
                std::cout << "Game " << (m_isPaused ? "PAUSED" : "RESUMED") << std::endl;
            }
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    if (!m_isPaused)
    {
        // What it does: Calls the update method of our Player object.
        // Why it's used: Delegates the player's internal logic updates to the Player class itself.
        // How it works: Passes the deltaTime so the Player can perform frame-rate independent movement.
        m_player.update(deltaTime); // NEW: Delegate update to Player

        // ... (Background color change logic remains here as it's game-level) ...
        const float colorChangeSpeed = 50.f;
        if (m_colorIncreasing) {
            m_backgroundColorValue += colorChangeSpeed * deltaTime.asSeconds();
        }
        else {
            m_backgroundColorValue -= colorChangeSpeed * deltaTime.asSeconds();
        }
        if (m_backgroundColorValue <= 0.f) {
            m_backgroundColorValue = 0.f;
            m_colorIncreasing = true;
        }
        else if (m_backgroundColorValue >= 200.f) {
            m_backgroundColorValue = 200.f;
            m_colorIncreasing = false;
        }
    }

    std::cout << "Delta Time (ms): " << deltaTime.asMilliseconds() << std::endl;
}

void Game::render()
{
    //m_window.clear(sf::Color(0, 0, (sf::Uint8)m_backgroundColorValue));
    m_window.clear(sf::Color(0, 0, static_cast<uint8_t>(m_backgroundColorValue)));


    // What it does: Calls the render method of our Player object.
    // Why it's used: Delegates the player's drawing responsibility to the Player class.
    // How it works: Passes the window by reference so the Player can draw itself onto it.
    m_player.render(m_window); // NEW: Delegate render to Player

    m_window.display();
}