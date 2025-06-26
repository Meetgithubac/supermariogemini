#include "BrickBlock.hpp"
#include "Player.hpp"
#include "Coin.hpp"
#include <iostream>

BrickBlock::BrickBlock(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture)
    : Block(position, size, texture),
    m_isBroken(false)
{
}

void BrickBlock::update(sf::Time deltaTime)
{
    Block::update(deltaTime);
}

void BrickBlock::checkPlayerCollision(Player& player, std::vector<std::unique_ptr<Coin>>& coins, int& score)
{
    if (m_isBroken) return;

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

                m_isBroken = true;
                std::cout << "Brick Block broken!" << std::endl;
            }
        }
    }
}