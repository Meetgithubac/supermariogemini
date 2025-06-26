#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Player;
class Coin;

class Block
{
public:
    Block(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture);
    virtual ~Block() = default;

    virtual void update(sf::Time deltaTime);
    virtual void render(sf::RenderWindow& window);
    virtual sf::FloatRect getGlobalBounds() const;

    virtual void checkPlayerCollision(Player& player, std::vector<std::unique_ptr<Coin>>& coins, int& score);

protected:
    sf::Sprite m_sprite;
    bool m_isHit;
    sf::Clock m_hitTimer;
    sf::Time m_hitDuration;
};