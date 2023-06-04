#pragma once

#include "MovingObject.h"

MovingObject::MovingObject(b2World& world, GameTextures texture)
    :m_world(world)
{
    //grafics
    m_object.setTexture(Resources::instance().getGameTexture(texture));
    sf::Vector2f spriteSize(m_object.getTextureRect().width, m_object.getTextureRect().height);
    m_object.setOrigin(spriteSize.x / 2, spriteSize.y / 2);
    m_object.setPosition(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2);

    //physics
    b2BodyDef bodyDef;
    bodyDef.position.Set(m_object.getPosition().x / SCALE, m_object.getPosition().y / SCALE);
    bodyDef.type = b2_dynamicBody; // Set the body type to dynamic

    m_object_body = world.CreateBody(&bodyDef);
    b2PolygonShape shape;
    sf::Vector2u boxSize = Resources::instance().getGameTexture(texture).getSize();
    shape.SetAsBox(boxSize.x / 2.0f / SCALE, boxSize.y / 2.0f / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    m_object_body->CreateFixture(&fixtureDef);

}

MovingObject::~MovingObject()
{
    //m_world.DestroyBody(m_object_body);
}


void MovingObject::draw(sf::RenderWindow& window)
{
    window.draw(m_object);
}

b2Vec2 MovingObject::getPosition()
{
    return m_object_body->GetPosition();
}
