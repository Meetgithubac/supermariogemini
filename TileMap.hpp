#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap(sf::Texture& tileset);

    bool load(const std::vector<std::vector<int>>& level, unsigned int tileCols, unsigned int tileRows);

    std::vector<sf::FloatRect> getSolidTileBounds(sf::FloatRect collisionRect) const;

    float getLevelWidth() const { return m_levelWidth; }
    float getLevelHeight() const { return m_levelHeight; }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_vertices;
    sf::Texture& m_tileset;
    unsigned int m_tileSize;

    float m_levelWidth;
    float m_levelHeight;

    std::vector<std::vector<int>> m_levelData;

    std::map<int, bool> m_solidTiles;
};