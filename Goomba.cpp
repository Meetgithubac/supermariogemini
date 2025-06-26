#include "Goomba.hpp"
#include "Player.hpp"
#include "TileMap.hpp"
#include <iostream>

Goomba::Goomba(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture)
    : Enemy(texture),
    m_timePerFrame(sf::seconds(0.15f)),
    m_currentFrame(0),
    m_frameCount(2),
    m_frameWidth(16),
    m_frameHeight(16)
{
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameWidth, m_frameHeight }));
    m_sprite.setPosition(startPosition);
    m_sprite.setScale({ size.x / m_frameWidth, size.y / m_frameHeight });

    m_velocity.x = -50.f;
    m_movementSpeed = 50.f;
    m_isAlive = true;
}

void Goomba::update(sf::Time deltaTime, const TileMap& tilemap)
{
    if (!m_isAlive) return;

    sf::Vector2f oldPosition = m_sprite.getPosition();
    m_sprite.move({ m_velocity.x * deltaTime.asSeconds(), 0.f });

    m_velocity.y += 500.f * deltaTime.asSeconds();
    if (m_velocity.y > 500.f) m_velocity.y = 500.f;
    m_sprite.move({ 0.f, m_velocity.y * deltaTime.asSeconds() });

    sf::FloatRect enemyBounds = getGlobalBounds();
    std::vector<sf::FloatRect> solidTiles = tilemap.getSolidTileBounds(enemyBounds);

    bool collidedHorizontally = false;
    for (const auto& tileBounds : solidTiles) {
        if (enemyBounds.findIntersection(tileBounds)) {
            collidedHorizontally = true;
            if (m_velocity.x > 0) {
                m_sprite.setPosition({ tileBounds.position.x - enemyBounds.size.x, m_sprite.getPosition().y });
            }
            else {
                m_sprite.setPosition({ tileBounds.position.x + tileBounds.size.x, m_sprite.getPosition().y });
            }
            m_velocity.x *= -1;
            break;
        }
    }

    enemyBounds = getGlobalBounds();
    bool onGround = false;
    sf::FloatRect feetCheck({ enemyBounds.position.x, enemyBounds.position.y + enemyBounds.size.y + 1.f }, { enemyBounds.size.x, 1.f });
    if (!tilemap.getSolidTileBounds(feetCheck).empty()) {
        onGround = true;
    }

    bool collidedVertically = false;
    for (const auto& tileBounds : solidTiles) {
        if (enemyBounds.findIntersection(tileBounds)) {
            collidedVertically = true;
            if (m_velocity.y > 0) {
                m_sprite.setPosition({ m_sprite.getPosition().x, tileBounds.position.y - enemyBounds.size.y });
                m_velocity.y = 0;
                onGround = true;
            }
            else if (m_velocity.y < 0) {
                m_sprite.setPosition({ m_sprite.getPosition().x, tileBounds.position.y + tileBounds.size.y });
                m_velocity.y = 0;
            }
        }
    }

    if (onGround && !collidedHorizontally) {
        float nextXPosition = m_sprite.getPosition().x + (m_velocity.x > 0 ? enemyBounds.size.x + 1.0f : -1.0f);
        sf::FloatRect nextStepGroundCheck({ nextXPosition, enemyBounds.position.y + enemyBounds.size.y + 1.0f }, { 1.0f, 1.0f });
        if (tilemap.getSolidTileBounds(nextStepGroundCheck).empty()) {
            m_velocity.x *= -1;
        }
    }

    updateAnimation();
}

void Goomba::render(sf::RenderWindow& window)
{
    if (m_isAlive) {
        window.draw(m_sprite);
    }
}

sf::FloatRect Goomba::getGlobalBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Goomba::checkPlayerCollision(Player& player)
{
    if (!m_isAlive) return;

    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect enemyBounds = getGlobalBounds();

    if (playerBounds.findIntersection(enemyBounds))
    {
        if (player.getVelocity().y > 0 &&
            playerBounds.position.y + playerBounds.size.y > enemyBounds.position.y &&
            playerBounds.position.y + playerBounds.size.y < enemyBounds.position.y + (enemyBounds.size.y / 2.0f))
        {
            m_isAlive = false;
            player.setVelocityY(-150.f);
            std::cout << "Player stomped Goomba!" << std::endl;
        }
        else if (!player.isInvincible())
        {
            player.takeDamage();
            std::cout << "Player hit Goomba and took damage!" << std::endl;
        }
    }
}

bool Goomba::isAlive() const
{
    return m_isAlive;
}

void Goomba::updateAnimation()
{
    if (m_animationClock.getElapsedTime() >= m_timePerFrame)
    {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth, 0 }, { m_frameWidth, m_frameHeight }));
        m_animationClock.restart();
    }
}