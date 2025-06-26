#pragma once

#include <SFML/Graphics.hpp>

class Player;

class Coin
{
public:
    Coin(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture, int value);

    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds() const;

    void checkPlayerCollision(Player& player, int& score);
    bool isActive() const { return m_isActive; }

private:
    sf::Sprite m_sprite;
    int m_value;
    bool m_isActive;

    sf::Clock m_animationClock;
    sf::Time m_timePerFrame;
    int m_currentFrame;
    int m_frameCount;
    int m_frameWidth;
    int m_frameHeight;

    void updateAnimation();
};