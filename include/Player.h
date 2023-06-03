#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "MovingObject.h"

class Player : public MovingObject
{
public:
    Player(b2World&, GameTextures);
    void move();
    void updateDirection();

    //void updateDirection(sf::Vector2f);
    //void move(sf::Time);
    //void UpgradeToSuper();
    //void DowngradeToNormal();


private:
    Direction m_direction = Stay;
    //std::unique_ptr <PlayerState> m_state;

};