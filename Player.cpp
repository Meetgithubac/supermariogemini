#include "Player.hpp"
#include "TileMap.hpp"
#include "TextureManager.hpp"
#include <iostream>
#include <memory>

Player::Player(sf::Vector2f startPosition, sf::Vector2f size, sf::Texture& texture)
    : m_sprite(texture),
    m_movementSpeed(150.f),
    m_sprintSpeedMultiplier(1.8f),
    m_gravity(500.f),
    m_jumpStrength(-300.f),
    m_onGround(false),
    m_currentState(State::Idle),
    m_previousState(State::Idle),
    m_currentFrame(0),
    m_timePerFrame(sf::seconds(0.1f)),
    m_frameWidth(16),
    m_frameHeight(16),
    m_jumpKeyHeld(false),
    m_minJumpVelocityCutoff(80.f),
    m_textureManager(nullptr),
    m_isInvincible(false),
    m_invincibilityDuration(sf::seconds(2.0f)),
    m_flashInterval(sf::seconds(0.1f)),
    m_isSpriteVisible(true),
    m_standingHeight(size.y),
    m_crouchingHeight(size.y * 0.7f)
{
    m_animations[State::Idle] = { 0, 0, sf::seconds(0.1f), false };
    m_animations[State::Walking] = { 1, 2, sf::seconds(0.1f), true };
    m_animations[State::Running] = { 1, 2, sf::seconds(0.05f), true };
    m_animations[State::Jumping] = { 4, 4, sf::seconds(0.1f), false };
    m_animations[State::Falling] = { 5, 5, sf::seconds(0.1f), false };
    m_animations[State::Crouching] = { 6, 6, sf::seconds(0.1f), false };
    m_animations[State::Damaged] = { 0, 0, sf::seconds(0.1f), false };

    m_sprite.setTexture(texture);
    m_sprite.setScale({ size.x / m_frameWidth, size.y / m_frameHeight });

    m_sprite.setPosition(startPosition);
    m_velocity = sf::Vector2f(0.f, 0.f);

    m_currentHitboxSize.x = size.x;
    m_currentHitboxSize.y = m_standingHeight;
}

void Player::update(sf::Time deltaTime, sf::Vector2u windowSize, const TileMap& tilemap)
{
    float currentMovementSpeed = m_movementSpeed;

    handleInput();

    updateDamageState(deltaTime);

    if (m_currentState == State::Crouching) {
        m_velocity.x = 0.f;
    }
    else if (m_currentState == State::Running) {
        currentMovementSpeed *= m_sprintSpeedMultiplier;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            m_velocity.x = currentMovementSpeed;
            m_sprite.setScale({ -std::abs(m_sprite.getScale().x), m_sprite.getScale().y });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            m_sprite.setOrigin({ m_sprite.getLocalBounds().size.x, 0 });
            m_velocity.x = -currentMovementSpeed;
            m_sprite.setOrigin({ 0, 0 });
            m_sprite.setScale({ std::abs(m_sprite.getScale().x), m_sprite.getScale().y });
        }
        else {
            m_velocity.x = 0.f;
        }
    }
    else if (m_currentState == State::Walking || m_currentState == State::Idle) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            m_velocity.x = currentMovementSpeed;
            m_sprite.setOrigin({ m_sprite.getLocalBounds().size.x, 0 });
            m_sprite.setScale({ -std::abs(m_sprite.getScale().x), m_sprite.getScale().y });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            m_velocity.x = -currentMovementSpeed;
            m_sprite.setOrigin({ 0, 0 });
            m_sprite.setScale({ std::abs(m_sprite.getScale().x), m_sprite.getScale().y });
        }
        else {
            m_velocity.x = 0.f;
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            m_velocity.x = m_movementSpeed;
            m_sprite.setOrigin({ m_sprite.getLocalBounds().size.x, 0 });
            m_sprite.setScale({ -std::abs(m_sprite.getScale().x), m_sprite.getScale().y });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            m_velocity.x = -m_movementSpeed;
            m_sprite.setOrigin({ 0, 0 });
            m_sprite.setScale({ std::abs(m_sprite.getScale().x), m_sprite.getScale().y });
        }
        else {
            if (m_currentState != State::Jumping && m_currentState != State::Falling) {
                m_velocity.x = 0.f;
            }
        }
    }

    sf::Vector2f oldPosition = m_sprite.getPosition();
    m_sprite.move({m_velocity.x * deltaTime.asSeconds(), 0.f});

    checkCollisions(tilemap, oldPosition);

    applyGravity(deltaTime);

    oldPosition = m_sprite.getPosition();
    m_sprite.move({0.f, m_velocity.y * deltaTime.asSeconds()});

    checkCollisions(tilemap, oldPosition);

    const float LEVEL_WIDTH = 50 * 32.0f;
    if (m_sprite.getPosition().x < 0) {
        m_sprite.setPosition({0, m_sprite.getPosition().y});
        m_velocity.x = 0;
    }
    if (m_sprite.getPosition().x + m_sprite.getGlobalBounds().size.x > LEVEL_WIDTH) {
        m_sprite.setPosition({ LEVEL_WIDTH - m_sprite.getGlobalBounds().size.x, m_sprite.getPosition().y });
        m_velocity.x = 0;
    }

    updateAnimation();
    updateHitbox();
}

void Player::render(sf::RenderWindow& window)
{
    if (m_isSpriteVisible) {
        window.draw(m_sprite);
    }
}

sf::Vector2f Player::getPosition() const
{
    return m_sprite.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const
{
    if (m_currentState == State::Crouching) {
        float offsetY = m_standingHeight - m_crouchingHeight;
        return sf::FloatRect({ m_sprite.getPosition().x, m_sprite.getPosition().y + offsetY },{ m_currentHitboxSize.x, m_crouchingHeight });
    }
    else {
        return sf::FloatRect({ m_sprite.getPosition().x, m_sprite.getPosition().y },{m_currentHitboxSize.x, m_standingHeight });
    }
}

void Player::setPosition(sf::Vector2f newPos)
{
    m_sprite.setPosition(newPos);
}

void Player::handleInput()
{
    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    bool sprintPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);

    if (upPressed && m_onGround && !m_jumpKeyHeld && m_currentState != State::Crouching) {
        jump();
        m_jumpKeyHeld = true;
    }
    else if (!upPressed) {
        m_jumpKeyHeld = false;
        if (m_velocity.y < m_minJumpVelocityCutoff && m_velocity.y < 0) {
            m_velocity.y = m_minJumpVelocityCutoff;
        }
    }

    if (m_onGround) {
        if (downPressed) {
            setState(State::Crouching);
        }
        else if (rightPressed || leftPressed) {
            if (sprintPressed) {
                setState(State::Running);
            }
            else {
                setState(State::Walking);
            }
        }
        else {
            setState(State::Idle);
        }
    }
    else {
        if (m_velocity.y < 0) {
            setState(State::Jumping);
        }
        else if (m_velocity.y > 0) {
            setState(State::Falling);
        }
    }

    if (m_isInvincible) {
        setState(State::Damaged);
    }
}

void Player::updateAnimation()
{
    AnimationProperties props = m_animations[m_currentState];

    if (m_animationClock.getElapsedTime() >= props.frameDuration) {
        m_currentFrame++;
        if (m_currentFrame > props.endFrame || m_currentFrame < props.startFrame) {
            m_currentFrame = props.startFrame;
        }

        m_sprite.setTextureRect(sf::IntRect({ m_currentFrame * m_frameWidth, 0 }, { m_frameWidth, m_frameHeight }));
        m_animationClock.restart();
    }
}

void Player::applyGravity(sf::Time deltaTime)
{
    m_velocity.y += m_gravity * deltaTime.asSeconds();
    if (m_velocity.y > 500.f) {
        m_velocity.y = 500.f;
    }
}

void Player::jump()
{
    if (m_onGround) {
        m_velocity.y = m_jumpStrength;
        m_onGround = false;
        setState(State::Jumping);
    }
}

void Player::checkCollisions(const TileMap& tilemap, sf::Vector2f oldPosition)
{
    sf::FloatRect playerBounds = getGlobalBounds();

    if (m_sprite.getPosition().x != oldPosition.x) {
        std::vector<sf::FloatRect> solidTiles = tilemap.getSolidTileBounds(playerBounds);
        for (const auto& tileBounds : solidTiles) {
            if (playerBounds.findIntersection(tileBounds)) {
                if (m_velocity.x > 0) {
                    m_sprite.setPosition({ tileBounds.position.x - playerBounds.size.x , m_sprite.getPosition().y});
                }
                else if (m_velocity.x < 0) {
                    m_sprite.setPosition({ tileBounds.position.x + tileBounds.size.x , m_sprite.getPosition().y });
                }
                m_velocity.x = 0;
                playerBounds = getGlobalBounds();
            }
        }
    }

    if (m_sprite.getPosition().y != oldPosition.y) {
        m_onGround = false;
        std::vector<sf::FloatRect> solidTiles = tilemap.getSolidTileBounds(playerBounds);
        for (const auto& tileBounds : solidTiles) {
            if (playerBounds.findIntersection(tileBounds)) {
                if (m_velocity.y > 0) {
                    m_sprite.setPosition({ m_sprite.getPosition().x, tileBounds.position.y - playerBounds.size.y });
                    m_onGround = true;
                    m_velocity.y = 0;
                }
                else if (m_velocity.y < 0) {
                    m_sprite.setPosition({ m_sprite.getPosition().x, tileBounds.position.y+ tileBounds.size.y });
                    m_velocity.y = 0;
                }
                playerBounds = getGlobalBounds();
            }
        }
    }
}

void Player::setState(State newState)
{
    if (m_currentState == newState) return;

    m_previousState = m_currentState;
    m_currentState = newState;

    AnimationProperties props = m_animations[m_currentState];
    m_currentFrame = props.startFrame;
    m_timePerFrame = props.frameDuration;
    m_animationClock.restart();

    updateHitbox();
}

void Player::updateHitbox()
{
    if (m_currentState == State::Crouching) {
        if (m_previousState != State::Crouching) {
            float y_offset_change = m_standingHeight - m_crouchingHeight;
            m_sprite.move({ 0, y_offset_change });
        }
        m_sprite.setTextureRect(sf::IntRect({ m_animations[State::Crouching].startFrame * m_frameWidth , 0 }, { m_frameWidth, m_frameHeight }));
    }
    else {
        if (m_previousState == State::Crouching) {
            float y_offset_change = m_standingHeight - m_crouchingHeight;
            m_sprite.move({ 0, -y_offset_change });
        }
    }
}

void Player::takeDamage()
{
    if (!m_isInvincible)
    {
        std::cout << "Player took damage!" << std::endl;
        m_isInvincible = true;
        m_invincibilityClock.restart();
        m_flashClock.restart();
        m_isSpriteVisible = false;
        m_previousState = m_currentState;
        setState(State::Damaged);
    }
}

void Player::updateDamageState(sf::Time deltaTime)
{
    if (m_isInvincible)
    {
        if (m_invincibilityClock.getElapsedTime() >= m_invincibilityDuration)
        {
            m_isInvincible = false;
            m_isSpriteVisible = true;
            if (m_currentState == State::Damaged) {
                setState(m_previousState);
            }
            std::cout << "Invincibility ended." << std::endl;
        }
        else
        {
            if (m_flashClock.getElapsedTime() >= m_flashInterval)
            {
                m_isSpriteVisible = !m_isSpriteVisible;
                m_flashClock.restart();
            }
        }
    }
}