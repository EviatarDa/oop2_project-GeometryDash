#pragma once

#include "StaticObject.h"

StaticObject::StaticObject(b2World& world, GameTextures texture, sf::Vector2f location)
{
    //grafics
    m_object.setTexture(Resources::instance().getGameTexture(texture));
    sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);
    m_object.setOrigin(sprite_size.x / 2, sprite_size.y / 2);
    m_object.setPosition(location);

    //physics
    b2BodyDef bodyDef;
    bodyDef.position.Set(m_object.getPosition().x / SCALE, m_object.getPosition().y / SCALE);
    bodyDef.type = b2_staticBody;

    m_object_body = world.CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(sprite_size.x / 2.0f / SCALE, sprite_size.y / 2.0f / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    m_object_body->CreateFixture(&fixtureDef);
}

StaticObject::StaticObject(GameTextures texture, sf::Vector2f location)
    :m_object_body(nullptr)
{
    if (texture == Spike2)
    {
        sf::Vector2f locationn = location;
    }
    //grafics
    m_object.setTexture(Resources::instance().getGameTexture(texture));
    sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);
    m_object.setOrigin(sprite_size.x / 2, sprite_size.y / 2);
    m_object.setPosition(location);
}

StaticObject::~StaticObject()
{
	// Reset the pointer to null
	m_object_body = nullptr; 
}

void StaticObject::draw(sf::RenderWindow& window)
{
    window.draw(m_object);
}

b2Body* StaticObject::getBody() const
{
    return m_object_body;
}
