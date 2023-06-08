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


private:
    Direction m_direction = Stay;
    std::unique_ptr <PlayerState> m_state;
    std::pair<GameTextures, GameTextures> m_player_textures;
    int m_points;
    b2Vec2 m_first_location;

    void changeBodyAndSprite(GameTextures);

};