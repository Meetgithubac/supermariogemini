#include "QuestionBlock.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include "Coin.hpp"
#include <iostream>

QuestionBlock::QuestionBlock(sf::Vector2f position, sf::Vector2f size, sf::Texture& activeTexture, sf::Texture& emptyTexture)
    : Block(position, size, activeTexture),
    m_activeTexture(activeTexture),
    m_emptyTexture(emptyTexture),
    m_isEmpty(false),
    m_timePerFrame(sf::seconds(0.15f)),
    m_currentFrame(0),
    m_frameCount(4),
    m_frameWidth(16),
    m_frameHeight(16)
{
    m_sprite.setTexture(m_activeTexture);
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameWidth, m_frameHeight }));
    m_sprite.setScale({size.x / m_frameWidth, size.y / m_frameHeight
});
}

void QuestionBlock::update(sf::Time deltaTime)
{
    Block::update(deltaTime);
    if (!m_isEmpty)
    {
        updateAnimation();
    }
}

void QuestionBlock::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void QuestionBlock::checkPlayerCollision(Player& player, std::vector<std::unique_ptr<Coin>>& coins, int& score)
{
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect blockBounds = getGlobalBounds();

    if (playerBounds.findIntersection(blockBounds))
    {
        if (player.getVelocity().y < 0 &&
            playerBounds.position.y < blockBounds.position.y + blockBounds.size.y &&
            playerBounds.position.y > blockBounds.position.y)
        {
            if (!m_isHit && !m_isEmpty)
            {
                m_isHit = true;
                m_hitTimer.restart();
                player.setVelocityY(0);
                player.setPosition({ player.getPosition().x, blockBounds.position.y + blockBounds.size.y });
                m_sprite.setPosition({ m_sprite.getPosition().x, m_sprite.getPosition().y - 5.f });

                m_isEmpty = true;
                m_sprite.setTexture(m_emptyTexture);
                m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameWidth, m_frameHeight }));

                std::cout << "Question Block hit! Dispensing coin..." << std::endl;

                sf::Vector2f coinSpawnPos = sf::Vector2f(blockBounds.position.x + blockBounds.size.x / 4, blockBounds.position.y - blockBounds.size.y);
                coins.push_back( std::make_unique<Coin>(coinSpawnPos, sf::Vector2f(24.f, 24.f), player.getTextureManager().getTexture("coin_texture"), 200));

                score += 200;
            }
        }
    }
}

void QuestionBlock::updateAnimation()
{
    if (m_animationClock.getElapsedTime() >= m_timePerFrame)
    {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth, 0 }, { m_frameWidth, m_frameHeight }));
        m_animationClock.restart();
    }
}