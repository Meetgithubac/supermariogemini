#include "TileMap.hpp"
#include <iostream>
#include <memory>

TileMap::TileMap(sf::Texture& tileset)
    : m_tileset(tileset),
    m_tileSize(0),
    m_levelWidth(0),
    m_levelHeight(0)
{
    m_solidTiles[1] = true;
    m_solidTiles[2] = true;
}

bool TileMap::load(const std::vector<std::vector<int>>& level, unsigned int tileCols, unsigned int tileRows)
{
    m_levelData = level;
    m_tileSize = 32;

    m_levelWidth = static_cast<float>(tileCols * m_tileSize);
    m_levelHeight = static_cast<float>(tileRows * m_tileSize);

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(tileCols * tileRows * 4);

    for (unsigned int i = 0; i < tileCols; ++i)
    {
        for (unsigned int j = 0; j < tileRows; ++j)
        {
            int tileType = m_levelData[j][i];

            int tu = tileType % (m_tileset.getSize().x / m_tileSize);
            int tv = tileType / (m_tileset.getSize().x / m_tileSize);

            sf::Vertex* quad = &m_vertices[(i + j * tileCols) * 4];

            quad[0].position = sf::Vector2f(static_cast<float>(i * m_tileSize), static_cast<float>(j * m_tileSize));
            quad[1].position = sf::Vector2f(static_cast<float>((i + 1) * m_tileSize), static_cast<float>(j * m_tileSize));
            quad[2].position = sf::Vector2f(static_cast<float>((i + 1) * m_tileSize), static_cast<float>((j + 1) * m_tileSize));
            quad[3].position = sf::Vector2f(static_cast<float>(i * m_tileSize), static_cast<float>((j + 1) * m_tileSize));

            quad[0].texCoords = sf::Vector2f(static_cast<float>(tu * m_tileSize), static_cast<float>(tv * m_tileSize));
            quad[1].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * m_tileSize), static_cast<float>(tv * m_tileSize));
            quad[2].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * m_tileSize), static_cast<float>((tv + 1) * m_tileSize));
            quad[3].texCoords = sf::Vector2f(static_cast<float>(tu * m_tileSize), static_cast<float>((tv + 1) * m_tileSize));
        }
    }
    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}

std::vector<sf::FloatRect> TileMap::getSolidTileBounds(sf::FloatRect collisionRect) const
{
    std::vector<sf::FloatRect> solidTiles;

    int startCol = static_cast<int>(collisionRect.position.x / m_tileSize);
    int endCol = static_cast<int>((collisionRect.position.x + collisionRect.size.x) / m_tileSize);
    int startRow = static_cast<int>(collisionRect.position.y / m_tileSize);
    int endRow = static_cast<int>((collisionRect.position.y + collisionRect.size.y) / m_tileSize);

    startCol = std::max(0, startCol);
    endCol = std::min(static_cast<int>(m_levelData[0].size()) - 1, endCol);
    startRow = std::max(0, startRow);
    endRow = std::min(static_cast<int>(m_levelData.size()) - 1, endRow);

    for (int j = startRow; j <= endRow; ++j)
    {
        for (int i = startCol; i <= endCol; ++i)
        {
            if (m_levelData[j][i] != 0 && m_solidTiles.count(m_levelData[j][i]))
            {
                //solidTiles.emplace_back( static_cast<float>(i * m_tileSize), static_cast<float>(j * m_tileSize) , static_cast<float>(m_tileSize), static_cast<float>(m_tileSize) );
                solidTiles.emplace_back(
                    sf::Vector2f(static_cast<float>(i * m_tileSize), static_cast<float>(j * m_tileSize)),
                    sf::Vector2f(static_cast<float>(m_tileSize), static_cast<float>(m_tileSize))
                );

            }
        }
    }
    return solidTiles;
}