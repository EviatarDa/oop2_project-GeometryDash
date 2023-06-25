#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "MovingObject.h"
#include "PlayerState.h"
#include "BoxState.h"
#include "ShipState.h"

class Player : public MovingObject
{
public:
    Player(b2World&, const std::pair<GameTextures, GameTextures>, const sf::Vector2f);
    void move();
    void updateDirection()override;
    void shipState();
    void boxState();
    void increasePoints();
    void kill();
    void releaseRight();
    void releaseLeft();
    void releaseSpace();
    void hop(const float) const;
    void reverseGravity();
    void collideBrick(const GameTextures);

    void setGravity();
    const bool isGravityMarked();

    void setBoxState();
    const bool isBoxStateMarked() const;
    void handleBoxStateMarking() ;

    void setShipState();
    const bool isShipStateMarked() const;
    void handleShipStateMarking();

    void setWin();
    const bool isWinner() const;

    void setDead();
    const bool isAlive()const;

    const int getCoins()const;

private:
    bool m_direction[4] = { false, false, false, false };
    std::unique_ptr <PlayerState> m_state;
    std::pair<GameTextures, GameTextures> m_player_textures;
    int m_coins;
    b2Vec2 m_first_location;
    bool m_touching_ground = false;
    b2Vec2 m_gravity;

    bool m_set_box_state = false;
    bool m_set_ship_state = false;
    bool m_win = false;
    bool m_alive = true;
    bool m_state_change = false;
    bool m_gravity_changed = false;

    void changeBodyAndSprite(const GameTextures);

};