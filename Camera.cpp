#include "Camera.hpp"
#include <algorithm>

Camera::Camera(sf::Vector2f viewSize, float levelWidth, float levelHeight)
    : m_view(sf::FloatRect({ 0, 0 }, { viewSize.x, viewSize.y })),
    m_levelWidth(levelWidth),
    m_levelHeight(levelHeight)
{
    m_view.setCenter({ viewSize.x / 2.f, viewSize.y / 2.f });
}

void Camera::update(sf::Vector2f playerPosition)
{
    sf::Vector2f viewCenter = m_view.getCenter();
    sf::Vector2f viewSize = m_view.getSize();

    float targetX = playerPosition.x;
    float newX = std::max(viewSize.x / 2.f, std::min(targetX, m_levelWidth - viewSize.x / 2.f));

    m_view.setCenter({ newX, viewCenter.y });
}

void Camera::applyTo(sf::RenderWindow& window)
{
    window.setView(m_view);
}

sf::View Camera::getView() const
{
    return m_view;
}

sf::Vector2u Camera::getSize() const
{
    return sf::Vector2u(static_cast<unsigned int>(m_view.getSize().x), static_cast<unsigned int>(m_view.getSize().y));
}