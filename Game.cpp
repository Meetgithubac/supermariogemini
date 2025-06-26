#include "Game.hpp"
#include <algorithm>
#include "TileMap.hpp"
#include "Player.hpp"
#include "Goomba.hpp"
#include "Coin.hpp"
#include "QuestionBlock.hpp"
#include "BrickBlock.hpp"
#include "Camera.hpp"
#include "TextureManager.hpp"
#include <SFML/Graphics/Text.hpp> // Or just SFML/Graphics.hpp covers it
#include <iomanip>
#include <sstream>
#include <memory>

const int TILE_SIZE = 32;
const int MAP_COLS = 50;
const int MAP_ROWS = 10;

std::vector<std::vector<int>> level = {
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Game::Game()
    : m_window(sf::VideoMode({ 800, 600 }), "Super Mario Clone - Session 14", sf::Style::Close | sf::Style::Resize),
    m_levelWidth(static_cast<float>(MAP_COLS* TILE_SIZE)),
    m_levelHeight(static_cast<float>(MAP_ROWS* TILE_SIZE)),
    m_camera(sf::Vector2f(800, 600), m_levelWidth, m_levelHeight),
    m_backgroundColorValue(200.f),
    m_colorIncreasing(false),
    m_isPaused(false),
    m_tilemap(m_textureManager.getTexture("tileset_texture")),
    m_player(sf::Vector2f(100.f, 100.f), sf::Vector2f(50.f, 50.f), m_textureManager.getTexture("player_texture")), // Initialize m_player here
    m_scoreText(m_font),
    m_score(0)
{
    m_window.setVerticalSyncEnabled(false);
    m_window.setFramerateLimit(60);

    ////m_scoreText.setFont(m_font);
    //m_scoreText.setString("Score: 0");
    //m_scoreText.setCharacterSize(24);
    //m_scoreText.setFillColor(sf::Color::White);
    //m_scoreText.setPosition({10.f, 10.f});
    ////m_scoreText. ;

    loadAssets();
    initGameObjects();
}

Game::~Game()
{
}

void Game::run()
{
    while (m_window.isOpen())
    {
        sf::Time deltaTime = m_clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    while (std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }
        if (const auto key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->scancode == sf::Keyboard::Scancode::P)
            {
                m_isPaused = !m_isPaused;
            }
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    if (!m_isPaused)
    {
        m_player.update(deltaTime, m_window.getSize(), m_tilemap);
        m_camera.update(m_player.getPosition());

        for (const auto& enemy : m_enemies)
        {
            enemy->update(deltaTime, m_tilemap);
            enemy->checkPlayerCollision(m_player);
        }

        m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(),
            [](const std::unique_ptr<Enemy>& enemy) {
                return !enemy->isAlive();
            }),
            m_enemies.end());

        for (const auto& coin : m_coins)
        {
            coin->update(deltaTime);
            coin->checkPlayerCollision(m_player, m_score);
        }

        m_coins.erase(std::remove_if(m_coins.begin(), m_coins.end(),
            [](const std::unique_ptr<Coin>& coin) {
                return !coin->isActive();
            }),
            m_coins.end());

        for (const auto& block : m_blocks)
        {
            block->update(deltaTime);
            block->checkPlayerCollision(m_player, m_coins, m_score);
        }

        m_blocks.erase(std::remove_if(m_blocks.begin(), m_blocks.end(),
            [](const std::unique_ptr<Block>& block) {
                BrickBlock* brick = dynamic_cast<BrickBlock*>(block.get());
                return (brick != nullptr && brick->isBroken());
            }),
            m_blocks.end());

        const float colorChangeSpeed = 50.f;
        if (m_colorIncreasing) {
            m_backgroundColorValue += colorChangeSpeed * deltaTime.asSeconds();
        }
        else {
            m_backgroundColorValue -= colorChangeSpeed * deltaTime.asSeconds();
        }
        if (m_backgroundColorValue <= 0.f) {
            m_backgroundColorValue = 0.f;
            m_colorIncreasing = true;
        }
        else if (m_backgroundColorValue >= 200.f) {
            m_backgroundColorValue = 200.f;
            m_colorIncreasing = false;
        }

        std::stringstream ss;
        ss << "SCORE: " << std::setw(6) << std::setfill('0') << m_score;
        m_scoreText.setString(ss.str());
    }
}

void Game::render()
{
    m_window.clear(sf::Color(0, 0, static_cast<uint8_t>(m_backgroundColorValue)));

    m_camera.applyTo(m_window);

    renderBackgroundLayers();

    m_window.draw(m_tilemap);

    for (const auto& enemy : m_enemies)
    {
        enemy->render(m_window);
    }

    for (const auto& coin : m_coins)
    {
        coin->render(m_window);
    }

    for (const auto& block : m_blocks)
    {
        block->render(m_window);
    }

    m_player.render(m_window);

    renderHUD();

    m_window.display();
}

void Game::loadAssets()
{
    m_textureManager.loadTexture("player_texture", "Assets/Textures/player_spritesheet.png");
    m_textureManager.loadTexture("background_sky", "Assets/Textures/background_sky.png");
    m_textureManager.loadTexture("background_clouds", "Assets/Textures/background_clouds.png");
    m_textureManager.loadTexture("background_mountains", "Assets/Textures/background_mountains.png");
    m_textureManager.loadTexture("tileset_texture", "Assets/Textures/tileset.png");
    m_textureManager.loadTexture("goomba_texture", "Assets/Textures/goomba_spritesheet.png");
    m_textureManager.loadTexture("coin_texture", "Assets/Textures/coin_spritesheet.png");

    m_textureManager.loadTexture("question_block_active_texture", "Assets/Textures/question_block_spritesheet.png");
    m_textureManager.loadTexture("question_block_empty_texture", "Assets/Textures/empty_block_texture.png");
    m_textureManager.loadTexture("brick_block_texture", "Assets/Textures/brick_block_texture.png");

    if (!m_font.openFromFile("Assets/Fonts/SuperMarioBros-3.ttf"))
    {
        std::cerr << "Error loading font: Assets/Fonts/SuperMarioBros-3.ttf" << std::endl;
    }
}

void Game::initGameObjects()
{
    m_tilemap.load(level, MAP_COLS, MAP_ROWS);
    //m_player = Player(sf::Vector2f(100.f, 100.f), sf::Vector2f(50.f, 50.f), m_textureManager.getTexture("player_texture"));
    m_player.setTextureManager(&m_textureManager);

    m_enemies.push_back(std::make_unique<Goomba>(sf::Vector2f(200.f, 400.f), sf::Vector2f(32.f, 32.f), m_textureManager.getTexture("goomba_texture")));
    m_enemies.push_back(std::make_unique<Goomba>(sf::Vector2f(600.f, 400.f), sf::Vector2f(32.f, 32.f), m_textureManager.getTexture("goomba_texture")));
    m_enemies.push_back(std::make_unique<Goomba>(sf::Vector2f(800.f, 400.f), sf::Vector2f(32.f, 32.f), m_textureManager.getTexture("goomba_texture")));

    m_coins.push_back(std::make_unique<Coin>(sf::Vector2f(250.f, 450.f), sf::Vector2f(24.f, 24.f), m_textureManager.getTexture("coin_texture"), 100));
    m_coins.push_back(std::make_unique<Coin>(sf::Vector2f(280.f, 450.f), sf::Vector2f(24.f, 24.f), m_textureManager.getTexture("coin_texture"), 100));
    m_coins.push_back(std::make_unique<Coin>(sf::Vector2f(310.f, 450.f), sf::Vector2f(24.f, 24.f), m_textureManager.getTexture("coin_texture"), 100));
    m_coins.push_back(std::make_unique<Coin>(sf::Vector2f(700.f, 400.f), sf::Vector2f(24.f, 24.f), m_textureManager.getTexture("coin_texture"), 100));

    m_blocks.push_back(std::make_unique<QuestionBlock>(
        sf::Vector2f(300.f, 200.f), sf::Vector2f(32.f, 32.f),
        m_textureManager.getTexture("question_block_active_texture"),
        m_textureManager.getTexture("question_block_empty_texture")));

    m_blocks.push_back(std::make_unique<BrickBlock>(
        sf::Vector2f(332.f, 200.f), sf::Vector2f(32.f, 32.f),
        m_textureManager.getTexture("brick_block_texture")));

    m_blocks.push_back(std::make_unique<QuestionBlock>(
        sf::Vector2f(364.f, 200.f), sf::Vector2f(32.f, 32.f),
        m_textureManager.getTexture("question_block_active_texture"),
        m_textureManager.getTexture("question_block_empty_texture")));



    m_farBackground->setTexture(m_textureManager.getTexture("background_mountains"));
    m_midBackground->setTexture(m_textureManager.getTexture("background_clouds"));
    m_backgroundSprite->setTexture(m_textureManager.getTexture("background_sky"));

    sf::Vector2u viewSize = m_camera.getSize();
    m_farBackground->setScale({ static_cast<float>(viewSize.x) / m_farBackground->getGlobalBounds().size.x, static_cast<float>(viewSize.y) / m_farBackground->getGlobalBounds().size.y });
    m_midBackground->setScale({ static_cast<float>(viewSize.x) / m_midBackground->getGlobalBounds().size.x, static_cast<float>(viewSize.y) / m_midBackground->getGlobalBounds().size.y });
    m_backgroundSprite->setScale({ static_cast<float>(viewSize.x) / m_backgroundSprite->getGlobalBounds().size.x, static_cast<float>(viewSize.y) / m_backgroundSprite->getGlobalBounds().size.y });

    //m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition({ 10, 10 });
    m_scoreText.setString("SCORE: 000000");
}

void Game::renderBackgroundLayers()
{
    sf::View currentView = m_window.getView();
    sf::Vector2f cameraCenter = currentView.getCenter();
    sf::Vector2f viewSize = currentView.getSize();

    float parallaxFactorFar = 0.1f;
    float parallaxFactorMid = 0.3f;

    sf::Vector2f farBgPos;
    farBgPos.x = cameraCenter.x * parallaxFactorFar - viewSize.x / 2;
    farBgPos.y = 0;
    m_farBackground->setPosition(farBgPos);

    sf::Vector2f midBgPos;
    midBgPos.x = cameraCenter.x * parallaxFactorMid - viewSize.x / 2;
    midBgPos.y = 0;
    m_midBackground->setPosition(midBgPos);

    m_backgroundSprite->setPosition({ cameraCenter.x - viewSize.x / 2, 0 });

    if(m_backgroundSprite)
        m_window.draw(*m_backgroundSprite);
    if (m_midBackground)
        m_window.draw(*m_midBackground);
    if (m_farBackground)
        m_window.draw(*m_farBackground);
}

void Game::renderHUD()
{
    sf::View hudView = m_window.getDefaultView();
    m_window.setView(hudView);
    m_window.draw(m_scoreText);
    m_window.setView(m_camera.getView());
}