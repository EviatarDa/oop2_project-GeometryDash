#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "MovingObject.h"
#include "Animation.h"
#include "Factory.h"


class Enemy : public MovingObject
{
public:
    Enemy(b2World&, const GameTextures, const sf::Vector2f, const bool,
        const GameAnimations, const GameTextures);
    void move()override;
    void updateDirection() override;
    void swap();

private:
    //0-Right 1-Left
    bool m_direction[2] = { true, false };
    float m_attach;
    Animation m_animation;
    bool m_up;
    bool m_swap = false;

    static bool m_registerit1;
    static bool m_registerit2;
    static bool m_registerit3;
    static bool m_registerit4;

};