#pragma once

#include "Board.h"
class Brick;

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
    for (int brick = 0; brick < m_game_floor.size(); brick++)
    {
        m_window.draw(m_game_floor[brick]);
    }
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

void Board::changeBoxShip(std::pair<GameTextures, GameTextures> player_textures)
{
    //delete the old player body
    if (m_moving_objects[0]->getBody() != nullptr)
        m_world.DestroyBody(m_moving_objects[0]->getBody());

    //create the new player
    m_player_textures = player_textures;
    m_moving_objects[0] = std::make_unique<Player>(m_world, m_player_textures);
}


void Board::createLevel()
{
    m_moving_objects.push_back(std::make_unique<Player>(m_world, m_player_textures));

    const sf::Image& source = Resources::instance().getGameMaps(Map1);
    for (size_t y = 0; y < source.getSize().y; ++y)
    {
        for (size_t x = 0; x < source.getSize().x; ++x)
        {
            sf::Vector2f location(50 * x + 25, 50 * y + 25);
            if (source.getPixel(x, y) == SPIKE1_COLOR)
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Spike1);
        
                m_game_floor.push_back(result.first);
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
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Coin);
                m_game_floor.push_back(result.first);
            }
            else if ((source.getPixel(x, y) == GATE1_COLOR))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Gate1);
                m_game_floor.push_back(result.first);
            }
            else if ((source.getPixel(x, y) == RECTANGLE_COLOR))
            {
                m_static_objects.push_back(std::make_unique<Brick>(m_world, Rectangle, location));
            }
            else if ((source.getPixel(x, y) == SPIKES_COLOR))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Spikes);
                m_game_floor.push_back(result.first);
            }
            else if ((source.getPixel(x, y) == SPIKE2_COLOR))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Spike2);
                m_game_floor.push_back(result.first);
            }
            else if ((source.getPixel(x, y) == JUMPER1_COLOR))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Jumper1);
                m_game_floor.push_back(result.first);
            }
            else if ((source.getPixel(x, y) == JUMPER2_COLOR))
            {
                std::pair<sf::Sprite, sf::Vector2u> result = createSprite(x, y, Jumper2);
                m_game_floor.push_back(result.first);
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



