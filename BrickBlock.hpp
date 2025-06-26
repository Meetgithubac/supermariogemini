#pragma once

#include "Block.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Coin;

class BrickBlock : public Block
{
public:
    BrickBlock(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture);

    void update(sf::Time deltaTime) override;
    void checkPlayerCollision(Player& player, std::vector<std::unique_ptr<Coin>>& coins, int& score) override;

    bool isBroken() const { return m_isBroken; }

private:
    bool m_isBroken;
};