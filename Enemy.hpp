#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Player;

class Enemy
{
public:
    explicit Enemy(sf::Texture& texture);

    virtual ~Enemy() = default; // Pure virtual destructor, define in .cpp

    virtual void update(sf::Time deltaTime, const class TileMap& tilemap) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;

    virtual void checkPlayerCollision(Player& player) = 0;

    virtual bool isAlive() const = 0;

protected:
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;
    float m_movementSpeed;
    bool m_isAlive;
};