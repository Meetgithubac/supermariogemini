

#include <SFML/Graphics.hpp>
#include "Game.hpp"
int main()
{
    try {
        Game game;
        game.run();
    }
    catch (const sf::Exception& e) {
        std::cerr << "SFML Exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Standard Exception: " << e.what() << std::endl;
    }

    return 0;
}