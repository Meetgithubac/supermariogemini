// Source/Main.cpp

// What it does: Includes the necessary SFML header for creating a window and handling events.
// Why it's used: This header provides the sf::RenderWindow class and event handling mechanisms.
// How it works: It brings the declarations of SFML window-related functionalities into our scope.
// Alternatives: None for SFML window creation. You'd use different headers for different libraries (e.g., GLFW, SDL).
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"

int main()
{
   /*
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Super Mario Clone", sf::Style::Close | sf::Style::Resize);

    window.setVerticalSyncEnabled(false);

	window.setFramerateLimit(60);   // setting maximum frame rate to 60 FPS. for all devices.
	sf::Clock clock;    // Declare a clock outside the loop
 

    // game objects and demonstrations.
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f)); // 50x50 pixels
    player.setFillColor(sf::Color::Green);
    player.setPosition({ 100.f, 100.f });
    float playerSpeed = 200.f; // Pixels per second

    while (window.isOpen())
    {
		sf::Time deltaTime = clock.restart();   //measure dt and restart clock.(measures the time since the last restart() call / or last frame)
        std::cout << "Delta Time (sec): " << deltaTime.asSeconds() << std::endl;

        while (const std::optional event = window.pollEvent())
        {
           
            if (event->is <sf::Event::Closed>())
            {
                window.close();
            }
         
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                std::cout << "new width: " << resized->size.x << std::endl;
                std::cout << "new height: " << resized->size.y << std::endl;
                sf::FloatRect visibleArea({ 0, 0 }, { static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) });
                    window.setView(sf::View(visibleArea));
            }

        }

        // keyboard handling.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
        {
            // What it does: Moves the player rectangle to the right.
            /* How it works : playerSpeed is in pixels / second.deltaTime.asSeconds() provides the time in seconds.
                                 Multiplying them gives the distance to move this frame: pixels/second * seconds = pixels.
            */ 
     /*       player.move({playerSpeed * deltaTime.asSeconds(), 0.f}); // Move right
        }
        // What it does: Checks if the 'A' key is currently pressed.
        // Why it's used: To control player movement to the left.
        // How it works: Similar to 'D' key check, but moves in the negative X direction.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
        {
            player.move({ -playerSpeed * deltaTime.asSeconds(), 0.f }); // Move left
        }
        // What it does: Checks if the 'W' key is currently pressed.
        // Why it's used: To control player movement upwards.
        // How it works: Similar, but moves in the negative Y direction (Y increases downwards in SFML).
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
        {
            player.move({ 0.f, -playerSpeed * deltaTime.asSeconds() }); // Move up
        }
        // What it does: Checks if the 'S' key is currently pressed.
        // Why it's used: To control player movement downwards.
        // How it works: Similar, but moves in the positive Y direction.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
        {
            player.move({ 0.f, playerSpeed * deltaTime.asSeconds() }); // Move down
        }
        */

        /*
            // practice challange.
             // --- 1. Input Handling & Update (Game Logic) combined for simple movement ---
            // Determine movement direction based on key presses
            sf::Vector2f movement(0.f, 0.f); // Stores the desired movement vector for this frame

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
            {
                movement.x -= 1.f; // Move left
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
            {
                movement.x += 1.f; // Move right
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
            {
                movement.y -= 1.f; // Move up
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
            {
                movement.y += 1.f; // Move down
            }

            if (movement.x != 0.f || movement.y != 0.f)
            {
           
                float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
                if (length > 0.f) // Avoid division by zero if movement is (0,0)
                {
                    movement.x /= length;
                    movement.y /= length;
                }
            }

       
            player.move({ movement * playerSpeed * deltaTime.asSeconds() });
        */

		//2--------- update the game objects.


		//3--------- render the game objects.
    /*    window.clear(sf::Color(0, 100, 200)); // A nice dark blue color

		window.draw(player); // Draw the player rectangle
        
        window.display();
    }

  
        return 0;
    */
    // What it does: Creates an instance of our Game class.
      // Why it's used: This object encapsulates our entire game.
      // How it works: Calls the Game class constructor.
Game game;

// What it does: Starts the main game loop.
// Why it's used: Begins the continuous update and rendering of the game.
// How it works: Calls the public run() method of our game object.

game.run();

// What it does: Indicates successful program termination.
// Why it's used: Standard practice for main functions.
return 0;
}

// session-5 finished