#pragma once

#include "Board.h"

Board::Board(sf::RenderWindow& window, std::pair<GameTextures, GameTextures> player_texture)
	:m_window(window), m_gravity(0.0f,9.8f), m_world(m_gravity), m_player_textures(player_texture)
{
    m_background.setTexture(Resources::instance().getGameTexture(Level_Background));
    m_background.scale(1.6f, 1.6f);
    m_world.SetContactListener(&m_contact);
}


void Board::drawBoard()
{
    m_window.draw(m_background);
    for (int object = 0; object < m_static_objects.size(); object++)
    {
        m_static_objects[object]->draw(m_window);
    }
    for (int object = 0; object < m_moving_objects.size(); object++)
    {
        m_moving_objects[object]->draw(m_window);
    }
}

void Board::moveObjects()
{
    // Update Box2D world
    float timeStep = 1.0f / 60.0f; // Adjust the time step as needed
    int32 velocityIterations = 6; // Adjust the iterations as needed
    int32 positionIterations = 2; // Adjust the iterations as needed
    m_world.Step(timeStep, velocityIterations, positionIterations);

    for (int index = 0; index < m_moving_objects.size(); index++)
    {
        m_moving_objects[index]->move();
    }
}


b2Vec2 Board::getPlayerPosition()
{
    return m_player->getPosition();
}

void Board::viewBackground(float addition)
{
    m_background.setPosition(m_background.getPosition().x + addition , m_background.getPosition().y);
}

void Board::swapGravity()
{
    m_gravity = -m_gravity;
    m_world.SetGravity(m_gravity);
}

void Board::updateMovingDirections()
{
    //update each moving object direction 
    for (int object = 0; object < m_moving_objects.size(); ++object)
    {
        m_moving_objects[object]->updateDirection();
    }
}

void Board::rightReleased()
{
    m_player->releaseRight();
}

void Board::leftReleased()
{
    m_player->releaseLeft();
}

void Board::spaceReleased()
{
    m_player->releaseSpace();
}

void Board::changeBoxShip(std::pair<GameTextures, GameTextures> player_textures)
{
    m_player_textures = player_textures;
}

void Board::handleCollision()
{
    std::erase_if(m_static_objects, [](const auto& static_object) {return static_object->getDelete(); });
       
    if (!m_player->isAlive())
        m_player->kill();

    if (m_player->isBoxStateMarked())
        m_player->handleBoxStateMarking();

    if (m_player->isShipStateMarked())
        m_player->handleShipStateMarking();
    
    if (m_player->isGravityMarked())
        swapGravity();

    if (m_player->isWinner())
        m_win = true;
        

    for (auto& object : m_static_objects)
    {
        if (!object->isActive())
        {
            object->shutDown();
        }
        object->restart();
    }
}


void Board::createLevel(const GameMaps level, const GameSounds sound)
{
    m_game_song.setBuffer(Resources::instance().getGameSounds(sound));
    m_game_song.setLoop(true);
    m_game_song.play();
    const sf::Image& source = Resources::instance().getGameMaps(level);
    for (size_t y = 0; y < source.getSize().y; ++y)
    {
        for (size_t x = 0; x < source.getSize().x; ++x)
        {
            sf::Vector2f location(50 * x + 25, 50 * y + 25);

            if (source.getPixel(x, y) == sf::Color::White)
                continue;
            else if ((source.getPixel(x, y) == PLAYER_COLOR))
            {
                m_player = new Player(m_world, m_player_textures, location);
                m_moving_objects.push_back(std::unique_ptr<Player>(m_player));
                m_player_location = location;
            }
            else if ((source.getPixel(x, y) == FLOOR_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Brick>(m_world, Floor, location));
            }
            else if ((source.getPixel(x, y) == CUBE_CUBE_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Brick>(m_world, CubeCube, location));
            }
            else if ((source.getPixel(x, y) == CUBE1_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Brick>(m_world, Cube1, location));
            }
            else if ((source.getPixel(x, y) == CUBE2_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Brick>(m_world, Cube2, location));
            }
            else if ((source.getPixel(x, y) == RECTANGLE_COLOR))
            {
                sf::Vector2f rectangle_location(50 * x + 25, 50 * y + 38);
                m_static_objects.push_back(std::make_unique<Brick>(m_world, Rectangle, rectangle_location));
            }
            else if ((source.getPixel(x, y) == COIN_COLOR))
            {
                m_static_objects.push_back(std::make_unique<class Coin>(m_world, Coin, location));
            }
            else if ((source.getPixel(x, y) == GATE1_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Gate>(m_world, Gate1, location));
            }
            else if ((source.getPixel(x, y) == GATE2_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Gate>(m_world, Gate2, location));
            }
            else if ((source.getPixel(x, y) == GATE3_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Gate>(m_world, Gate3, location));
            }
            else if ((source.getPixel(x, y) == GATE4_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Gate>(m_world, Gate4, location));
            }
            else if ((source.getPixel(x, y) == GATE5_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Gate>(m_world, Gate5, location));
            }
            else if ((source.getPixel(x, y) == SPIKES_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Spike>(m_world, Spikes, location, false));
            }
            else if (source.getPixel(x, y) == SPIKE1_COLOR)
            {
                m_static_objects.push_back(std::make_unique<Spike>(m_world, Spike1, location, false));
            }
            else if (source.getPixel(x, y) == SPIKE1_UP_COLOR)
            {
                m_static_objects.push_back(std::make_unique<Spike>(m_world, Spike1, location, true));
            }
            else if ((source.getPixel(x, y) == SPIKE2_COLOR))
            {
                sf::Vector2f spike2_location(50 * x + 25, 50 * y +38);
                m_static_objects.push_back(std::make_unique<Spike>(m_world, Spike2, spike2_location, false));
            }
            else if ((source.getPixel(x, y) == JUMPER1_COLOR))
            {
                sf::Vector2f jumper1_location(50 * x + 25, 50 * y + 38);
                m_static_objects.push_back(std::make_unique<Jumper>(m_world, Jumper1, jumper1_location, false));
            }
            else if ((source.getPixel(x, y) == JUMPER2_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Jumper>(m_world, Jumper2, location, false));
            }
            else if ((source.getPixel(x, y) == JUMPER1_UP_COLOR))
            {
                sf::Vector2f jumper1_location(50 * x + 25, 50 * y +13);
                m_static_objects.push_back(std::make_unique<Jumper>(m_world, Jumper1, jumper1_location, true));
            }
            else if ((source.getPixel(x, y) == ENEMY1_COLOR))
            {
                m_moving_objects.push_back(std::make_unique<Enemy>(m_world, Enemy1, location, false,
                    Enemy1Animation, Enemy1SpriteSheet));
            }
            else if ((source.getPixel(x, y) == ENEMY1_UP_COLOR))
            {
                m_moving_objects.push_back(std::make_unique<Enemy>(m_world, Enemy1, location, true,
                    Enemy1Animation, Enemy1SpriteSheet));
            }
            else if ((source.getPixel(x, y) == ENEMY2_COLOR))
            {
                m_moving_objects.push_back(std::make_unique<Enemy>(m_world, Enemy2, location, false,
                    Enemy2Animation, Enemy2SpriteSheet));
            }
            else if ((source.getPixel(x, y) == ENEMY2_UP_COLOR))
            {
                m_moving_objects.push_back(std::make_unique<Enemy>(m_world, Enemy2, location, true,
                    Enemy2Animation, Enemy2SpriteSheet));
            }
        }
    }
}

bool Board::isWin()
{
    return m_win;
}

int Board::getCoins()
{
    return m_player->getCoins();
}

void Board::resetBoard()
{
    m_static_objects.clear();
    m_moving_objects.clear();
    m_player = nullptr;
    m_win = false;
    m_background.setPosition(0, 0);

    // Destroy all fixtures
    b2Body* body = m_world.GetBodyList();
    while (body) {
        b2Fixture* fixture = body->GetFixtureList();
        while (fixture) {
            b2Fixture* nextFixture = fixture->GetNext();
            body->DestroyFixture(fixture);
            fixture = nextFixture;
        }
        body = body->GetNext();
    }

    // Destroy all bodies
    body = m_world.GetBodyList();
    while (body) {
        b2Body* nextBody = body->GetNext();
        m_world.DestroyBody(body);
        body = nextBody;
    }
    m_game_song.pause();
}


