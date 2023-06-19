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
    Player(b2World&, std::pair<GameTextures, GameTextures>, sf::Vector2f);
    void move();
    void updateDirection()override;
    void shipState();
    void boxState();
    void increasePoints();
    void kill();
    void releaseRight();
    void releaseLeft();
    void releaseSpace();
    void hop(float);
    void reverseGravity();
    void collideBrick(GameTextures);
    void setGravity();
    bool isGravityMarked();
    void setBoxState();
    bool isBoxStateMarked() ;
    void handleBoxStateMarking() ;
    void setShipState();
    bool isShipStateMarked() ;
    void handleShipStateMarking() ;
    void setWin();
    bool isWinner();
    void setDead();
    bool isAlive();
    int getCoins();

private:
    bool m_direction[4] = { false, false, false, false };
    std::unique_ptr <PlayerState> m_state;
    std::pair<GameTextures, GameTextures> m_player_textures;
    int m_coins;
    b2Vec2 m_first_location;
    bool m_touching_ground = false;
    void changeBodyAndSprite(GameTextures);
    b2Vec2 m_gravity;

    bool m_set_box_state = false;
    bool m_set_ship_state = false;
    bool m_win = false;
    bool m_alive = true;
    bool m_state_change = false;
    bool m_gravity_changed = false;
};