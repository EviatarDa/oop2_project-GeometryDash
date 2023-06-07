#pragma once

#include "Board.h"

Board::Board(sf::RenderWindow& window, std::pair<GameTextures, GameTextures> player_texture)
	:m_window(window), m_gravity(0.0f,9.8f), m_world(m_gravity), m_player_textures(player_texture)
{
    m_background.setTexture(Resources::instance().getGameTexture(Level_Background));
    m_background.scale(1.6f, 1.6f);

    createLevel();
}

Board::~Board()
{
    for (auto& object : m_moving_objects)
        if (object->getBody() != nullptr)
            m_world.DestroyBody(object->getBody());
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
        //handleCollisions(*m_moving_objects[index]);
    }
}


b2Vec2 Board::getPlayerPosition()
{
    return m_moving_objects[m_player_index]->getPosition();
}

void Board::viewBackground(float addition)
{
    m_background.setPosition(m_background.getPosition().x +addition , m_background.getPosition().y);
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

void Board::changeBoxShip(std::pair<GameTextures, GameTextures> player_textures)
{
    //delete the old player body
    if (m_moving_objects[m_player_index]->getBody() != nullptr)
        m_world.DestroyBody(m_moving_objects[m_player_index]->getBody());

    //create the new player
    m_player_textures = player_textures;
    m_moving_objects[m_player_index] = std::make_unique<Player>(m_world, m_player_textures, m_player_location);
}


void Board::createLevel()
{
    const sf::Image& source = Resources::instance().getGameMaps(Map1);
    for (size_t y = 0; y < source.getSize().y; ++y)
    {
        for (size_t x = 0; x < source.getSize().x; ++x)
        {
            sf::Vector2f location(50 * x + 25, 50 * y + 25);
            if ((source.getPixel(x, y) == PLAYER_COLOR))
            {
                m_moving_objects.push_back(std::make_unique<Player>(m_world, m_player_textures, location));
                m_player_location = location;
                m_player_index = m_moving_objects.size()-1;
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
            else if ((source.getPixel(x, y) == COIN_COLOR))
            {
                m_static_objects.push_back(std::make_unique<class Coin>(Coin, location));
            }
            else if ((source.getPixel(x, y) == GATE1_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Gate>(Gate1, location));
            }
            else if ((source.getPixel(x, y) == GATE2_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Gate>(Gate2, location));
            }
            else if ((source.getPixel(x, y) == GATE3_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Gate>(Gate3, location));
            }
            else if ((source.getPixel(x, y) == GATE4_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Gate>(Gate4, location));
            }
            else if ((source.getPixel(x, y) == RECTANGLE_COLOR))
            {
                sf::Vector2f rectangle_location(50 * x + 25, 50 * y + 38);
                m_static_objects.push_back(std::make_unique<Brick>(m_world, Rectangle, rectangle_location));
            }
            else if ((source.getPixel(x, y) == SPIKES_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Spike>(Spikes, location));
            }
            else if (source.getPixel(x, y) == SPIKE1_COLOR)
            {
                m_static_objects.push_back(std::make_unique<Spike>(Spike1, location));
            }
            else if ((source.getPixel(x, y) == SPIKE2_COLOR))
            {
                sf::Vector2f spike2_location(50 * x + 25, 50 * y +38);
                m_static_objects.push_back(std::make_unique<Spike>(Spike2, spike2_location));
            }
            else if ((source.getPixel(x, y) == JUMPER1_COLOR))
            {
                sf::Vector2f jumper1_location(50 * x + 25, 50 * y + 38);
                m_static_objects.push_back(std::make_unique<Jumper>(Jumper1, jumper1_location));
            }
            else if ((source.getPixel(x, y) == JUMPER2_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Jumper>(Jumper2, location));
            }
        }
    }
}


