#pragma once

#include "Board.h"

Board::Board(sf::RenderWindow& window)
	:m_window(window), m_gravity(0.0f,9.8f), m_world(m_gravity)
{
    m_background.setTexture(Resources::instance().getGameTexture(Level_Background));
    m_background.scale(1.6f, 1.6f);

    m_moving_objects.push_back(std::make_unique<Player>(m_world, PlayerBox));

    //createPlayerBox();
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

    //m_player_box.setPosition(SCALE * m_player_body->GetPosition().x, SCALE * m_player_body->GetPosition().y);
    //m_player_box.setRotation(m_player_body->GetAngle() * 180 / b2_pi);
}

void Board::jumpPlayer()
{
    m_player_body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -JUMP_FORCE), true);
}

void Board::movePlayerRight()
{
    float currentSpeed_y = m_player_body->GetLinearVelocity().y;
    m_player_body->SetLinearVelocity({ MOVEMENT_SPEED, currentSpeed_y });
}

void Board::movePlayerLeft()
{
    float currentSpeed_y = m_player_body->GetLinearVelocity().y;
    m_player_body->SetLinearVelocity({ -MOVEMENT_SPEED, currentSpeed_y });
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

void Board::createPlayerBox()
{
    m_player_box.setTexture(Resources::instance().getGameTexture(PlayerBox));
    sf::Vector2f spriteSize(m_player_box.getTextureRect().width, m_player_box.getTextureRect().height);
    m_player_box.setOrigin(spriteSize.x / 2, spriteSize.y / 2);
    m_player_box.setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2);
   

    b2BodyDef bodyDef;
    bodyDef.position.Set(m_player_box.getPosition().x / SCALE, m_player_box.getPosition().y / SCALE); 
    bodyDef.type = b2_dynamicBody; // Set the body type to dynamic

    b2Body* body = m_world.CreateBody(&bodyDef);
    b2PolygonShape shape;
    sf::Vector2u boxSize = Resources::instance().getGameTexture(PlayerBox).getSize();
    shape.SetAsBox(boxSize.x / 2.0f / SCALE, boxSize.y / 2.0f / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f; 
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    m_player_body = body;
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
                sf::Vector2u spike_size = Resources::instance().getGameTexture(Spike1).getSize();
                sf::Sprite spike;
                spike.setOrigin(spike_size.x / 2, spike_size.y / 2);
                spike.setTexture(Resources::instance().getGameTexture(Spike1));
                spike.setPosition(50 * x+25, 50 * y+25);
        
                m_game_floor.push_back(spike);
                //createPhysicalBody(spike, spike_size);
            }
            else if ((source.getPixel(x, y) == Black))
            {
                sf::Vector2u brick_size = Resources::instance().getGameTexture(Brick).getSize();
                sf::Sprite brick;
                brick.setTexture(Resources::instance().getGameTexture(Brick));
                brick.setOrigin(brick_size.x / 2, brick_size.y / 2);
                brick.setPosition(50 * x + 25, 50 * y + 25);
                m_game_floor.push_back(brick);
                createPhysicalBody(brick, brick_size);
            }
            else if ((source.getPixel(x, y) == Grey))
            {
                sf::Vector2u cube_cube_size = Resources::instance().getGameTexture(CubeCube).getSize();
                sf::Sprite cube_cube;
                cube_cube.setTexture(Resources::instance().getGameTexture(CubeCube));
                cube_cube.setOrigin(cube_cube_size.x / 2, cube_cube_size.y / 2);
                cube_cube.setPosition(50 * x + 25, 50 * y + 25);
                m_game_floor.push_back(cube_cube);
                createPhysicalBody(cube_cube, cube_cube_size);
            }
            else if ((source.getPixel(x, y) == Blue))
            {
                sf::Vector2u cube1_size = Resources::instance().getGameTexture(Cube1).getSize();
                sf::Sprite cube1;
                cube1.setTexture(Resources::instance().getGameTexture(Cube1));
                cube1.setOrigin(cube1_size.x / 2, cube1_size.y / 2);
                cube1.setPosition(50 * x + 25, 50 * y + 25);
                m_game_floor.push_back(cube1);
                createPhysicalBody(cube1, cube1_size);
            }
            else if ((source.getPixel(x, y) == Cyan))
            {
                sf::Vector2u cube2_size = Resources::instance().getGameTexture(Cube2).getSize();
                sf::Sprite cube2;
                cube2.setTexture(Resources::instance().getGameTexture(Cube2));
                cube2.setOrigin(cube2_size.x / 2, cube2_size.y / 2);
                cube2.setPosition(50 * x + 25, 50 * y + 25);
                m_game_floor.push_back(cube2);
                createPhysicalBody(cube2, cube2_size);
            }
            else if ((source.getPixel(x, y) == Yellow))
            {
                sf::Vector2u coin_size = Resources::instance().getGameTexture(Coin).getSize();
                sf::Sprite coin;
                coin.setTexture(Resources::instance().getGameTexture(Coin));
                coin.setOrigin(coin_size.x / 2, coin_size.y / 2);
                coin.setPosition(50 * x + 25, 50 * y + 25);
                m_game_floor.push_back(coin);
            }
            else if ((source.getPixel(x, y) == Orange))
            {
                sf::Vector2u gate_size = Resources::instance().getGameTexture(Gate1).getSize();
                sf::Sprite gate;
                gate.setTexture(Resources::instance().getGameTexture(Gate1));
                gate.setOrigin(gate_size.x / 2, gate_size.y / 2);
                gate.setPosition(50 * x + 25, 50 * y + 25);
                m_game_floor.push_back(gate);
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



