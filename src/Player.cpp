#pragma once

#include "Player.h"


Player::Player(b2World& world, GameTextures texture)
	:MovingObject(world, texture),
     m_state(std::make_unique<BoxState>())
{
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
    //to change
    m_object.setTexture(Resources::instance().getGameTexture(PlayerShip));
    m_state.reset(new ShipState());
}

void Player::boxState()
{
    //to change
    m_object.setTexture(Resources::instance().getGameTexture(PlayerBox));
    m_state.reset(new BoxState());
}
