#include "Coin.hpp"
#include "Player.hpp"
#include <iostream>

Coin::Coin(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture, int value)
    : m_value(value),
    m_isActive(true),
    m_timePerFrame(sf::seconds(0.1f)),
    m_currentFrame(0),
    m_frameCount(4),
    m_frameWidth(16),
    m_frameHeight(16),
    m_sprite(texture)
{
    //m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameWidth, m_frameHeight }));
    m_sprite.setPosition(position);
    m_sprite.setScale({ size.x / m_frameWidth, size.y / m_frameHeight });
}

void Coin::update(sf::Time deltaTime)
{
    if (m_isActive)
    {
        updateAnimation();
    }
}

void Coin::render(sf::RenderWindow& window)
{
    if (m_isActive)
    {
        window.draw(m_sprite);
    }
}

sf::FloatRect Coin::getGlobalBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Coin::checkPlayerCollision(Player& player, int& score)
{
    if (m_isActive && player.getGlobalBounds().findIntersection(getGlobalBounds()))
    {
        m_isActive = false;
        score += m_value;
        std::cout << "Coin collected! Score: " << score << std::endl;
    }
}

void Coin::updateAnimation()
{
    if (m_animationClock.getElapsedTime() >= m_timePerFrame)
    {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth , 0 }, { m_frameWidth, m_frameHeight }));
        m_animationClock.restart();
    }
}