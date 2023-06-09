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
    void updateDirection();
    void shipState();
    void boxState();
    void increasePoints();
    void kill()override;

    void releaseRight()override;
    void releaseLeft()override;
    void releaseSpace()override;

    void canJump();
    void hop();

private:
    bool m_direction[4] = { false, false, false, false };
    std::unique_ptr <PlayerState> m_state;
    std::pair<GameTextures, GameTextures> m_player_textures;
    int m_points;
    b2Vec2 m_first_location;
    bool m_touching_ground = false;

    void changeBodyAndSprite(GameTextures);

};