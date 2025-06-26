#include "Block.hpp"
#include "Player.hpp"
#include "Coin.hpp"
#include <iostream>

Block::Block(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture)
    : m_sprite(texture),
    m_isHit(false),
    m_hitDuration(sf::seconds(0.2f))
{
    m_sprite.setPosition(position);
    m_sprite.setScale({size.x / m_sprite.getLocalBounds().size.x, size.y / m_sprite.getLocalBounds().size.y});
}

void Block::update(sf::Time deltaTime)
{
    if (m_isHit)
    {
        if (m_hitTimer.getElapsedTime() >= m_hitDuration)
        {
            m_isHit = false;
            m_sprite.setPosition({ m_sprite.getPosition().x, m_sprite.getPosition().y + 5.f });
        }
    }
}

void Block::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::FloatRect Block::getGlobalBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Block::checkPlayerCollision(Player& player, std::vector<std::unique_ptr<Coin>>& coins, int& score)
{
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect blockBounds = getGlobalBounds();

    if (playerBounds.findIntersection(blockBounds))
    {
        if (player.getVelocity().y < 0 &&
            playerBounds.position.y < blockBounds.position.y + blockBounds.size.y &&
            playerBounds.position.y > blockBounds.position.y)
        {
            if (!m_isHit)
            {
                m_isHit = true;
                m_hitTimer.restart();
                player.setVelocityY(0);
                player.setPosition({ player.getPosition().x, blockBounds.position.y + blockBounds.size.y });
                m_sprite.setPosition({ m_sprite.getPosition().x, m_sprite.getPosition().y - 5.f });
                std::cout << "Block hit from below!" << std::endl;
            }
        }
    }
}