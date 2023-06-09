#pragma once

#include "StaticObject.h"

StaticObject::StaticObject(b2World& world, GameTextures texture, sf::Vector2f location)
    :GameObject(texture, location),
    m_type(texture)
{

    sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);

    //physics
    b2BodyDef bodyDef;
    bodyDef.position.Set(m_object.getPosition().x / SCALE, m_object.getPosition().y / SCALE);
    bodyDef.type = b2_staticBody;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    m_object_body = world.CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(sprite_size.x / 2.0f / SCALE, sprite_size.y / 2.0f / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    m_object_body->CreateFixture(&fixtureDef);
}

StaticObject::StaticObject(GameTextures texture, sf::Vector2f location)
    :GameObject(texture, location)
{
    //grafics
    m_object.setTexture(Resources::instance().getGameTexture(texture));
    sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);
    m_object.setOrigin(sprite_size.x / 2, sprite_size.y / 2);
    m_object.setPosition(location);
}

StaticObject::~StaticObject()
{
    m_object_body->DestroyFixture(m_object_body->GetFixtureList());
    m_object_body = nullptr;

}

GameTextures StaticObject::getType()
{
    return m_type;
}

void StaticObject::setDelete()
{
    m_delete = true;
}

bool StaticObject::getDelete()
{
    return m_delete;
}
