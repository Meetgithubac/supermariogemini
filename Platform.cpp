// Source/Entities/Platform/Platform.cpp

#include "Platform.hpp"

// What it does: Platform class constructor implementation.
// Why it's used: Sets up the visual and physical properties of a new platform.
// How it works: Initializes the shape with size, sets its position and a brown color.
Platform::Platform(sf::Vector2f position, sf::Vector2f size)
    : m_shape(size) // Initialize shape with given size
{
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color(139, 69, 19)); // Brown color
}

// What it does: Draws the platform's shape to the window.
// Why it's used: Renders the platform for display.
// How it works: Calls the window's draw method with the internal shape.
void Platform::render(sf::RenderWindow& window)
{
    window.draw(m_shape);
}

// What it does: Returns the platform's bounding box.
// Why it's used: To allow other objects to check for collisions with this platform.
sf::FloatRect Platform::getGlobalBounds() const
{
    return m_shape.getGlobalBounds();
}