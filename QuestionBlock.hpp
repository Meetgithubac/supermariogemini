#pragma once

#include "Block.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Coin;

class QuestionBlock : public Block
{
public:
    QuestionBlock(sf::Vector2f position, sf::Vector2f size, sf::Texture& activeTexture, sf::Texture& emptyTexture);

    void update(sf::Time deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void checkPlayerCollision(Player& player, std::vector<std::unique_ptr<Coin>>& coins, int& score) override;

private:
    sf::Texture& m_activeTexture;
    sf::Texture& m_emptyTexture;
    bool m_isEmpty;

    sf::Clock m_animationClock;
    sf::Time m_timePerFrame;
    int m_currentFrame;
    int m_frameCount;
    int m_frameWidth;
    int m_frameHeight;

    void updateAnimation();
};