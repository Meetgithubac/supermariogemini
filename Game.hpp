#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "Player.hpp"
#include "TileMap.hpp"
#include "Enemy.hpp"
#include "Coin.hpp"
#include "Block.hpp"
#include "QuestionBlock.hpp"
#include "BrickBlock.hpp"
#include "Camera.hpp"
#include "Goomba.hpp"
#include "TextureManager.hpp"

class Player;
class TileMap;
class Enemy;
class Coin;
class Block; // Base Block
class QuestionBlock; // Specific Block
class BrickBlock; // Specific Block
class Camera;
class TextureManager; // Make sure this is included too


class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;

    int m_score;
    sf::Font m_font;
    sf::Text m_scoreText;

    TextureManager m_textureManager;

    /*Player m_player;

    TileMap m_tilemap;*/

    std::unique_ptr<Player> m_player;
    std::unique_ptr<TileMap> m_tilemap;

    std::vector<std::unique_ptr<Enemy>> m_enemies;
    std::vector<std::unique_ptr<Coin>> m_coins;

    std::vector<std::unique_ptr<Block>> m_blocks;

    

    Camera m_camera;
    float m_levelWidth;
    float m_levelHeight;

    std::optional<sf::Sprite> m_farBackground;
    std::optional<sf::Sprite> m_midBackground;
    std::optional<sf::Sprite> m_backgroundSprite;

    float m_backgroundColorValue;
    bool m_colorIncreasing;
    bool m_isPaused;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void loadAssets();
    void initGameObjects();
    void renderBackgroundLayers();
    void renderHUD();
};