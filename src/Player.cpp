#pragma once

#include "Player.h"


Player::Player(b2World& world, std::pair<GameTextures, GameTextures> textures, sf::Vector2f location /*b2Vec2& gravity*/)
    :MovingObject(world, textures.first, location),
    m_player_textures(textures),
    m_state(std::make_unique<BoxState>()),
    m_points(0),
    m_first_location(m_object_body->GetPosition())
    //m_world(world),
    //m_gravity(gravity)
{
    //shipState();
}

void Player::move()
{
    m_state->move(m_direction, m_object_body, m_touching_ground);
    m_object.setPosition(SCALE * m_object_body->GetPosition().x, SCALE * m_object_body->GetPosition().y);
    m_object.setRotation(m_object_body->GetAngle() * 180 / b2_pi);
}

void Player::updateDirection()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_direction[Left] = true;
        m_direction[Stay] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_direction[Right] = true;
        m_direction[Stay] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_direction[Up] = true;
        m_direction[Stay] = false;
    }
}

void Player::shipState()
{
    changeBodyAndSprite(m_player_textures.second);
    m_state.reset(new ShipState());
}

void Player::boxState()
{
    changeBodyAndSprite(m_player_textures.first);
    m_state.reset(new BoxState());
}

void Player::increasePoints()
{
    m_points++;
}

void Player::kill()
{
    if (dynamic_cast<ShipState*>(m_state.get()) != nullptr)
    {
        boxState();
    }
    m_object_body->SetTransform(m_first_location, m_object_body->GetAngle());
    m_alive = true;
}

void Player::releaseRight()
{
    m_direction[Right] = false;
    m_direction[Stay] = true;
}

void Player::releaseLeft()
{
    m_direction[Left] = false;
    m_direction[Stay] = true;
}

void Player::releaseSpace()
{
    m_direction[Up] = false;
    m_direction[Stay] = true;
}

void Player::hop(float hop_force)
{
    //to avoid "icetower" jumps
    m_object_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    m_object_body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -hop_force), true);
}

void Player::reverseGravity()
{
    //m_gravity = -m_gravity;
    //m_world.SetGravity(m_gravity);
}

void Player::collideBrick(GameTextures brick_type)
{
    if (brick_type != Floor)
        m_state->collideBrick(m_touching_ground, m_alive);
    else
        m_touching_ground = true;
}

void Player::handleMarking()
{
    if (dynamic_cast<ShipState*>(m_state.get()) != nullptr)
    {
        boxState();
    }
    else
        shipState();
    m_marked = false;
}



void Player::changeBodyAndSprite(GameTextures game_texture)
{
    m_object.setTexture(Resources::instance().getGameTexture(game_texture), true);
    sf::Vector2f spriteSize(m_object.getTextureRect().width, m_object.getTextureRect().height);
    m_object.setOrigin(spriteSize.x / 2, spriteSize.y / 2);

    //create new shape
    b2PolygonShape shape;
    sf::Vector2u boxSize = Resources::instance().getGameTexture(game_texture).getSize();
    shape.SetAsBox(boxSize.x / 2.0f / SCALE, boxSize.y / 2.0f / SCALE);

    //distroy the old fixture
    m_object_body->DestroyFixture(m_object_body->GetFixtureList());

    //change the fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    m_object_body->CreateFixture(&fixtureDef);
}
