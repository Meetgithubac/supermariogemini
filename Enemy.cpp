#include "Enemy.hpp"
// No common implementation for base Enemy class
// Derived classes like Goomba will provide implementation
Enemy::Enemy(sf::Texture& texture)
    : m_sprite(texture), // Default construct sprite, will be set by derived class
    m_velocity(0.f, 0.f),
    m_movementSpeed(0.f),
    m_isAlive(true)
{
    // No specific logic needed here for base Enemy
}

// Define the pure virtual destructor, even if empty
//Enemy::~Enemy() = default;