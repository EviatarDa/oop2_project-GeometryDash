#pragma once

#include "Player.h"


Player::Player(b2World& world, GameTextures texture)
	:MovingObject(world, texture)
{
}

void Player::move()
{
    switch (m_direction)
    {
    case Up:
    {
        if(true)//to change
        {
            m_object_body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -JUMP_FORCE), true);
        }
        break;
    }
    case Right:
    {
        float currentSpeed_y = m_object_body->GetLinearVelocity().y;
        m_object_body->SetLinearVelocity({ MOVEMENT_SPEED, currentSpeed_y });
        break;
    }

    case Left:
    {
        float currentSpeed_y = m_object_body->GetLinearVelocity().y;
        m_object_body->SetLinearVelocity({ -MOVEMENT_SPEED, currentSpeed_y });
        break;
    }

    case Stay:
    {
        float currentSpeed_y = m_object_body->GetLinearVelocity().y;
        m_object_body->SetLinearVelocity({ 0, currentSpeed_y });
        break;
    }

    default:
        break;
    }

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
