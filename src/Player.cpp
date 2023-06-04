#pragma once

#include "Player.h"


Player::Player(b2World& world, GameTextures texture)
	:MovingObject(world, texture),
     m_state(std::make_unique<BoxState>())
{
    shipState();
}

void Player::move()
{
    m_state->move(m_direction, m_object_body);

    m_object.setPosition(SCALE * m_object_body->GetPosition().x, SCALE * m_object_body->GetPosition().y);
    m_object.setRotation(m_object_body->GetAngle() * 180 / b2_pi);
}

void Player::updateDirection()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_direction = Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_direction = Right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_direction = Up;
    }
    else
    {
        m_direction = Stay;
    }
}

void Player::shipState()
{
    m_object.setTexture(Resources::instance().getGameTexture(PlayerShip), true);
    sf::Vector2f spriteSize(m_object.getTextureRect().width, m_object.getTextureRect().height);
    m_object.setOrigin(spriteSize.x / 2, spriteSize.y / 2);

    //create new shape
    b2PolygonShape shape;
    sf::Vector2u boxSize = Resources::instance().getGameTexture(PlayerShip).getSize();
    shape.SetAsBox(boxSize.x / 2.0f / SCALE, boxSize.y / 2.0f / SCALE);

    //distroy the old fixture
    m_object_body->DestroyFixture(m_object_body->GetFixtureList());

    //change the fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    m_object_body->CreateFixture(&fixtureDef);

    m_state.reset(new ShipState());
}

void Player::boxState()
{
    //to change
    m_object.setTexture(Resources::instance().getGameTexture(PlayerBox));
    m_state.reset(new BoxState());
}
