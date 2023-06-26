#pragma once

#include "MovingObject.h"

MovingObject::MovingObject( b2World& world, const GameTextures texture, const sf::Vector2f location)
    :GameObject(texture, location)
{
    //getting the sprite size
    const sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);

    //physics
    b2BodyDef bodyDef; //define body
    bodyDef.position.Set(m_object.getPosition().x / SCALE, m_object.getPosition().y / SCALE); //poses the body
    bodyDef.type = b2_dynamicBody; // Set the body type to dynamic

    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this); // update the pointer to return himself

    m_object_body = world.CreateBody(&bodyDef); // pushing body into the board world
    b2PolygonShape shape; //define the body  shape
    shape.SetAsBox(sprite_size.x / 2.0f / SCALE, sprite_size.y / 2.0f / SCALE); // shape size
    b2FixtureDef fixtureDef; // define fuxture
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    m_object_body->CreateFixture(&fixtureDef); //pushing the fixture into the body
}


const b2Vec2 MovingObject::getPosition()const
{
    return m_object_body->GetPosition();
}


