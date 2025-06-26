#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <map>
#include <string>

class TileMap;
class TextureManager;

class Player
{
public:
    enum class State {
        Idle,
        Walking,
        Running,
        Jumping,
        Falling,
        Crouching,
        Damaged
    };

    Player(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture);

    void update(sf::Time deltaTime, sf::Vector2u windowSize, const TileMap& tilemap);
    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    void setPosition(sf::Vector2f newPos);

    void setVelocityY(float yVelocity) { m_velocity.y = yVelocity; }
    sf::Vector2f getVelocity() const { return m_velocity; }

    void setTextureManager(TextureManager* tm) { m_textureManager = tm; }
    TextureManager& getTextureManager() { return *m_textureManager; }

    void takeDamage();
    bool isInvincible() const { return m_isInvincible; }

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;
    float m_movementSpeed;
    float m_sprintSpeedMultiplier;

    float m_gravity;
    float m_jumpStrength;
    bool m_onGround;

    float m_standingHeight;
    float m_crouchingHeight;
    sf::Vector2f m_currentHitboxSize;

    State m_currentState;
    State m_previousState;
    int m_currentFrame;
    sf::Clock m_animationClock;
    sf::Time m_timePerFrame;
    int m_frameWidth;
    int m_frameHeight;

    struct AnimationProperties {
        int startFrame;
        int endFrame;
        sf::Time frameDuration;
        bool loop;
    };
    std::map<State, AnimationProperties> m_animations;

    bool m_jumpKeyHeld;
    float m_minJumpVelocityCutoff;

    TextureManager* m_textureManager;

    bool m_isInvincible;
    sf::Clock m_invincibilityClock;
    sf::Time m_invincibilityDuration;
    sf::Clock m_flashClock;
    sf::Time m_flashInterval;
    bool m_isSpriteVisible;

    void handleInput();
    void updateAnimation();
    void applyGravity(sf::Time deltaTime);
    void jump();
    void checkCollisions(const TileMap& tilemap, sf::Vector2f oldPosition);
    void setState(State newState);

    void updateHitbox();
    void updateDamageState(sf::Time deltaTime);
};