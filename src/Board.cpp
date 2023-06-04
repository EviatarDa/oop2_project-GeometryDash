#pragma once

#include "Board.h"

Board::Board(sf::RenderWindow& window)
	:m_window(window), m_gravity(0.0f,9.8f), m_world(m_gravity)
{
    m_background.setTexture(Resources::instance().getGameTexture(Level_Background));
    m_background.scale(1.6f, 1.6f);

    m_moving_objects.push_back(std::make_unique<Player>(m_world, PlayerBox));
    createLevel();
}

void Board::drawBoard()
{
    m_window.draw(m_background);
    for (int brick = 0; brick < m_game_floor.size(); brick++)
    {
        m_window.draw(m_game_floor[brick]);
    }
    for (int object = 0; object < m_moving_objects.size(); object++)
    {
        m_moving_objects[object]->draw(m_window);
    }
    //window.draw(m_player_box);
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
    return m_moving_objects[0]->getPosition();
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


void Board::createLevel()
{
    const sf::Image& source = Resources::instance().getGameMaps(Map1);

    for (size_t y = 0; y < source.getSize().y; ++y)
    {
        for (size_t x = 0; x < source.getSize().x; ++x)
        {
            if (source.getPixel(x, y) == Red)
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Spike1);
        
                m_game_floor.push_back(result.first);
                //createPhysicalBody(spike, spike_size);
            }
            else if ((source.getPixel(x, y) == Black))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Brick);
                m_game_floor.push_back(result.first);
                createPhysicalBody(result.first, result.second);
            }
            else if ((source.getPixel(x, y) == Grey))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, CubeCube);
                m_game_floor.push_back(result.first);
                createPhysicalBody(result.first, result.second);
            }
            else if ((source.getPixel(x, y) == Blue))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Cube1);
                m_game_floor.push_back(result.first);
                createPhysicalBody(result.first, result.second);
            }
            else if ((source.getPixel(x, y) == Cyan))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Cube2);
                m_game_floor.push_back(result.first);
                createPhysicalBody(result.first, result.second);
            }
            else if ((source.getPixel(x, y) == Yellow))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Coin);
                m_game_floor.push_back(result.first);
            }
            else if ((source.getPixel(x, y) == Orange))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Gate1);
                m_game_floor.push_back(result.first);
               // createPhysicalBody(gate, gate_size);
            }
        }

    }
}

void Board::createPhysicalBody(const sf::Sprite& sprite, const sf::Vector2u sprite_size)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);
    bodyDef.type = b2_staticBody;
    b2Body* body = m_world.CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(sprite_size.x / 2.0f / SCALE, sprite_size.y / 2.0f / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    m_floor_bodies.push_back(body);
}

std::pair<sf::Sprite, sf::Vector2u> Board::createSprite(const int x,const int y,const GameTextures texture)
{
    sf::Vector2u object_size = Resources::instance().getGameTexture(CubeCube).getSize();

    sf::Sprite sprite;
    sprite.setTexture(Resources::instance().getGameTexture(texture));
    sprite.setOrigin(object_size.x / 2, object_size.y / 2);
    sprite.setPosition(50 * x + 25, 50 * y + 25);

    return std::make_pair(sprite, object_size);
}



