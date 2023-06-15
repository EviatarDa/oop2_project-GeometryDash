#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "MovingObject.h"
#include "Animation.h"


class Enemy : public MovingObject
{
public:
    Enemy(b2World&, GameTextures, sf::Vector2f, bool, GameAnimations, GameTextures);
    void move()override;
    void swap();

private:
    //0-Right 1-Left
    bool m_direction[2] = { true, false };
    float m_attach;
    Animation m_animation;
    bool m_up;

};