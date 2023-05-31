#pragma once

#include "Board.h"

Board::Board()
	:m_gravity(0.0f,9.8f), m_world(m_gravity)
{
    m_background.setTexture(Resources::instance().getGameTexture(Level_Background));
    m_background.scale(1.6f, 1.6f);

    createPlayerBox();
    createLevel();
}

void Board::drawBoard(sf::RenderWindow& window)
{
    window.draw(m_background);
    for (int brick = 0; brick < m_game_floor.size(); brick++)
    {
        window.draw(m_game_floor[brick]);
    }
    for (int spike = 0; spike < m_spikes.size(); spike++)
    {
        window.draw(m_spikes[spike]);
    }
    window.draw(m_player_box);

}

void Board::moveObjects()
{
    // Update Box2D world
    float timeStep = 1.0f / 60.0f; // Adjust the time step as needed
    int32 velocityIterations = 6; // Adjust the iterations as needed
    int32 positionIterations = 2; // Adjust the iterations as needed
    m_world.Step(timeStep, velocityIterations, positionIterations);
    m_player_box.setPosition(SCALE * m_player_body->GetPosition().x, SCALE * m_player_body->GetPosition().y);
    m_player_box.setRotation(m_player_body->GetAngle() * 180 / b2_pi);
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


b2Vec2 Board::getPlayerPosition()
{
    return m_player_body->GetPosition();
}

void Board::viewBackground(float addition)
{
    m_background.setPosition(m_background.getPosition().x +addition , m_background.getPosition().y);
}

void Board::createPlayerBox()
{
    m_player_box.setTexture(Resources::instance().getGameTexture(PlayerBox));
    m_player_box.setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2);

    // Create a Box2D body definition for the player box
    b2BodyDef bodyDef;
    bodyDef.position.Set(m_player_box.getPosition().x / SCALE, m_player_box.getPosition().y / SCALE); 
    bodyDef.type = b2_dynamicBody; // Set the body type to dynamic

    // Create the Box2D body in the world
    b2Body* body = m_world.CreateBody(&bodyDef);

    // Create a Box2D shape for the player box
    b2PolygonShape shape;
    sf::Vector2u boxSize = Resources::instance().getGameTexture(PlayerBox).getSize();
    shape.SetAsBox(boxSize.x / 2.0f / SCALE, boxSize.y / 2.0f / SCALE);

    // Create a fixture definition for the player box shape
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f; 
    fixtureDef.friction = 0.3f;

    // Attach the fixture to the player box body
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
                sf::Vector2u spike_size = Resources::instance().getGameTexture(Spike).getSize();
                sf::Sprite spike;
                spike.setTexture(Resources::instance().getGameTexture(Spike));
                spike.setPosition(50 * x, 50 * y);
                m_spikes.push_back(spike);
                createPhysicalBody(spike, spike_size);

            }
            else if ((source.getPixel(x, y) == Black))
            {
                sf::Vector2u brick_size = Resources::instance().getGameTexture(Brick).getSize();
                sf::Sprite brick;
                brick.setTexture(Resources::instance().getGameTexture(Brick));
                brick.setPosition(50 * x, 50 * y);
                m_game_floor.push_back(brick);
                createPhysicalBody(brick, brick_size);
            }
            else if ((source.getPixel(x, y) == Grey))
            {
                sf::Vector2u cube_cube_size = Resources::instance().getGameTexture(CubeCube).getSize();
                sf::Sprite cube_cube;
                cube_cube.setTexture(Resources::instance().getGameTexture(CubeCube));
                cube_cube.setPosition(50 * x, 50 * y);
                m_game_floor.push_back(cube_cube);
                createPhysicalBody(cube_cube, cube_cube_size);
            }
            else if ((source.getPixel(x, y) == Blue))
            {
                sf::Vector2u cube1_size = Resources::instance().getGameTexture(Cube1).getSize();
                sf::Sprite cube1;
                cube1.setTexture(Resources::instance().getGameTexture(Cube1));
                cube1.setPosition(50 * x, 50 * y);
                m_game_floor.push_back(cube1);
                createPhysicalBody(cube1, cube1_size);
            }
            else if ((source.getPixel(x, y) == Cyan))
            {
                sf::Vector2u cube2_size = Resources::instance().getGameTexture(Cube2).getSize();
                sf::Sprite cube2;
                cube2.setTexture(Resources::instance().getGameTexture(Cube2));
                cube2.setPosition(50 * x, 50 * y);
                m_game_floor.push_back(cube2);
                createPhysicalBody(cube2, cube2_size);
            }
            else if ((source.getPixel(x, y) == Yellow))
            {
                sf::Vector2u coin_size = Resources::instance().getGameTexture(Coin).getSize();
                sf::Sprite coin;
                coin.setTexture(Resources::instance().getGameTexture(Coin));
                coin.setPosition(50 * x, 50 * y);
                m_game_floor.push_back(coin);
            }
            else if ((source.getPixel(x, y) == Orange))
            {
                sf::Vector2u gate_size = Resources::instance().getGameTexture(Gate1).getSize();
                sf::Sprite gate;
                gate.setTexture(Resources::instance().getGameTexture(Gate1));
                gate.setPosition(50 * x, 50 * y);
                m_game_floor.push_back(gate);
                createPhysicalBody(gate, gate_size);
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


//void Board::createFloor(int length, GameTextures texture)
//{
//    sf::Vector2u brick_size = Resources::instance().getGameTexture(texture).getSize();
//    float yPos = static_cast<float>(WINDOW_HEIGHT) - brick_size.y; // Position the sprites at the bottom of the window
//
//    for (int bricks = 0; bricks < length; ++bricks)
//    {
//        sf::Sprite brick;
//        brick.setTexture(Resources::instance().getGameTexture(texture));
//
//        // Position the first sprite on the lower left side of the window
//        if (bricks == 0)
//        {
//            float xPos = 0.0f;
//            brick.setPosition(xPos, yPos);
//        }
//        else
//        {
//            sf::Sprite prev_brick = m_game_floor[bricks - 1];
//            float xPos = prev_brick.getPosition().x + prev_brick.getGlobalBounds().width;
//            brick.setPosition(xPos, yPos);
//        }
//        m_game_floor.push_back(brick);
//
//        b2BodyDef bodyDef;
//        bodyDef.position.Set(brick.getPosition().x / SCALE, brick.getPosition().y / SCALE); 
//        bodyDef.type = b2_staticBody; 
//
//        b2Body* body = m_world.CreateBody(&bodyDef);
//
//
//        b2PolygonShape shape;
//        shape.SetAsBox(brick_size.x / 2.0f / SCALE, brick_size.y / 2.0f / SCALE); 
//        b2FixtureDef fixtureDef;
//        fixtureDef.shape = &shape;
//
//        body->CreateFixture(&fixtureDef);
//
//        m_floor_bodies.push_back(body);
//    }
//}
