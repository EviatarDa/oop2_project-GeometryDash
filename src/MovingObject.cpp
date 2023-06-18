#pragma once

#include "MovingObject.h"

MovingObject::MovingObject(b2World& world, GameTextures texture, sf::Vector2f location)
    :GameObject(texture, location)
{
    sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);

    //physics
    b2BodyDef bodyDef;
    bodyDef.position.Set(m_object.getPosition().x / SCALE, m_object.getPosition().y / SCALE);
    bodyDef.type = b2_dynamicBody; // Set the body type to dynamic
    //bodyDef.angularDamping = 1.0f;  // Set a non-zero angular damping value
    //bodyDef.fixedRotation = true;  // Set the fixedRotation flag to true

    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    m_object_body = world.CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(sprite_size.x / 2.0f / SCALE, sprite_size.y / 2.0f / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    m_object_body->CreateFixture(&fixtureDef);

    // Set a high moment of inertia to prevent rotation
    //b2MassData massData;
    //m_object_body->GetMassData(&massData);
    //massData.I = 1e9f;  // Set a high moment of inertia
    //m_object_body->SetMassData(&massData);
}


b2Vec2 MovingObject::getPosition()
{
    return m_object_body->GetPosition();
}


void MovingObject::setDead()
{
    m_alive = false;
}

bool MovingObject::isAlive()
{
    return m_alive;
}

//void MovingObject::setState()
//{
//    m_state_change = true;
//}

void MovingObject::setGravity()
{
    m_gravity_changed = true;
}

bool MovingObject::isGravityMarked()
{
    if (m_gravity_changed)
    {
        m_gravity_changed = false;
        return true;
    }
    else
        return m_gravity_changed;
}

//bool MovingObject::isStateMarked()
//{
//    return m_state_change;
//}
