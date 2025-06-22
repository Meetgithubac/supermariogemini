// Source/Game/Game.hpp
/*
// What it does: Ensures this header file is included only once per compilation unit.
// Why it's used: Prevents redefinition errors and speeds up compilation.
// How it works: A non-standard but widely supported directive. Alternatives are #ifndef/#define/#endif guards.
#pragma once

// What it does: Includes the SFML Graphics module.
// Why it's used: Provides access to sf::RenderWindow, sf::Color, sf::RectangleShape, sf::Sprite, sf::Texture etc.
// How it works: Makes all declarations from SFML/Graphics.hpp available.
// Alternatives: Could forward declare sf::RenderWindow, but for the Game class, we'll likely need many graphics elements.
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player/Player.hpp" // NEW: Include the Player class header


// What it does: Defines the Game class.
// Why it's used: Encapsulates all core game logic, window management, and the main game loop.
// How it works: Declares member variables (attributes) and member functions (methods) of the game.
class Game
{
public: // Public members are accessible from outside the class.

    // What it does: Constructor for the Game class.
    // Why it's used: Initializes the game object when it's created.
    // How it works: Called automatically when a Game object is instantiated.
    // Alternatives: Can take parameters for window size, title etc.
    Game();

    // What it does: Runs the main game loop.
    // Why it's used: This is the primary function that starts and manages the game's execution.
    // How it works: Contains the while(window.isOpen()) loop, calls update and render.
    // Alternatives: Could be broken into smaller functions, but "run" is a common entry point.
    void run();

private: // Private members are only accessible from within the class itself.

    // What it does: Represents the game window.
    // Why it's used: All drawing operations are performed on this window.
    // How it works: An instance of sf::RenderWindow. It's a member so all game methods can access it.
    // Alternatives: Could be passed around as a pointer/reference, but owning it as a member is standard.
    sf::RenderWindow m_window; // Member variable prefix 'm_' is a common convention

    // What it does: Measures time between frames.
    // Why it's used: To calculate delta time for frame-rate independent movement.
    // How it works: An instance of sf::Clock.
    // Alternatives: None within SFML.
    sf::Clock m_clock;

    // What it does: A simple player rectangle for testing movement.
    // Why it's used: To demonstrate game logic and rendering within the Game class.
    // How it works: An instance of sf::RectangleShape.
    // Alternatives: Will eventually be replaced by a proper Player class.
    sf::RectangleShape m_player;

    // What it does: Speed of the player in pixels per second.
    // Why it's used: Constant for controlling player movement speed.
    // How it works: A float variable.
    float m_playerSpeed;

    // What it does: Processes events (input, window events) for a single frame.
    // Why it's used: Separates event handling logic from the main loop.
    // How it works: Iterates through sf::Event queue.
    // Alternatives: Could be integrated directly into run(), but separation improves readability.
    void processEvents();

    // What it does: Updates the game state based on elapsed time (deltaTime).
    // Why it's used: Contains all game logic (movement, physics, AI, animations).
    // How it works: Takes sf::Time deltaTime as input to ensure frame-rate independence.
    // Alternatives: Could use a fixed update step, but variable is simpler for now.
    void update(sf::Time deltaTime);

    // What it does: Draws all game objects to the window.
    // Why it's used: Handles all rendering operations.
    // How it works: Clears the window, draws objects, and displays the frame.
    // Alternatives: Could pass sf::RenderWindow to individual objects for them to draw themselves.
    void render();
};
*/



//updated one


// Source/Game/Game.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player/Player.hpp" // NEW: Include the Player class header

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;

    // REMOVED: sf::RectangleShape m_player;
    // REMOVED: float m_playerSpeed;

    // What it does: An instance of our new Player class.
    // Why it's used: The Game class now owns and manages the player object.
    // How it works: A member variable of type Player.
    Player m_player; // NEW: Member variable of type Player

    float m_backgroundColorValue;
    bool m_colorIncreasing;
    bool m_isPaused; // From Challenge 2, Session 3

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
};