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

bool StaticObject::isActive()
{
    return m_active;
}

void StaticObject::inactive()
{
    m_active = false;
}

void StaticObject::shutDown()
{
    m_object.setColor(sf::Color::Red);
    m_object_body->DestroyFixture(m_object_body->GetFixtureList());
    m_inactive_timer = m_clock.getElapsedTime();
    m_active = true;
    m_fixture_destroyed = true;
}

void StaticObject::restart()
{
    sf::Time elapsed = m_clock.getElapsedTime() - m_inactive_timer;
    if (elapsed >= sf::seconds(5.0f)) {
        if (m_fixture_destroyed) {

            m_object.setColor(sf::Color(255,255,255));

            //physics
            sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);
            b2PolygonShape shape;
            shape.SetAsBox(sprite_size.x / 2.0f / SCALE, sprite_size.y / 2.0f / SCALE);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            m_object_body->CreateFixture(&fixtureDef);
            m_fixture_destroyed = false;
        }
    }
}
