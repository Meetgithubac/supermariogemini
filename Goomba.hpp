#pragma once

#include "Enemy.hpp"
#include <SFML/Graphics.hpp>

class Goomba : public Enemy
{
public:
    Goomba(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture);

    void update(sf::Time deltaTime, const class TileMap& tilemap) override;
    void render(sf::RenderWindow& window) override;
    sf::FloatRect getGlobalBounds() const override;

    void checkPlayerCollision(Player& player) override;
    bool isAlive() const override;

private:
    sf::Clock m_animationClock;
    sf::Time m_timePerFrame;
    int m_currentFrame;
    int m_frameCount;
    int m_frameWidth;
    int m_frameHeight;

    void updateAnimation();
};