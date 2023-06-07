#pragma once

#include "MovingObject.h"

MovingObject::MovingObject(b2World& world, GameTextures texture, sf::Vector2f location)
{
    //grafics
    m_object.setTexture(Resources::instance().getGameTexture(texture));
    sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);
    m_object.setOrigin(sprite_size.x / 2, sprite_size.y / 2);
    //m_object.setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2);
    m_object.setPosition(location);

    //physics
    b2BodyDef bodyDef;
    bodyDef.position.Set(m_object.getPosition().x / SCALE, m_object.getPosition().y / SCALE);
    bodyDef.type = b2_dynamicBody; // Set the body type to dynamic

    m_object_body = world.CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(sprite_size.x / 2.0f / SCALE, sprite_size.y / 2.0f / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    m_object_body->CreateFixture(&fixtureDef);
}

MovingObject::~MovingObject()
{
    // Reset the pointer to null
    m_object_body = nullptr; 
}


void MovingObject::draw(sf::RenderWindow& window)
{
    window.draw(m_object);
}

b2Vec2 MovingObject::getPosition()
{
    return m_object_body->GetPosition();
}

b2Body* MovingObject::getBody()const
{
    return m_object_body;
}
