#pragma once

#include "Player.h"


Player::Player(b2World& world, const std::pair<GameTextures, GameTextures> textures, const sf::Vector2f location)
    :MovingObject(world, textures.first, location),
    m_player_textures(textures),
    m_state(std::make_unique<BoxState>()),
    m_coins(0),
    m_first_location(m_object_body->GetPosition()),
    m_gravity(world.GetGravity())
{
}

void Player::move()
{
    m_state->move(m_direction, m_object_body, m_touching_ground, m_gravity, m_object);
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
    //if (m_gravity.y > 0)
    m_object.setRotation(0);
    //else
      //  m_object.setRotation(180);
}

void Player::boxState()
{
    changeBodyAndSprite(m_player_textures.first);
    m_state.reset(new BoxState());
}

void Player::increasePoints()
{
    m_coins++;
}

void Player::kill()
{
    boxState();
    if (m_gravity.y < 0)
    {
        m_gravity_changed = true;
        m_gravity = -m_gravity;
    }
    m_object_body->SetTransform(m_first_location, m_object_body->GetAngle());
    m_object_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
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

void Player::hop(const float hop_force) const
{
    //to avoid "icetower" jumps
    m_object_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    if(m_gravity.y>0)
        m_object_body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -hop_force), true);
    else
        m_object_body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, hop_force), true);
}

void Player::reverseGravity()
{
    m_gravity = -m_gravity;
}

void Player::collideBrick(const GameTextures brick_type)
{
    if (brick_type != Floor)
        m_state->collideBrick(m_touching_ground, m_alive);
    else
        m_touching_ground = true;
}

void Player::setGravity()
{
    m_gravity_changed = true;
}

const bool Player::isGravityMarked()
{
    if (m_gravity_changed)
    {
        m_gravity_changed = false;
        return true;
    }
    else
        return m_gravity_changed;
}


void Player::setBoxState()
{
    m_set_box_state = true;
}

const bool Player::isBoxStateMarked()const
{
    return m_set_box_state;
}

void Player::handleBoxStateMarking()
{
    boxState();
    m_set_box_state = false;
}

void Player::setShipState()
{
    m_set_ship_state = true;
}

const bool Player::isShipStateMarked()const
{
    return m_set_ship_state;
}

void Player::handleShipStateMarking()
{
    shipState();
    m_set_ship_state = false;
}

void Player::setWin()
{
    m_win = true;
}

const bool Player::isWinner() const
{
    return m_win;
}

void Player::setDead()
{
    m_alive = false;
}

const bool Player::isAlive()const
{
    return m_alive;
}

const int Player::getCoins()const
{
    return m_coins;
}



void Player::changeBodyAndSprite(const GameTextures game_texture)
{
    m_object.setTexture(Resources::instance().getGameTexture(game_texture), true);
    const sf::Vector2f spriteSize(m_object.getTextureRect().width, m_object.getTextureRect().height);
    m_object.setOrigin(spriteSize.x / 2, spriteSize.y / 2);

    //create new shape
    b2PolygonShape shape;
    const sf::Vector2u boxSize = Resources::instance().getGameTexture(game_texture).getSize();
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
