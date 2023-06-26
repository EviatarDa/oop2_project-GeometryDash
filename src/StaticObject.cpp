#pragma once

#include "StaticObject.h"

StaticObject::StaticObject(b2World& world, const GameTextures texture, const sf::Vector2f location)
    :GameObject(texture, location), m_type(texture)
{
    //keep the size
    const sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);

    //physics
    b2BodyDef bodyDef; // difine body
    bodyDef.position.Set(m_object.getPosition().x / SCALE, m_object.getPosition().y / SCALE); //locate it
    bodyDef.type = b2_staticBody; // define static
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this); // define its pointer for the collision 

    m_object_body = world.CreateBody(&bodyDef); //pushing the body to the world
    b2PolygonShape shape; //define shapr
    shape.SetAsBox(sprite_size.x / 2.0f / SCALE, sprite_size.y / 2.0f / SCALE); // set box
    b2FixtureDef fixtureDef; // define fixture
    fixtureDef.shape = &shape;
    m_object_body->CreateFixture(&fixtureDef); //pushing to body
}

StaticObject::~StaticObject()
{
    m_object_body->DestroyFixture(m_object_body->GetFixtureList());
    m_object_body = nullptr;
}

const GameTextures StaticObject::getType() const
{
    return m_type;
}

void StaticObject::setDelete()
{
    m_delete = true;
}

const bool StaticObject::getDelete()const
{
    return m_delete;
}

const bool StaticObject::isActive()const
{
    return m_active;
}

void StaticObject::inactive()
{
    m_active = false;
}

void StaticObject::shutDown()
{
    //shuting down objct by deleting 
    m_object.setColor(sf::Color::Red);
    m_object_body->DestroyFixture(m_object_body->GetFixtureList());

    //starting count the incative time
    m_inactive_timer = m_clock.getElapsedTime();
    m_active = true;
    m_fixture_destroyed = true;
}

void StaticObject::restart()
{
    //restart the object if 5 sec passed
    const sf::Time elapsed = m_clock.getElapsedTime() - m_inactive_timer;
    if (elapsed >= sf::seconds(5.0f)) {
        if (m_fixture_destroyed) {

            m_object.setColor(sf::Color(255,255,255));

            //physics - creatiing again the fixture 
            const sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);
            b2PolygonShape shape;
            shape.SetAsBox(sprite_size.x / 2.0f / SCALE, sprite_size.y / 2.0f / SCALE);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            m_object_body->CreateFixture(&fixtureDef);
            m_fixture_destroyed = false;
        }
    }
}
