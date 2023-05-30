#pragma once

#include "Board.h"

Board::Board()
	:m_gravity(0.0f,9.8f), m_world(m_gravity)
{
    m_background.setTexture(Resources::instance().getGameTexture(Level_Background));
    m_background.scale(1.6f, 1.6f);

    createPlayerBox();
    createFloor(10, Floor);

}

void Board::drawBoard(sf::RenderWindow& window)
{
    window.draw(m_background);
    for (int brick = 0; brick < m_game_floor.size(); brick++)
    {
        window.draw(m_game_floor[brick]);
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
    //m_world.Step(1 / 60.f, 8, 3);
    m_player_box.setPosition(SCALE * m_player_body->GetPosition().x, SCALE * m_player_body->GetPosition().y);
    m_player_box.setRotation(m_player_body->GetAngle() * 180 / b2_pi);
}

void Board::jumpPlayer()
{
    b2Vec2 velocity = m_player_body->GetLinearVelocity();
    float currentHeight = m_player_body->GetPosition().y * SCALE;
    if (currentHeight < MAX_JUMP_HEIGHT)
    {
        float jumpForceToApply = JUMP_FORCE;
        if (currentHeight + jumpForceToApply > MAX_JUMP_HEIGHT)
        {
            jumpForceToApply = MAX_JUMP_HEIGHT - currentHeight;
        }
        m_player_body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -jumpForceToApply), true);
    }
}

void Board::movePlayerRight()
{
    float currentSpeed = m_player_body->GetLinearVelocity().x;
    if (currentSpeed < MAX_MOVEMENT_SPEED)
    {
        float forceToApply = MOVEMENT_FORCE;
        if (currentSpeed + forceToApply > MAX_MOVEMENT_SPEED)
        {
            forceToApply = MAX_MOVEMENT_SPEED - currentSpeed;
        }
        m_player_body->ApplyForceToCenter(b2Vec2(forceToApply, 0.0f), true);
    }
}

void Board::movePlayerLeft()
{
    float currentSpeed = m_player_body->GetLinearVelocity().x;
    if (currentSpeed > -MAX_MOVEMENT_SPEED)
    {
        float forceToApply = -MOVEMENT_FORCE;
        if (currentSpeed + forceToApply < -MAX_MOVEMENT_SPEED)
        {
            forceToApply = -MAX_MOVEMENT_SPEED - currentSpeed;
        }
        m_player_body->ApplyForceToCenter(b2Vec2(forceToApply, 0.0f), true);
    }
}

void Board::createPlayerBox()
{
    m_player_box.setTexture(Resources::instance().getGameTexture(PlayerBox));
    m_player_box.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2); /// todo change

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


void Board::createFloor(int length, GameTextures texture)
{
    sf::Vector2u brick_size = Resources::instance().getGameTexture(texture).getSize();
    float yPos = static_cast<float>(WINDOW_HEIGHT) - brick_size.y; // Position the sprites at the bottom of the window

    for (int bricks = 0; bricks < length; ++bricks)
    {
        sf::Sprite brick;
        brick.setTexture(Resources::instance().getGameTexture(texture));

        // Position the first sprite on the lower left side of the window
        if (bricks == 0)
        {
            float xPos = 0.0f;
            brick.setPosition(xPos, yPos);
        }
        else
        {
            sf::Sprite prev_brick = m_game_floor[bricks - 1];
            float xPos = prev_brick.getPosition().x + prev_brick.getGlobalBounds().width;
            brick.setPosition(xPos, yPos);
        }
        m_game_floor.push_back(brick);

        // Create a Box2D body definition for the floor sprite
        b2BodyDef bodyDef;
        // Divide by SCALE to convert from pixel coordinates to Box2D meters
        bodyDef.position.Set(brick.getPosition().x / SCALE, brick.getPosition().y / SCALE); 
        bodyDef.type = b2_staticBody; // Set the body type to static

        // Create the Box2D body in the world
        b2Body* body = m_world.CreateBody(&bodyDef);

        // Create a Box2D shape for the floor sprite
        b2PolygonShape shape;
        // Divide by SCALE to convert from pixel sizes to Box2D meters
        shape.SetAsBox(brick_size.x / 2.0f / SCALE, brick_size.y / 2.0f / SCALE); 

        // Create a fixture definition for the floor shape
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;

        // Attach the fixture to the floor body
        body->CreateFixture(&fixtureDef);

        // Store the floor body for future reference
        m_floor_bodies.push_back(body);
    }
}
