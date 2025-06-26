#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera(sf::Vector2f viewSize, float levelWidth, float levelHeight);

    void update(sf::Vector2f playerPosition);
    void applyTo(sf::RenderWindow& window);
    sf::View getView() const;
    sf::Vector2u getSize() const;

private:
    sf::View m_view;
    float m_levelWidth;
    float m_levelHeight;
};